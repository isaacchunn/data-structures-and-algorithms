#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

//Question 3: FInd the length of longest substring of a given string ofd digits, such that sum of digits in the first half 
//and second half of the substring is same. For example, if the input string is 142124, the whole string is the answer.
//The sum of the first 3 digits = sum of the last 3 digits. (1+4+2) = (1+2+4). Thus the length is 6. If the input is 12345678
//Then the output is 0. If the input is 9430723, then the output is 4 (4307)

//Maybe this can be a sliding window approach?

int lengthLongestSubstring(char * seq)
{
    //Set up our indexes
    int left = 0;
    int right = strlen(seq) - 1;
}


//Driver code 
int main()
{

    return 1;
}