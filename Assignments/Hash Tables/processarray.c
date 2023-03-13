#include <stdlib.h>
#include <stdio.h>

int ProcessArray(int * listA, int x, int n)
{
    int i,j,k;
    i = 0;
    j = n - 1;
    do
    {
        k = (i+j)/2;
        if(x <= listA[k])
            j = k-1;
        if (listA[k] <=x)
            i = k+1;
    } while (i <= j);

    if (listA[k] == x)
        return k;
    else   
        return -1;
}

void main (void)
{
    int listA[8] = {1,2,3,4,6,7,9,10};

    printf("%d",ProcessArray(listA, 7, 10));

}