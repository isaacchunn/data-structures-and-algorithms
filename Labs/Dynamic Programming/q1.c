#include <stdio.h>
#include <stdlib.h>

//memory
int *r;

//Complexity; O(2^n)
/// @brief Solves the rod cutting problem using recursion
/// @param p price list
/// @param n length of rod
/// @return maximum revenue of rod cutting problem
int cr_recursive(int *p, int n)
{
    //Price holder
    int q;
    int i;
    //If the length is 0, return 0=
    if(n == 0)
        return 0;

    //Set q to be a very low number
    q = -99999;
    //For each i, we recursively find all the possible matching, but this gives alot of repeated calculations
    for(i = 1; i <= n; i++)
    {
        //We find the max of the price of the current (including this) and all sub recursive calls
        q = max(q, p[i] + cr_recursive(p, n - i));
    }
    
    return q;
}

/// @brief Solves the rod cutting problem from top down using DP
/// @param p price list
/// @param n length of rod
/// @return maximum revenue of rod cutting problem
int cr_top_down_dp(int *p, int n)
{
    int q, i;
    //If lengh is 0 return 0.
    if (n == 0)
        return 0;
    //Else we can try to use our memoized R array
    //If at this index the result is more than 0, then we have calculated this before and we can reuse it
    if(r[n] > 0)
    {
        return r[n];
    }
    else
    {
        //Elsee we have to calculate current r[n]
        q = -99999;
        for(i = 1; i <=n; i++)
        {
            q = max(q, p[i] + cr_top_down_dp(p,n-i));
        }
        //Store r[n]
        r[n] = q;
    }
    return q;
}

//TIME COMPLEXITY : N^2
/// @brief Solves the rod cutting problem from bottom up
/// @param p price list
/// @param n length of rod
/// @return maximum revenue of rod cutting problem
int cr_bottom_up_dp(int *p, int n)
{
    int q, i, j;

    r[0] = 0; //Update price calculated if length 0 to be 0! Since it was initialzied as -1.
    
    //Double for loop so n^2
    for(j = 1; j <= n; j++)
    {  
        q = -9999;
        for(i = 1; i <= j; i++)
        {
            q = max(q, p[i] + r[j-i]);
        }
        r[j] = q;
    }
    return r[n];
}
 
void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,5,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    
    printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
    scanf("%d",&function);
    while (function != 0)
    {
        if (function == 1)
        {       
             //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;

            printf("The maximun value is: %d \n", cr_recursive(p,n));
        }
        else if (function == 2)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_top_down_dp(p,n));
        }
        else if (function == 3)
        {
            //set all memory elements to -1
            for (i=0; i<=n; i++)
                r[i] = -1;
                
            printf("The maximun value is: %d \n", cr_bottom_up_dp(p,n));
        }
        printf("Choose a function (1 for recursive, 2 for top-down DP, 3 for bottom-up DP, 0 to stop): \n");
        scanf("%d",&function);
    }
}