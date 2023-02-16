//////////////////////////////////////////////////////////////////////////////////

/* SC1007: Data Structures and Algorithms
Assignment 1 - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function

int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
/// @brief Inserts an item into the linked list in ascending order (preventing duplicates)
/// @param ll linked list
/// @param item item to add
/// @return -1 if function not completed successfully, else returns index of item added
int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
    //A traversal is always necessary to check if there exists an item
    //However, if we have went above a certain number without getting an instance, then the number must not exist
    //Based on the assumption that it is always sorted or empty.
    //So we loop through the ll first
    ListNode * curr, *newNode, *pre;
    int index = 0;

	//Sanity checks
	if(ll == NULL)
		return -1;

    //Check that head is NULL or the current head item is more than the item to be added
    if(ll->head == NULL || ll->head->item > item)
    {
        //Then new node is malloced and inserted in.
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = ll->head;
        ll->head = newNode;
        //Increment size
        ll->size++;
        //This is the index in which we return where it is added
        return 0;
    }
    
    //If not, we do normal traversal to find the place to add
    curr = ll->head;
    //Else we start from the head and continue the traversal
    while(curr != NULL)
    {
        //Else we start comparing from the head onwards (first repetition)
        if(curr->item == item)
            return -1;

        //Once our current item has become bigger than item, then we insert before this and update the links accordingly
        if(curr->item > item)
        {
            //Create a node
            newNode = malloc(sizeof(ListNode));
            newNode->item = item;
            //Update the links
            //Should update pre next to be next node
            pre->next = newNode;
            //Update newNodes next to curr, basically inserting new node in between...
            newNode->next = curr;
            //Increment size.
            ll->size++;
            return index;
        }  
        //Update pre
        pre = curr;
        //Traverse the list
        curr = curr->next;
        //Increment index
        index++;
    }

    //If at the end of the loop, nothing was returned or added, then we must just add it at the back
    //Create a node
    newNode = malloc(sizeof(ListNode));
    newNode->item = item;
    pre->next = newNode;
    newNode->next = NULL;
    //Increment the size once again
    ll->size++;

    return index;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}