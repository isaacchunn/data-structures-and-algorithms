#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
//Question 2: Design a backtracking algorithm to print out all possible permutations of a given seequence. For example, input is gien as 1,2,3,4.
//The 24 output permutations are printed out from 1,2,3,4
//However, it is entirely obvious there should be 24 prints, as the number of permutations is actually n!, in this case it is 4! which is 24.



/// @brief Swaps two characters in a string (no error checking)
/// @param seq seq
/// @param idx1 index 1
/// @param idx2 index 2
void swap(char * seq, int idx1, int idx2)
{
    //if both the same, ignore.
    if(idx1 == idx2)
        return;

    char c = seq[idx1];
    seq[idx1] = seq[idx2];
    seq[idx2]= c;
}

/// @brief Prints all the permutations of a sequence
/// @param seq sequence
/// @param startIndex start index
/// @param endIndex end index
/// @param count total count of prints
void printPermutations(char * seq, int startIndex, int endIndex, int * count)
{
    //Reached the end of iteration of recursive, print current sequence
    if(startIndex == endIndex)
    {
        //Increase the count of our results
        (*count)++;
        puts(seq);
    }
    else
    {
        for(int i = startIndex; i <= endIndex; i++)
        {
            //Swap the character, then call recursive, then swap back. (typical backtracking problem)
            swap(seq, i, startIndex);
            printPermutations(seq, startIndex + 1, endIndex, count);
            swap(seq, i, startIndex);
        }
    }
}


//Driver code 
int main()
{
    char input[MAX_LENGTH];
    scanf("%s", &input);
    int length = strlen(input);   
    int count = 0;
    printf("Length: %d\n",length);
    printPermutations(input, 0, length -1, &count);
    printf("Total count: %d\n", count);
    return 1;
}