#include <stdio.h>
#include <stdlib.h>

//memory
int *r;

/// @brief Bottom up approach of rod cutting problem but printing the pieces cut in ascending order
/// @param p price list
/// @param n length of rod
/// @return maximum value.
int cr_bottom_up_dp_print(int *p, int n)
{
    //We need another array for this, mainly called s to store some parent like structure.
    //Handle our typical rod problem first
    int q, i, j;

    //Memory alloc a new "parent array to store first index of cut"
    int * s = calloc(n + 1, sizeof(int));

    r[0] = 0;
    for (j = 1; j <= n; j++)
    {
        q = -9999;
        for(i = 1; i<= j; i++)
        {
            //Instead of using max, we will use if to store our "last known index of cut"
            if(q < p[i] + r[j-i])
            {
                q = p[i] + r[j -i];
                //Update our s array at the parent index to be current rod cut max
                s[j] = i;
            }
        }
        r[j] = q;
    }

    //Print out s array
    for(i = 0; i <=n; i++)
        printf("%d ", i);
    putchar('\n');
    for(i = 0; i <=n; i++)
        printf("%d ", s[i]);
    printf("\nOrder of cutting pieces: ");
    //Now we have our solution
    //We would like to print out the order of cutting in ascending order.
    while (n > 0)
    {
        //While the "length is greater than 0, print the first cut index at this array.
        printf("%d, ", s[n]);
        //Minus off the rest
        n -= s[n];
    }

    return q;
}

 
void main ()
{
    int n;      //length of  rod
    int function;
    int i;
    int *p;     //price list
    
    int price_list[10] = {0,1,4,8,9,10,17,17,20,24}; //declare one more value to cover the index 0;
    
    n = sizeof(price_list) / sizeof(int) - 1;
    p = price_list;
    
    
    //allocate the memory array
    r = malloc(sizeof(int) * (n+1));
    
    
    //set all memory elements to -1
    for (i=0; i<=n; i++)
        r[i] = -1;
                
    printf("The maximun value is: %d \n", cr_bottom_up_dp_print(p,n));
}