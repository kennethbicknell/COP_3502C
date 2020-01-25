#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BEFORE -1
#define AFTER 1

#define SUCCESS 0
#define FAILURE -1

#define MAX_LEN 100

typedef struct name{
    char* string;
} name;

typedef struct arrayList{
    int size;
    name* names;
} arrayList;

char newAlpha[26]; //alphabet

arrayList* createList(int numNames);
void cleanup(arrayList * list);
int mergeSort(int start, int end, arrayList* nameList);
int readNames(int numNames, arrayList* nameList);
void printNames(int numNames, arrayList* nameList);
int compare(char* s1, char* s2);
int findIndex(char letter);


int main(){
    int numNames, i;

    //read in the new order of the alphabet
    for(i = 0; i < 26; i++){
        scanf(" %c", &newAlpha[i]);
    }
    
    scanf("%d", &numNames);
    
    arrayList * nameList = createList(numNames); //create array with as much space as we need
    if (nameList == NULL)
        return FAILURE;

    if (readNames(numNames, nameList) == FAILURE) //read in the names
        return FAILURE;
    
    if (mergeSort(0, numNames - 1, nameList) == FAILURE){//sort the names
        cleanup(nameList);
        return FAILURE;
    }
    printNames(numNames, nameList); //print the names

    cleanup(nameList);

    
    
    return 0;
}

arrayList* createList(int numNames){
    //create an arraylist to hold our names
    arrayList * ret;
    ret = (arrayList *) calloc(1, sizeof(arrayList));
    if (ret == NULL)
        return  NULL;

    ret->size = numNames;
    ret->names = (name*)calloc(numNames, sizeof(name)); //we know the exact amount of memory we will need so we just immediately allocate it

    if (ret->names == NULL){
        free(ret);
        return NULL;
    }


    return ret;
}

void cleanup(arrayList * list){
    int i;
    for (i = 0; i < list->size; i++){
        free(list->names[i].string); //free each name
    }
    free(list->names); //free the array of names

    free(list); //free the whole list
}

int readNames(int numNames, arrayList* nameList){
    //read each name and put it in nameList
    char buffer[MAX_LEN + 1];
    int i;
    for(i = 0; i < numNames; i++){
        scanf("%s", buffer);
        nameList->names[i].string = (char *) calloc(strlen(buffer) + 1, sizeof(char)); //calloc the exact memory space needed for each name
        if (nameList->names[i].string == NULL){
            cleanup(nameList);
            return FAILURE;
        }
        strcpy(nameList->names[i].string, buffer);
    }
    return SUCCESS;
}

void printNames(int numNames, arrayList* nameList){
    //print each name in the list
    int i;
    for(i = 0; i < numNames; i++){
        printf("%s\n", nameList->names[i].string);
    }
    return;
}


//performs a merge sort using practice test 1 #2 as a template
int mergeSort(int start, int end, arrayList* nameList){ 
    int front, mid, back, merged, i;
    //base case first to avoid shenaniagns
    if (start == end){ //only 1 element -> dont sort
        return SUCCESS;
    }
    
    arrayList* temp = createList(end-start + 1);
    if(temp == NULL){
        return FAILURE;
    }
    

    //set up for breaking the list in half
    front = start;
    mid = (start + end) / 2;
    back = mid + 1;
    merged = 0;
    //front is front half of the array
    //back is back half of the array
    
    if (mergeSort(front, mid, nameList) == FAILURE){ //sort the front 1/2
        cleanup(temp);
        return FAILURE;
    }
    if (mergeSort(back, end, nameList) == FAILURE){ //sort the front 1/2
        cleanup(temp);
        return FAILURE;
    }
    
    
    while (merged <= end - start){
        
        if ( front == mid + 1 || (back != end + 1 && compare(nameList->names[front].string, nameList->names[back].string) == BEFORE)){
            //if the front is empty or the string in the back half should come first
            //copy the string in the back half to the sorted array
            
            // calloc just enough memory in temp for the string
            temp->names[merged].string = (char*) calloc(strlen(nameList->names[back].string) + 1, sizeof(char));
            strcpy(temp->names[merged++].string, nameList->names[back++].string);
        } else {
            //otherwise copy the string from the front half into the array
            
            //same calloc procedure
            temp->names[merged].string = (char*) calloc(strlen(nameList->names[front].string) + 1, sizeof(char));
            strcpy(temp->names[merged++].string, nameList->names[front++].string);
        }
    }
    for (i = start; i <= end; i++){
        //because this program is trying to be as memory efficient as possible we have to
        //realloc in case the word is bigger than the already calloced space
        char* buf = (char *) realloc(nameList->names[i].string, (strlen(temp->names[i-start].string) + 1) * sizeof(char));
        if (buf == NULL){
            cleanup(temp);
            return FAILURE;
        }
        nameList->names[i].string = buf;
        strcpy(nameList->names[i].string, temp->names[i-start].string);
    }
    cleanup(temp);
    
    return SUCCESS;
}

int compare(char* s1, char* s2){
    //return BEFORE if s2 comes before s1
    //retrun AFTER if s2 comes before s1 or order doesnt matter.
    int i;


    for (i = 0; i <= MAX_LEN; i++){
        if(s1[i] == '\0' && s2[i] == '\0'){
            return AFTER; //if we reach the end of both words at the same time that means they are the same and the order doesnt matter
        } else if (s1[i] == '\0' && s2[i] != '\0'){
            return AFTER; // if we reach the end of s1 before the end of s2 that means s2 is longer and comes after s1
        } else if (s1[i] != '\0' && s2[i] == '\0'){
            return BEFORE; // if we reach the end of s2 first this means that s1 is longer and s2 should come before s1
        } else if (findIndex(s1[i]) < findIndex(s2[i])){
            return AFTER; //if the curent letter of s1 comes before the current letter of s2, s2 should come after s1
        } else if (findIndex(s1[i]) > findIndex(s2[i])){
            return BEFORE; //if the curent letter of s1 comes after the current letter of s2, s2 should come before s1
        }
    }
}

int findIndex(char target){
    //go through each letter to  find the index of the target letter
    int i;
    for (i = 0; i < 26; i++){
        if (newAlpha[i] == target)
            return i;
    }
    return -1;
}