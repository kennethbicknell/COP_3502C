#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;
typedef struct Stack Stack;

struct Node{
    int value;
    int Maxsupport;
    Node * next;
};

struct LinkedList{
    Node * front;
};

struct Stack{
    LinkedList * list;
};

Stack * createStack();
LinkedList * createList();
void push(Stack * chain, int value);
void breakChain(Stack * chain);
void pop(Stack * chain);
Node * createNode();
void cleanup(Stack * chain);

//globals for chain management
int height = 0,link = 0, broken = 0, whole = 0;

int main(){
    Stack * chain = createStack();
    int input;
    scanf("%d", &input);

    while(input >= 0){
        link++;
        push(chain, input);
        scanf("%d", &input);
    }

    printf("Ending chain height is %d.\n", height);
    printf("There are %d broken links and %d whole links on the floor.\n", broken, whole);

    cleanup(chain);

    return 0;
}

Stack * createStack(){ //create the stack
    Stack * ret = (Stack *) malloc(sizeof(Stack));
    ret->list = createList();
    return ret;
}

LinkedList * createList(){ // create the list that the stack consists of
    LinkedList * ret = (LinkedList *) malloc(sizeof(LinkedList));
    ret->front = NULL;
    return ret;
}

void push(Stack * chain, int value){
    Node * front = chain->list->front; //for EZ life
    
    if(front == NULL){ //list is empty
        //no need to check first link
        Node * temp = (Node *) malloc(sizeof(Node));

        //init node
        temp->value = value;
        temp->next = front;
        temp->Maxsupport = value;
        
        //set new node as front of list/top of stack
        chain->list->front = temp;
        height++;
        return;
    }
    
    //potential # of links supported at this spot by last weak spot
    int currmax = front->Maxsupport - 1;
    
    if (currmax < 0){ //if the max supported # of links at this poiunt is <0 we cant support this link
        breakChain(chain);
    } else {
        Node * temp = (Node *) malloc(sizeof(Node));
        
        //init
        temp->value = value;
        temp->next = front;
        //if the grade of this link is less than the amount of links supported by last weak point than this is the new weak point
        (currmax < value) ? (temp->Maxsupport = currmax) : (temp->Maxsupport = value);

        //set the new node as the top of the stack
        chain->list->front = temp;
        height++; //new link inceases chain height
    }
}

void breakChain(Stack * chain){
    //place holders to make life easy
    Node * cur = chain->list->front;
    Node * next = chain->list->front->next;
    
    whole++; //the link that caused the break will always be whole

    //max support decreases by one from the weakest link until the end
    //pop links of the chain while the support is following this pattern
    while ((next->Maxsupport) - (cur->Maxsupport) == 1){
        
        //due to the nature of the support pattern any link with val = support will break when the chain breaks
        (cur->value == cur->Maxsupport) ? broken++ : whole++;
        height--; //height always decreases by one when a link comes off
        
        pop(chain); //take the link off the chain
        
        cur = chain->list->front; //more EZ lif
        next = chain->list->front->next;
        
        if (next == NULL && (cur->value == cur->Maxsupport)){ //if we are at the end and the top was a weakest link then it breaks
            pop(chain);
            broken++;
            height--;
            break;
        }
    }

    if(next != NULL){ //handling for the first weak link because it would'nt follow the pattern in a nonempty list
        pop(chain);
        broken++;
        height--;
    }
    printf("Chain broken at link %d. New height is %d.\n", link, height);
}

void pop(Stack * chain){ //stack pop
    Node * temp = chain->list->front;
    chain->list->front = temp->next;
    free(temp);
    return;
}

void cleanup(Stack * chain){
    Node * front = chain->list->front;
    while (front != NULL){ //pop each node from the stack which frees it
        pop(chain);
        front = chain->list->front;
    }
    free(chain->list); //free the list that the stack consists of
    free(chain);//free the stack
}


