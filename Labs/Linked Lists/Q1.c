/*
Implement the removeNode() function for a linked list, using the lecture diagrams and
pseudo-code as a reference. The prototype for the removeNode() function is given below:

int removeNode(ListNode **ptrHead, int index);

The function should return 0 if the delete operation is successful and -1 otherwise. Recall that
the function requires a pointer to the head pointer in order to correctly delete the first node.

Write a program to test the removeNode() function. It should first allow the user to create a
linked list of integers by appending values to the end of the list. Next, it should allow the user to
delete nodes one by one based on their indices.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;

void printList(ListNode *cur);
ListNode * findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
int removeNode(ListNode **ptrHead,int index);

int main()
{
    //Static variable of list
    ListNode *head=NULL;
    //Storing of size
    int size =0;
    int item;
    int index;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head,size, item)) size++;
    scanf("%*s");
    //Prints the list after user has stopped trying to append inside
    printList(head);
    
    while(size > 0){
        printf("Enter the index of the node to be removed: ");
        scanf("%d",&index);

        if(removeNode(&head,index))
            size--;
        else{
            printf("The node cannot be removed.\n");
            break;
        }

        printf("After the removal operation,\n");
        printList(head);
    }
    printf("There are no more nodes in the linked list.,\n");
    //Prints the list if the current node cannot be removed.
    printList(head);
    return 0;
}

/******************************************************************************/
/*!
\brief
Prints the list starting from curr.
\param cur node to start printing the linked list from
\exception None
*/
/******************************************************************************/
void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

/******************************************************************************/
/*!
\brief
Linearly traverses through the linked list to acquire the node at index (if applicable).
\param cur node to start searching from
\param index index in which the node should be returned
\exception None
\return cur
*/
/******************************************************************************/
ListNode *findNode(ListNode* cur, int index)
{
    //Starting checks
    if (cur == NULL || index < 0)
        return NULL;
    
    while(index > 0){
        cur = cur->next;
        if (cur == NULL)
            return NULL;
        index--;
   }
   return cur;
}

/******************************************************************************/
/*!
\brief
Attempts to insert a node at index with value of item
\param ptrHead - pointer to head of LL
\param index - index at which to add our node into the LL
\exception None
\return 1 if successfully removed, 0 if not successful
*/
/******************************************************************************/
int insertNode(ListNode **ptrHead, int index, int item){

    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0)
    {
        //Dynamically allocate a new node
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        //Update the new head with this new node as it is the first in the LL
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index-1)) != NULL)
    {
        //Dynamically allocate a new node
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;   
        //Set the new node's next to the current pre next as we are inserting after pre
        newNode->next = pre->next;
        //Then set pre next to newNode as it is behind new Node now
        pre->next = newNode;
        return 1;
    }
    return 0;
}

/******************************************************************************/
/*!
\brief
Removes a node in the LL at index
\param ptrHead - pointer to head of LL
\param index - index at which to remove our node from the LL
\exception None
\return 1 if successfully removed, 0 if not successful
*/
/******************************************************************************/
int removeNode(ListNode **ptrHead, int index)
{
    //Check if head is already null, we can return straight 0
    if(*ptrHead == NULL)
        return 0;

    /* Write your program code here */
    //Set curr to be ptrhead
    ListNode *curr;
    ListNode * pre, *nodeToRemove;
    //Check if the index is 0 first, this means we are attempting to remove the head, so we should update the head accordingly
    if(index == 0)
    {
        curr = *ptrHead;
        *ptrHead = (*ptrHead)->next;
        //Then we free curr
        free(curr);
        return 1;
    }
    //Else we just attempt to find the node at that index
    else if((nodeToRemove = findNode(*ptrHead, index)) != NULL)
    {
        //If we found the node to remove, we then find the node at the previous index as it is not a doubly linked list
        //Check if pre exists,
        if((pre = findNode(*ptrHead, index -1)) != NULL)
        {
            //Set pre-> next to be nodeToRemove's next
            pre->next = nodeToRemove->next;
            //Then we free the nodeToRemove
            free(nodeToRemove);
            //Return 1 for successful remove
            return 1;
        }
    }
    return 0;
}