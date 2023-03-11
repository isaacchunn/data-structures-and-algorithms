#include <stdio.h>
#include <stdlib.h>

void quickSort(int A[], int low, int high);
int partition (int A[], int low, int high);

void dualSortedSearch (int[],int, int, int[]);

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

    quickSort(A,0,size-1);
    dualSortedSearch(A,size,K,index);

    if(index[0]!=-1)
        printf("Index : [%d,%d] / Numbers: [%d,%d]\n",index[0], index[1], A[index[0]], A[index[1]]);
    else
        printf("Not found");

    free(A);
    return 0;
}

void dualSortedSearch(int A[], int size, int K, int dualIndex[])
{
   //Use a two pointer pointer method
   int left =0;
   int right = size -1;
   int sum;
   //While right is still larger than left, if it fails then we have intersected and we have not found anything.
   while(left < right)
   {
        sum = A[left] + A[right];
        //Check the sum of the current left and right
        if(sum == K)
        {
            dualIndex[0] = left;
            dualIndex[1] = right;
            return;
        }
        else if (sum < K)
        {
            //if sum is less than k, we want to increment our left
            left++;
        }
        else
        {
            //Else if its bigger we lower right by 1
            right--;
        }
   }
}

int partition (int A[], int low, int high)
{
    int pivot = A[high];
    int i = (low - 1);

    int temp;
    for (int j = low; j <= high- 1; j++)
    {
        if (A[j] < pivot)
        {
            i++;

            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    temp = A[i+1];
    A[i+1]= A[high];
    A[high] = temp;
    return (i + 1);
}

void quickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(A, low, high);

        quickSort(A, low, pivot - 1);
        quickSort(A, pivot + 1, high);
    }
}
