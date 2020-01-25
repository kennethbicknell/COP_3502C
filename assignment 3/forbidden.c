#include <stdio.h>
#include <string.h>

#define TRUE (0==0)
#define FALSE !TRUE
#define MAXLEN 12

int swap(char * inputString, char badString[][MAXLEN + 1], int badcount, int from, int to);//swaps 2 characters and checks all word combinations with new letter positions

int main(){
    char inputString[MAXLEN + 1], usedchar[MAXLEN + 1] = "";
    int badcount, i, j, used, perms = 0;
    
    //up to line 23 is getting input
    scanf("%s", inputString);
    scanf("%d", &badcount);
    
    int inLength = strlen(inputString);
    int useLength = 0;

    char badString[badcount][MAXLEN + 1];//create array after we know amount of forbidden words

    for(i = 0; i < badcount; i++){
        scanf("%s", badString[i]); //get each forbidden word
    }

    /*
        we check if each letter has already been used in the place we are swapping to
        basically saying "if we already put an a into this spot dont put a different a in"
    */

    for(i = 0; i < inLength; i++){// cycle through each letter
        used = FALSE; //reset used cause new letter
        
        for(j = 0; j < useLength; j++){
            if(usedchar[j] == inputString[i]){
                used = TRUE;
                break; //check each character to see if it's used before counting it
            }
        }
        
        if(!used){ //if the char was not used, expand the array, and add char to end
            usedchar[useLength] = inputString[i];
            usedchar[useLength + 1] = '\0';
            useLength++;
            //swap each unused letter into the first place
            perms += swap(inputString, badString, badcount, i, 0);
        }
    }

    printf("%d\n", perms);

    return 0;

}



int swap(char * inputString, char badString[][MAXLEN + 1], int badcount, int from, int to){
    int i, j, perms = 0, used;
    char temp, usedchar[MAXLEN + 1] = "";

    int inLength = strlen(inputString);
    int useLength = 0;

    if(to >= inLength){ //we use out of bounds to know we've reached a complete word
        
        for (i = 0; i < badcount; i++){
            if (strstr(inputString, badString[i]) != NULL)
                return 0; //if the word contains a forbidden word ignore it
        }

        return 1; //if the word doesnt contain any forbidden words then count it
    }

    if(from >= inLength) //because we check out of bounds for complete words we have to ignore out of bound swaps on incomplete words
        return 0;

    //swap the letters around  
    temp = inputString[to];
    inputString[to] = inputString[from];
    inputString[from] = temp;

    /*
        we check if each letter has already been used in the place we are swapping to
        basically saying "if we already put an a into this spot dont put a different a in"
    */


    
    for(i = to + 1; i <= inLength; i++){//loop through each letter that has not yet been swapped

        used = FALSE; //reset false each time
        for(j = 0; j < useLength; j++){
            if(usedchar[j] == inputString[i] && i < inLength){
                used = TRUE;//check each character to see if it's used before counting it
                break;
            }
        }
        
        if(!used){//if the char was not used, expand the array, and add char to end
            usedchar[useLength] = inputString[i];
            usedchar[useLength + 1] = '\0';
            useLength++;
            //swap each unused letter into the next place
            perms += swap(inputString, badString, badcount, i, to + 1);
        }
    }

    //reverse the swap
    inputString[from] = inputString[to];
    inputString[to] = temp;

    return perms;
}
