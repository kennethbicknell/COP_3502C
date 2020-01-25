#include <stdio.h>
#include <stdlib.h>

#define FAILURE 1
#define S

int *  post;
int * pre;
int main(){
    int numElements;
    scanf("%d", numElements);
    post = createArray(numElements);
    if(post == NULL)
        return FAILURE;
    pre = createArray(numElements);
}

int * createArray(int numElements){
    return (int *) malloc(numElements * sizeof(int));
}