//////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include <stdlib.h>

//////////////////////////////////   linked list //////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
	int size;
	ListNode *head;
	ListNode *tail;
} LinkedList;

////////////////////////////////// stack    //////////////////////////////////////////////
typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////////////////// queue ////////////////////////////////////////////

typedef struct _queue{
	LinkedList ll;
} Queue;

////////////////////////////////////////////////////////////////////////////////
void printList(ListNode *head);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////////////////////////////

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

//////////////////////////////////////////////////

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *s);

///////////////////////////////////////////////////////////////
// four questions
void removeUntil(Stack *s, int value);
void recursiveReverse(Queue *q);
int palindrome(char *word);
int balanced(char *expression);

//////////////////////////////////////////////////////////////////
/////

int main()
{
	Stack s;
	Queue q;
	int item[] = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };
	int i;
	char *word1 = "A man a plan a canal Panama";
	char *word2 = "Superman in the sky";

	//for question 1
	//initialize the stack
	s.ll.head = NULL;
	s.ll.size = 0;
	s.ll.tail = NULL;

	for (i = 0; i<11; i++)
		push(&s, item[i]);

	printList(s.ll.head);
	removeUntil(&s, 5);
	printList(s.ll.head);

	//for question 2
	//initialize the queue
	q.ll.head = NULL;
	q.ll.size = 0;
	q.ll.tail = NULL;

	for (i = 0; i<10; i++)
		enqueue(&q, i);
	printList(q.ll.head);
	recursiveReverse(&q);
	printList(q.ll.head);

	//for question 3
	palindrome(word1); //*word1="A man a plan a canal Panama";
	palindrome(word2);// *word2="Superman in the sky";


	//for question 4
	if (balanced("()")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	if (balanced("[()]")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	if (balanced("{[]()[]}")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	if (balanced("[({{)])")) printf("not balanced!\n");
	else
		printf("balanced!\n");

	return 0;
}

////////////////////////////////////////////////////////////////
//Question 1

/// @brief Pops all values off a stack of integers down to but not including the first occurence of the chosen value
/// @param s stack
/// @param value value to remove till
void removeUntil(Stack *s, int value){
    //Variable declaration
    int item;
    //Sanity check
    if(s == NULL)
        return;
    
    //While isnt empty
    while(!isEmptyStack(s))
    {
        item = peek(s);
        if(item == value)
            return;
        pop(s);
    }
}

////////////////////////////////////////////////////////////
//Question 2

/// @brief Reverses the order of items stored in a queue of integers.
/// @param q 
void recursiveReverse(Queue *q){

    int item;
    //Sanity check
    if(q == NULL || isEmptyQueue(q))
        return;
    
    //Else we set item to be dequeued item
    item = dequeue(q);
    recursiveReverse(q);
    //Then enqueue back based on call stack
    enqueue(q,item);
}

////////////////////////////////////////////////////////////
//Question 3

/// @brief Determines whether a given string is a palindrome.
/// @param word 
/// @return 0 if the string is a palindrome and -1 otherwise
int palindrome(char *word){

	if(word == NULL)
		return -1;
	//Variable declaration
    Stack s;
    Queue q;
    char * it = word;
    char c;
    int size, i;
    //Initialize both stack and queue
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;
    //Initialize queue
    q.ll.head = NULL;
    q.ll.tail = NULL;
    q.ll.size = 0;

    //Traverse the string
    while(*it != '\0')
    {
        //Want to ignore spaces...
        if(*it != ' ')
        {
            //Temp character
            c = *it;
            //Check if lower case
            if(c>= 65 && c <= 90)
                c+=32;
            
            //push and enqueue into stack and queue
            push(&s, c);
            enqueue(&q, c);
        }
        it++;
    }
    
    //Do half!
    size = s.ll.size /2;
    //Do a for loop
    for( i= 0; i < size; i++)
    {
        if(pop(&s) != dequeue(&q))
        {
            printf("%s was not a palindrome.\n", word);
            return -1;
        }

    }
    printf("%s was a palindrome.\n", word);
    return 0;
}



////////////////////////////////////////////////////////////
//Question 4

/// @brief Checks if the expression is balanced
/// @param expression expression
/// @return return 0 if not balanced, 1 otherwise.
int balanced(char *expression){

    //Variable declaration
    Stack s;
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;
    char c;

    while(*expression != '\0')
    {
        //Check if its opening brace
        if(*expression == '(' || *expression == '{' || *expression == '[')
        {
            //push current into stack
            push(&s, *expression);
        }
        else
        {
            //It's a closing bracket then we check
            c = peek(&s);
            //Check for all the cases
            if(c == '(' && *expression == ')')
                pop(&s);
            else if(c == '{' && *expression == '}')
                pop(&s);
            else if(c == '[' && *expression == ']')
                pop(&s);
            else
                return -1;
        }
        expression++;
    }
    //If stack still has elements, was not closed properly
    return !isEmptyStack(&s);
}

////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
	int item;

	item = ((s->ll).head)->item;
	removeNode(&(s->ll), 0);
	return item;
}

int peek(Stack *s){
	return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
	if ((s->ll).size == 0)
		return 1;
	return 0;
}


////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item){
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q){
	int item;
	item = ((q->ll).head)->item;
	removeNode(&(q->ll), 0);
	return item;
}

int isEmptyQueue(Queue *q){
	if ((q->ll).size == 0)
		return 1;
	return 0;
}



////////////////////////////////////////////////////////////////////////////////

void printList(ListNode *head){

	ListNode *temp = head;

	if (temp == NULL)
		return;

	while (temp != NULL){
		printf("%d ", temp->item);
		temp = temp->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

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

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->tail = ll->head;
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Inserting as new last node
	if (index == ll->size){
		pre = ll->tail;
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		ll->tail = pre->next;
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));

		if (index == ll->size)
			ll->tail = pre->next;

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

		if (ll->size == 0)
			ll->tail = 0;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		// Removing the last node, update the tail pointer
		if (index == ll->size - 1){
			ll->tail = pre;
			free(pre->next);
			pre->next = NULL;
		}
		else{
			cur = pre->next->next;
			free(pre->next);
			pre->next = cur;
		}
		ll->size--;
		return 0;
	}

	return -1;
}