
#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;


void printList(ListNode *cur);
ListNode * findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
void deleteList(ListNode **ptrHead);

int split(ListNode *cur,ListNode **ptrEvenList,ListNode **ptrOddList);

int main()
{
    ListNode *head=NULL;
    ListNode *oddHead = NULL;
    ListNode *evenHead = NULL;

    int size =0;
    int item;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        if(insertNode(&head,size, item)) size++;
    scanf("%*s");

    printf("\nBefore split() is called:\n");
    printf("The original list:\n");
    printList(head);

    split(head, &evenHead, &oddHead);

    printf("\nAfter split() was called:\n");
    printf("The original list:\n");
    printList(head);
	printf("The even list:\n");
	printList(evenHead);
	printf("The odd list:\n");
	printList(oddHead);

	if(head!=NULL)
       deleteList(&head);
    if(oddHead!=NULL)
       deleteList(&oddHead);
    if(evenHead!=NULL)
       deleteList(&evenHead);
    return 0;
}

void printList(ListNode *cur){
    printf("Current List: ");
    while (cur != NULL){
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode(ListNode* cur, int index)
{
   if (cur==NULL || index<0)
      return NULL;
   while(index>0){
      cur=cur->next;
      if (cur==NULL)
         return NULL;
      index--;
   }
   return cur;
}

int insertNode(ListNode **ptrHead, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode(*ptrHead, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        return 1;
    }
    return 0;
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

/// @brief Copies the content of a linked list into two other linked lists.
/// @param cur head of linked list
/// @param ptrEvenList even list
/// @param ptrOddList odd list
/// @return 1 if successful, 0 if unsuccessful
int split(ListNode *cur, ListNode **ptrEvenList,ListNode **ptrOddList)
{
    //Variable declaration
    ListNode * curr;
    int indice = 0, evenSize = 0, oddSize = 0;
    //Sanity check
    if(cur == NULL)
        return 0;
    //Variable initialization
    curr = cur;
    while(curr != NULL)
    {
        if(indice % 2 == 0)
        {
            //Even
            insertNode(ptrEvenList,evenSize++,curr->item);
        }
        else
        {
            //Odd
            insertNode(ptrOddList,oddSize++,curr->item);
        }
        indice++;
        curr = curr->next;
    }
    return 1;
}