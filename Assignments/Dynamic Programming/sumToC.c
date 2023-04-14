#include <stdio.h>
#include <stdlib.h>

typedef struct _arraynode
{
    int *itemArray;
    int sizeArray;
    struct _arraynode *next;
}ArrayNode;

typedef struct _arraylist{
   int size; //the size of a possible sequence
   ArrayNode *head;
} ArrayList;

typedef struct _listnode
{
    int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int sum; //the number of possible sequences
   int size;
   ListNode *head;
} LinkedList;

// You should not change the prototypes of these functions
//////LinkedList///////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int coin);
int removeNode(LinkedList *ll, int index);
ListNode *findNode(LinkedList ll, int index);
void removeAllItems(LinkedList *ll);
///////////////////////////////////////////////////

void sumToC(LinkedList* ll, int C, ArrayList* al);
int main()
{
    int C;
    printf("Enter a number:\n");
    scanf("%d",&C);

    LinkedList ll;
    ll.head = NULL;
    ll.sum = 0;
    ll.size = 0;
    ArrayList al;
    al.head = NULL;
    al.size = 0;

    sumToC(&ll,C,&al);
    ArrayNode* temp;
    int i,j;
    temp = al.head;
    for(i=0;i<al.size;i++){
        for(j=0;j<temp->sizeArray;j++)
            printf(" %d ",temp->itemArray[j]);
        printf("\n");
        temp = temp->next;
    }

    return 0;
}

///////////////////////////////////////////////////////
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

        if (index == 0){
		cur = ll->head;
		ll->head = (ListNode*) malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->sum += value;
		ll->size++;
		return 1;
	}

	return 0;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index > ll->size)
		return 0;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		ll->sum -= ll->head->item;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 1;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(*ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return 0;

		cur = pre->next;
		ll->sum -= cur->item;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 1;
	}

	return 0;
}

ListNode *findNode(LinkedList ll, int index){

	ListNode *temp;

	if (index < 0 || index >= ll.size)
		return NULL;

	temp = ll.head;

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
	ll->sum =0;
}

void printList(LinkedList * ll)
{
    ListNode * cur = ll->head;
    while (cur != NULL){
        printf("%d ->",cur->item);
		cur = cur->next;
	}
    printf(" | Sum: %d", ll->sum);
    putchar('\n');
}

///Let C be 6, then the output will be
// 1 2 3
// 1 5
// 2 4
// 6
/// @brief Prints all possible sequences in ascending positive integers that are summed to give a positive integer C where C < 50
/// @param ll linked list
/// @param C C value
/// @param al array list
void sumToC(LinkedList* ll, int C, ArrayList* al)
{
    //So far, we know that there cannot be duplicate numbers.
    //We have to store our results in array list using some dynamic programming based approach
    //We also use our linked list and list nodes to find a sequence.
    int i,j; //only loop up to C
    int prev;
    ListNode * curr;
    ArrayNode * newNode;
    ArrayNode * arrayCurr;
    
    //That means we overshot, and we have to return so that we can delete this node and carry on
    if(C < 0)
        return;

    //check the case where we reach the number nicely.
    if(C == 0)
    {
        //We found our solution
        //Make our new Node
        newNode = malloc(sizeof(ArrayNode));
        newNode->next = NULL;
        //Generate our other items based on our linked list size
        newNode->sizeArray = ll->size;
        //Make our item array
        newNode->itemArray = malloc(newNode->sizeArray * sizeof(int));
        
        j = 0;
        //Set our start of traversal
        curr = ll->head;
        //Append each item into our array list
        while(curr != NULL)
        {
            newNode->itemArray[j++] = curr->item;
            curr = curr->next;
        }
        
        //Update our array list
        if(al->head == NULL)
        {
            //Set this node to be head
            newNode->next = al->head;
            al->head = newNode;
        }
        else
        {       
            //Else, the arraylist has a head
            arrayCurr = al->head;
            //Then append this to the tail? So inefficient...
            while(arrayCurr != NULL && arrayCurr->next != NULL)
            {
                arrayCurr = arrayCurr->next;
            }
            arrayCurr->next = newNode;
        }
        //Increment our size of al
        al->size++;
        return;
    }

    prev = 1;
    //Go to the end of the linked lsit to find the value if head is not null
    if(ll->head != NULL)
    {
        curr = ll->head;
        while(curr->next != NULL)
        {
            curr = curr->next;
        }
        //+1 so we can start from a fresh index
        prev = curr->item + 1;
    }
    //Calculate all permutations from current + 1 minimum.
    for(i = prev; i <= C; i++)
    {      
        //Prevent further loops
        if(C - i < 0)
            break;
        //Add into the ll the current node
        insertNode(ll, ll->size, i);
        //Call our sum to c again, with our reduced C
        sumToC(ll,C - i, al);
        //Thern remove node like the same backtracking as n queens
        removeNode(ll, ll->size - 1);
    }
}
