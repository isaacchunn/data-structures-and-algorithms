#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
    ListNode *head;
    int size;
} LinkedList;

//GIVEN FUNCTIONS
void printList2(LinkedList ll);
ListNode* findNode2(LinkedList ll, int index);
int insertNode2(LinkedList *ll, int index, int item);
//TO DO
int removeNode2(LinkedList *ll,int index);

int main()
{
    //Initiialisation of the linked list struct
    LinkedList ll;
    //Simple assigning of main linked list struct variables
    ll.head = NULL;
    ll.size = 0;
    int item;
    int index;

    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(!insertNode2(&ll,ll.size, item)) break;
    }
    //Clears input buffer?
    scanf("%*s");
    //Prints the list once
    printList2(ll);

    while(1){
        printf("Enter the index of the node to be removed: ");
        scanf("%d",&index);

        //Attempts to remove the node at that index
        if(!removeNode2(&ll,index)){
            printf("The node cannot be removed.\n");
            break;
        }
        //If successful, it goes to here
        printf("After the removal operation,\n");
        printList2(ll);
    }
    //Print the list one more time
    printList2(ll);
    return 0;
}

void printList2(LinkedList ll){
    if(ll.head != NULL){
        ListNode *cur = ll.head;
        printf("Current List has %d elements: ",ll.size);

        while (cur != NULL){
            printf("%d ", cur->item);
            cur = cur->next;
        }
        printf("\n");
    }
}

ListNode* findNode2(LinkedList ll, int index)
{
   if(ll.head != NULL){
        ListNode *cur = ll.head;
        if (cur==NULL || index<0 || index >ll.size)
           return NULL;

        while(index>0){
            cur=cur->next;
            if (cur==NULL)
                return NULL;
            index--;
        }
        return cur;
   }
   else
     return NULL;
}

int insertNode2(LinkedList *ll, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = ll->head;

        ll->head = newNode;
        ll->size++;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode2(*ll, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        ll->size++;
        return 1;
    }
    return 0;
}

int removeNode2(LinkedList *ll,int index)
{
    /* Write your program code here */
    //Same implemention of the previous
    //First we check if the head of ll is null, we can return straight as the linked list *head has not been initialized yet
    //Or if given index is more than ll's size, then we also return as we cant remove a node there
    if(ll->head == NULL || index > ll->size - 1)
        return 0;

    ListNode * pre, *curr;
    //Else check if index is 0 which means we are removing the first node
    if(index == 0)
    {
        //Set curr to be head
        curr = ll->head;
        ll->head = ll->head->next;
        //Call free on head
        free(curr);
        //Set head to be head's next
        //Decrement ll size
        ll->size--;
        return 1;
    }
    else if((pre = findNode2(*ll, index -1)) != NULL)
    {
        if(pre->next != NULL)
        {
            curr = pre->next;
            //We have to set pre to be next's next
            pre->next = pre->next->next;
            //Free pre->next
            free(curr);
            //Decrement ll size
            ll->size--;
            return 1;
        }    
    }
    return 0;
}
