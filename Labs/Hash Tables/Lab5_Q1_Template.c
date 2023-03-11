#include <stdio.h>
#include <stdlib.h>

void dualSearch (int[],int, int, int[]);

int main()
{
    int i,size,K;
    int* A;
    int index[2] = {-1,-1};

    //Search key
    printf("Enter key: ");
    scanf("%d",&K);
    printf("%d \n", K);

    //create an array
    scanf("%d",&size);
    A=(int *)malloc(sizeof(int)*size);
    for(i=0; i<size; i++)
    {
        scanf("%d",&A[i]);
    }

    dualSearch(A,size,K,index);

    if(index[0]!=-1)
        printf("Index : [%d,%d] / Numbers: [%d,%d]\n",index[0], index[1], A[index[0]], A[index[1]]);
    else
        printf("Not found");

    free(A);
    return 0;
}

/// @brief  Find two elements in the array such that their sum is equal to K. The two elements can be the same element. Once a pair of elements is found, the program can be terminated.
/// @param A array
/// @param size size of array
/// @param K target sum
/// @param dualIndex return an array of the two indexes
void dualSearch(int A[], int size, int K, int dualIndex[])
{
   //The simplest way is to do a nested for loop that does not check all the elements again for those that have been checked.
   //Acquire all potential pairs.
   int i, j;
   for (i = 0; i < size; i++)
   {
        for(j = i + 1; j < size; j++)
        {
            //Check if the sum equals K
            if(A[i] + A[j] == K)
            {
                dualIndex[0] = i;
                dualIndex[1] = j;
                //Then we can return
                return;
            }
        }
   }
}
