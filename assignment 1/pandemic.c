#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE -1

#define TRUE (1==1)
#define FALSE (!TRUE)

#define ADD_STR "ADD"
#define END_STR "END"


#define DEFAULT_CAP 5
#define MAX_INPUT 100


typedef struct ArrayList
{
   int size;
   int cap;
   char ** strings;
} ArrayList;

typedef struct ArrayArrayList
{
   int size;
   int cap;
   ArrayList * student;
} ArrayArrayList;

int expand(ArrayList *);
int expand2(ArrayArrayList *);
int add(ArrayList *, char*);
int add2(ArrayArrayList *);
int findStudent(ArrayArrayList * students, char* row);
ArrayArrayList * newArrayArrayList();
int countStudents(ArrayArrayList * students, char* symptom);
void printStudents(ArrayArrayList * students, char* symptom);

int expand(ArrayList * al)
{
   //double the amount of space allocated to the array list
   int newCap = al->cap * 2;
   char** newValues = (char **) realloc(al->strings, newCap * sizeof(char*));
   
   // Check if allocation failed
   if (newValues == NULL)
   {
      return FAILURE;
   }
   
   
   // Update the array list
   al->cap = newCap;
   al->strings = newValues;
   
   // Return a success!
   return SUCCESS;
}


int expand2(ArrayArrayList * al)
{
   int newCap = al->cap * 2;
   ArrayList * newValues = 
      (ArrayList *) realloc(al->student, newCap * sizeof(ArrayList));
   
   // Check if allocation failed
   if (newValues == NULL)
   {
      return FAILURE;
   }
   
   // Update the array list
   al->cap = newCap;
   al->student = newValues;
   
   // Return a success!
   return SUCCESS;
}

int add(ArrayList * al, char* newInput)
{
   // Check if array list is full
   if (al->cap == al->size)
   {
      // Try to expand the array list
      if (expand(al) == FAILURE)
      {
         return FAILURE;
      }
   }
   
   // Allocate the memory then store the new value
   //We use strlen() to make sure we use only the memory we need
   al->strings[al->size] = (char*) calloc(strlen(newInput)+1,sizeof(char));
   strcpy(al->strings[al->size], newInput);
   al->size++;
   
   // Return a success
   return SUCCESS;
}

int add2(ArrayArrayList * students)
{
   // Check if array list is full
   if (students->cap == students->size)
   {
      
      // Try to expand the array list
      if (expand2(students) == FAILURE)
      {
         return FAILURE;
      }
   }
   
   // Initialize the new ArrayList
   students->student[students->size].size = 0;
   students->student[students->size].cap = DEFAULT_CAP;
   students->student[students->size].strings = (char **) calloc(DEFAULT_CAP, sizeof(char *));
   
   if (students->student[students->size].strings == NULL)
   {
      return FAILURE;
   }
   
   
   // Increment the number of elements in our list
   students->size++;
   
   // Return a success
   return SUCCESS;
}


ArrayArrayList * newArrayArrayList()
{
   ArrayArrayList * ret = calloc(1, sizeof(ArrayArrayList));
   
   if (ret == NULL)
      return ret;
   
   ret->size = 0;
   ret->cap = DEFAULT_CAP;
   // int ** arr2d = (int **) calloc(size, sizeof(int *));
   ret->student = (ArrayList *) calloc(ret->cap, sizeof(ArrayList));
   
   if (ret->student == NULL)
   {
      free(ret);
      ret = NULL;
   }
   
   return ret;
}

int findStudent(ArrayArrayList * students, char* studentName)
{
   int ret = FAILURE;
   int i;
   for (i = 0; i < students->size; i++)
   {
      // check the name of each student to see if it matches target
      if (strcmp(students->student[i].strings[0], studentName) == 0)
      {
         // the student exists
         return i;
      }
   }
   
   if (add2(students) == FAILURE)
   {
      return FAILURE;
   }
   
   ret = students->size - 1;
   
   // We add the student to the array list
   if (add(&students->student[ret], studentName) == FAILURE)
   {
      return FAILURE;
   }
   
   // Return the index of the new student
   return ret;
}

int countStudents(ArrayArrayList * students, char* symptom){
	int ret = 0;
	int i, j;
	//really inefficient function that checks each symptom of each student
	//and increases a counter each time it matches the target
	for (i = 0; i < students->size; i++){
		for (j = 1; j < students->student[i].size; j++){
			if(strcmp(students->student[i].strings[j], symptom) == 0)
				ret++;
		}
	}
	return ret;
}

void printStudents(ArrayArrayList * students, char* symptom){
	int i, j;
	//really inefficient function that checks each symptom of each student
	//and prints the student's name each time it matches the target
	
	for (i = 0; i < students->size; i++){
		for (j = 1; j < students->student[i].size; j++){
			if(strcmp(students->student[i].strings[j], symptom) == 0)
				printf("%s\n", students->student[i].strings[0]);
		}
	}
}

void freeMem(ArrayArrayList * students){
	int i, j;
	
	for (i = 0; i < students->size; i++){
		for (j = 0; j < students->student[i].size; j++){
			free(students->student[i].strings[j]); //this frees each string/char *
			
		}
		free(students->student[i].strings);//this frees each string array/char **
	}
	free(students->student);//this clears each arraylist
	
}

int main()
{
   int numInputs;
   scanf("%d", &numInputs);
   while ((getchar()) != '\n');//get numInputs and clear input stream
   
   ArrayArrayList * students = newArrayArrayList();
   
   if (students == NULL)
   {
      return 1;
   }
   
   for (int i = 0; i < numInputs; i++)
   {
	  char instr; //instruction
	  char name[MAX_INPUT+1];
	  char symptom[MAX_INPUT +1];
	  char query[7+1]; //static character arrays to hold values before adding them to array list
	  
	  scanf("%c", &instr);
	  
	  if (instr == 'u')//update
	  {
		scanf("%s", name);
		scanf("%s", symptom);
		while ((getchar()) != '\n');
		//get the students name and symptom then clear the input stream
		
		int studentIndex = findStudent(students, name);
		
		//findStudent() will add new students to the arraylist so we only need to add the symptom
		
		if (studentIndex == FAILURE){
			return 1;
		}
		
		//attempt to add the symptom to the found student
		if (add(&students->student[studentIndex], symptom) == FAILURE){
			return 1;
		}
		
		} else if	(instr == 'q'){ //query
		  
		  scanf("%s", query); 
		  
		  if(strcmp(query, "student") == 0){ //check if query is by student
			  
			  scanf("%s", name);
			  while ((getchar()) != '\n');//get name + clear input stream
			  
			  int studentIndex = findStudent(students, name);
			  int i;
			  
			  //student name is an element of the array so symptoms = size - 1
			  printf("%d\n", students->student[studentIndex].size - 1);
			  
			  for (i = 1; i < students->student[studentIndex].size; i++){
				  //name is in 0 index so print all strings affter
				  printf("%s\n", students->student[studentIndex].strings[i]);
			  }
			  
		  } else if(strcmp(query, "symptom") == 0){ //or by symptom
			  scanf("%s", symptom);
			  while ((getchar()) != '\n');//get symptom + clear input stream
			  
			  printf("%d\n", countStudents(students, symptom));
			  printStudents(students, symptom);
		  }
	  }
   }
   freeMem(students); //this goes through each array level to clear all the memory
   free(students);//this clears the arrayarraylist
   return 0;
}

