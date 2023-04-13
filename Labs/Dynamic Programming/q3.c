#include <stdio.h>
#include <stdlib.h>

/// @brief Calculates the distinct ways that one can score n points
/// @param n n points
/// @param score score array
/// @return number of ways that can score
int waysToScore(int n, int* score)
{
    //Do the bottom up approach
    int i ;
    //Create our memoization table
    int * r = calloc(n + 1, sizeof(int));

    //Set our base case, we will use this value as our counter of the "+1"
    r[0] = 1;
    //We can update our tables in multiples of 3,5,10 using +=, and then return back the value at our table with respect to n
    for(i = 3; i <= n; i++)
    {
        //Count all the ways we can go in multiples of 3 to n
        r[i] += r[i-3];
    }
    //Do the same for the rest
    for(i = 5; i <= n; i++)
    {
        //Count all the ways we can go in multiples of 3 to n
        r[i] += r[i-5];
    }
    for(i = 10; i <= n; i++)
    {
        //Count all the ways we can go in multiples of 3 to n
        r[i] += r[i-10];
    }
    //Then just return r at index n
    return r[n];
}

 
void main ()
{
    int n;

    int score[3] = {3,5,10}; 

    printf("Enter the value of N: ");
    scanf("%d",&n);


    printf("The number of ways to reach to a score of %d is: %d \n",n, waysToScore(n,score));
}
