#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 100

int main(){
	//provides 99999 random string of length Length
	int i, j, stringAmount;
	srand(time(NULL));
	stringAmount = 99999;
	
	for (i = 0; i < stringAmount; i++){
		for (j=0; j < LENGTH; j++){
			printf("%c", (rand() % 26) + 'a');
		}
		printf("\n");

	}

}