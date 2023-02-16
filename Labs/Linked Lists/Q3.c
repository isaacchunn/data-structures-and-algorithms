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

/// @brief Copies the contents of the linked list and stores even values into evenlist, odd values into oddlist
/// @param cur head of linked list
/// @param ptrEvenList linked lsit to store even values
/// @param ptrOddList linked lsit to store odd values
/// @return 1.
int split(ListNode *cur, ListNode **ptrEvenList,ListNode **ptrOddList)
{
    /* Write your program code here. */
    //Loop through the main, and then when we encounter an odd or even, we malloc and add it to the oddList
    int indice = 0;
    int oddIndex = 0;
    int evenIndex = 0;
    while(cur)
    {
        if(indice % 2 == 0)
        {
            //Even
            insertNode(ptrEvenList,evenIndex,cur->item);
            evenIndex++;
        }
        else
        {
            //Odd
            insertNode(ptrOddList,oddIndex,cur->item);
            oddIndex++;
        }
        //Check current value if it's even or odd
        //Update curr and indices
        cur = cur->next;
        indice++;
    }
    return 1;
}