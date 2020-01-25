#include <stdio.h>
#include <stdlib.h>

#define LENGTH 100

int main(){
	int i, j;
	char names[5][4] = {"abc", "cba", "qwe", "ewq", "tyu"};
	 printf("100000\n");
	 for(i = 0; i < 100000; i++){
		 printf("u ");
		 //printf("%s ", names[rand() % 5]);
		 for (j=0; j<3; j++){
			printf("%c", 'a' + (rand() % 26));
		 }
		 printf(" ");
		 for (j=0; j<LENGTH; j++){
			//randomString[j] = 'a' + (rand() % 26);
			printf("%c", 'a' + (rand() % 26));
		 }
		 printf("\n");
	 }
}