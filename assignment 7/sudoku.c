
#include <stdio.h>
#include <stdlib.h>

#define TRUE (1==1)
#define FALSE (1==0)

//#define SIZE 9
//#define SUB_SIZE 3
#define EMPTY 0
#define OPTIONS 3

int ** solvedBoard;
int *** unsolvedBoard;
int size;

void createBoards();
void readBoard();
void printBoard();
int isValid();
int backTrack(int, int);

int main()
{
    scanf("%d", &size); //read in size of grid
    
    createBoards(); //create grids of desired size
    
    readBoard(); //filll the grids

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

int isValid()
{
    int row, col, subRow, subCol, value, r, c;
    
    // Check each row
    for (row = 0; row < size; row++)
    {
        // Set that no value exists
        int contains[size];
        for (value = 0; value < size; value++)
        {
            contains[value] = FALSE;
        }
        
        // Loop through the row
        for (col = 0; col < size; col++)
        {
            // Check if a value is present
            if (solvedBoard[row][col] != EMPTY)
            {
                // Check if the value is already in the row
                if (contains[solvedBoard[row][col] - 1])
                {
                    return FALSE;
                }
                
                // Set the value is in the row
                contains[solvedBoard[row][col] - 1] = TRUE;
            }
        }
    }
    
    // Check each column
    for (col = 0; col < size; col++)
    {
        // Set that no value exists
        int contains[size];
        for (value = 0; value < size; value++)
        {
            contains[value] = FALSE;
        }
        
        // Loop through the column
        for (row = 0; row < size; row++)
        {
            // Check if a value is present
            if (solvedBoard[row][col] != EMPTY)
            {
                // Check if the value is already in the row
                if (contains[solvedBoard[row][col] - 1])
                {
                    return FALSE;
                }
                
                // Set the value is in the row
                contains[solvedBoard[row][col] - 1] = TRUE;
            }
        }
    }
    
    // No invalid row or column was found
    return TRUE;
}

int backTrack(int r, int c)
{
    printf("%d , %d\n", r, c);
    // THIS IS BACKTRACKING : Check validity
    if (!isValid())
    {
        return FALSE;
    }
    
    // Check if col index (c) is off the board
    if (r == size)
    {
        return backTrack(0, c + 1);
    }
    
    // Check if row index (r) is off the board
    if (c == size)
    {
        return TRUE;
    }
    
    // Check if forced
    /*if (solvedBoard[r][c] != 0)
    {
        return backTrack(r, c + 1);
    }*/
    
    // Try all possible decisions
    int attempt;
    for (attempt = 0; attempt < OPTIONS; attempt++)
    {
        solvedBoard[r][c] = unsolvedBoard[r][c][attempt];
        if (backTrack(r+1, c))
            return TRUE;
        
        // Undo the choice
        solvedBoard[r][c] = EMPTY;
    }
    
    // No solution found
    return FALSE;
}

void printBoard()
{
    //loop through each spot to print
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("%d ", solvedBoard[i][j]); 
        printf("\n");
    }
}

void readBoard()
{
    int i, j, k;
    //loop through each posiple spot in the grid, with each spot holding an array of 3 numbers
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
          for(k = 0; k < OPTIONS; k++)
            scanf("%d", &unsolvedBoard[i][j][k]);
}

