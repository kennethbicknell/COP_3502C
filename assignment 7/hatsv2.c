/*
Kenneth Bicknell
12/04/2019
assignment 7 : magical hats
Mostly sudoku.c from Prof. Meade
*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE (1==1)
#define FALSE (1==0)

#define EMPTY 0
#define OPTIONS 3

int ** solvedBoard;
int *** unsolvedBoard;
int size;

void createBoards();
void readBoard();
void printBoard();
int isValid(int, int);
int backTrack(int, int);

int main(){
    
    scanf("%d", &size); //read in size of grid
    
    createBoards(); //create grids of desired size
    
    readBoard(); //fill the grids

    if (backTrack(0, 0))//find correct grid
    {
        printBoard();
    }
    else
    {
        printf("No Solution found.\n");
    }
    
    return 0;
}

void createBoards(){
    int i,j;
    
    //used dynamic memory for ease of access
    solvedBoard = (int **) calloc(size, sizeof(int*));
    for (i = 0; i < size; i++){
        solvedBoard[i] = (int *) calloc(size, sizeof(int));
    }

    //triple pointer because each spot in the 2d grid hold 3 numbers
    unsolvedBoard = (int ***) calloc(size, sizeof(int **));
    for (i = 0; i < size; i++){
        unsolvedBoard[i] = (int **) calloc(size, sizeof(int *));
    }

    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            unsolvedBoard[i][j] = (int *) calloc(OPTIONS, sizeof(int));
        }
    }
}

int isValid(int currow, int curcol){
    int value, row, col;
    int contains[size];
    if(curcol == 0 && currow != 0){
        currow--;
        curcol = size - 1;
    } else if(curcol != 0){
        curcol--;
    }
    
    // Check current row
    //reset contains
    for (value = 0; value < size; value++)
    {
        contains[value] = FALSE;
    }
        
    // Loop through the row
    for (col = 0; col < size; col++)
    {
        // Check if a value is present
        if (solvedBoard[currow][col] != EMPTY)
        {
            // Check if the value is already in the row
            if (contains[solvedBoard[currow][col] - 1])
            {
                return FALSE;
            }
                
            // Set the value is in the row
            contains[solvedBoard[currow][col] - 1] = TRUE;
        }
    }
    
    

    // Check current col
    //clear contains
    for (value = 0; value < size; value++)
    {
        contains[value] = FALSE;
    }
        
    // Loop through the row
    for (row = 0; row < size; row++)
    {
        // Check if a value is present
        if (solvedBoard[row][curcol] != EMPTY)
        {
            // Check if the value is already in the col
            if (contains[solvedBoard[row][curcol] - 1])
            {
                return FALSE;
            }
                
            // Set the value is in the col
            contains[solvedBoard[row][curcol] - 1] = TRUE;
        }
    }
    
    // No invalid row or column was found
    return TRUE;
}

int backTrack(int r, int c){
    // THIS IS BACKTRACKING : Check validity
    if (!isValid(r, c))
    {
        return FALSE;
    }
    
    // Check if col index (c) is off the board
    if (c == size)
    {
        return backTrack(r + 1, 0);
    }
    
    // Check if row index (r) is off the board
    if (r == size)
    {
        return TRUE;
    }
    
    
    
    // Try all possible decisions
    int attempt;
    for (attempt = 0; attempt < OPTIONS; attempt++)
    {
        solvedBoard[r][c] = unsolvedBoard[r][c][attempt];
        if (backTrack(r, c + 1))
            return TRUE;
        
        // Undo the choice
        solvedBoard[r][c] = EMPTY;
    }
    
    // No solution found
    return FALSE;
}

void printBoard(){
    //loop through each spot to print
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("%d ", solvedBoard[i][j]); 
        printf("\n");
    }
}

void readBoard(){
    int i, j, k;
    //loop through each posiple spot in the grid, with each spot holding an array of 3 numbers
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
          for(k = 0; k < OPTIONS; k++)
            scanf("%d", &unsolvedBoard[i][j][k]);
}

