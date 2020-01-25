#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rot13(char string[]);
int isvowel(char character);

int main() {
	int n; //user input number of individual words
	int count = 0; //counter for loop
	char string[100 + 1];
	scanf("%d", &n);
	while (count < n) {
		scanf("%s", string);
		rot13(string);
		printf("%s\n", string);
		count++;
	}
	return 0;
}

void rot13(char string[]) {//this function goes through each letter and performs the encryption method for each letter
	int currentPos, spacesJumped = 13, newPosition, length;
	char newChar;
	length = strlen(string);
	for (int i = 0; i < length; i++) {//progress through the string one letter at a time
		if (!(string[i] >= 'a' && string[i] <= 'z')) { //if letter is not a lowercase letter then exit the function
			return;
		}
		currentPos = string[i] - 'a';
		newPosition = (currentPos + spacesJumped) % 26;//this is for handling wrapping of letters near the end of the alphabet
		newChar = 'a' + newPosition;
		spacesJumped = isvowel(string[i]); //change spaces jumped for the next letter
		string[i] = newChar;
		
	}


}

int isvowel(char character) {
	if (character == 'a' || character == 'e' || character == 'i' || character == 'o' || character == 'u') {
		return 14;
	}else return 13;
}