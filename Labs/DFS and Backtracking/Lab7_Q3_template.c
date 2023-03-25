#include <stdio.h>
#include <stdlib.h>

int nQueens(int** board, int N, int col);
int isSafe(int** board,int N, int row, int col);
void printSolution(int** board, int N);

//Global variable
int count = 0;

int main()
{
    int **board;
    int BSize;

    int i,j;

    printf("Enter the size of chessBoard:\n");
    scanf("%d",&BSize);

    board = (int **)malloc(BSize*sizeof(int *));
    for(i=0;i<BSize;i++)
        board[i] = (int *)malloc(BSize*sizeof(int));

    for(i=0;i<BSize;i++)
       for(j=0;j<BSize;j++)
           board[i][j] = 0;

    nQueens(board, BSize, 0);
    printf("Total Solutions: %d\n", count);
    return 0;
}

/// @brief Prints out all the solutions of the nqueens problem
/// @param board board
/// @param BSize board size
/// @param col columns
/// @return 1 if succcessful, 0 if not.
int nQueens(int** board, int BSize, int col)
{
    int i,j;

    //Sanity check.
    if(board == NULL)
        return 0;

    //Backtracking function
    if(col >= BSize)
    {
        printSolution(board,BSize);
        count++;
        return 1;   
    }

    //Do a loop for the columns
    for(i = 0; i < BSize; i++)
    {
        //If this row and col is safe
        if(isSafe(board, BSize, i, col))
        {
            //Place a queen here
            board[i][col] = 1;
            //if(nQueens(board,BSize,col+1)) //If you want the first solution
                //return 1;
            nQueens(board,BSize,col+1); //recursion like, it will keep going using this i to find a solution
            //Else delete the queen, then later we reset and continue, finding all the solutions.
            board[i][col] = 0;
        }
    }
    return 0;
}

//Safe checking
int isSafe(int** board,int BSize, int row, int col)
{
    int i, j;

    // Horizontal check
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Upper left diagonal check
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Lower left diagonal check
    for (i = row, j = col; j >= 0 && i < BSize; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void printSolution(int** board, int BSize)
{
    int i,j;
    for (i = 0; i < BSize; i++) {
        for (j = 0; j < BSize; j++){
            if(board[i][j]==1)
                printf(" Q ");
            else
                printf(" + ");
        }
        printf("\n");
    }
    printf("\n");
}
