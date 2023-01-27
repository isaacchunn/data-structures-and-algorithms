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
    //Edited to show result.
    
	if(palindrome(word1) == 0) //*word1="A man a plan a canal Panama";
        printf("%s was a palindrome.\n", word1);
    else
        printf("%s was not a palindrome.\n", word1);

    if(palindrome(word2) == 0) //*word2="Superman in the sky";
        printf("%s was a palindrome.\n", word2);
    else
        printf("%s was not a palindrome.\n", word2);

	//for question 4 return 1 to show not balanced...? why they do like that lol
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

void removeUntil(Stack *s, int value){

	// write your code here
    int item;
    //Given that we want to pop up to the value first
    //Check if s null or size 0, else no point checking
    if(s != NULL && s->ll.size == 0)
        return;
    
    //Else we pop until we find it
    while(!isEmptyStack(s))
    {
        //Peek the item first
        item = peek(s);
        if(item == value)
            break;
        //Else we continue popping
        pop(s);
    }
}

////////////////////////////////////////////////////////////
//Question 2

void recursiveReverse(Queue *q){

	// write your code here
	//If q is empty, then this is base case
	if(isEmptyQueue(q))
		return;
	
	//Store the current top item
	int item = dequeue(q);
	//Then continue calling the func into the call stack
	recursiveReverse(q);
	//Once empty, it goes all the way back, then we just queue everything better based on the call stack
	enqueue(q, item);
}

////////////////////////////////////////////////////////////
//Question 3

int palindrome(char *word){

	// write your code here
    //Push every letter in word to a stack and queue, then check if top of stack == top of queue.
    Stack s;
    Queue q;
    char * read = word;
    char c;
    //Initialization of values
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;
    
    q.ll.head = NULL;
    q.ll.tail = NULL;
    q.ll.size = 0;

    while(*read != '\0')
    {
        //Push and enqueue in to the stack and queue
        //In this case we are pushing in the char, but its okay cause it will just be casted as an int instead.
        //We are going to compare ascii values later using int.
        //Ignore the spaces
        if(*read != ' ')
        {
            c = *read;
            //Check if read is higher case, assuming the correct input is given
            //Alternatively can use ctype.h to do this
            if(c >= 65 && c <= 90)
                c+= 32;

            push(&s, c);
            enqueue(&q, c);
        }
        read++;
    }
    //Then we just compare top of stack with front of queue
    //The top of the stack should be equal to the first output of the queue.
    //Suppose a string is Banana
    //Then the stack is stored in ananaB
    //And the queue is stored as per normal Banana, but the first dequeued is at the front which is B.
    //One check should have been sufficient since they are same size
    while(!isEmptyStack(&s) && !isEmptyQueue(&q))
    {
        //Check if the pop and deuqeued elements are same, if not, return -1.
        if(pop(&s) != dequeue(&q))
            return -1;
    }
    //On here, it is a palindrome.
    return 0;
}

////////////////////////////////////////////////////////////
//Question 4
//Similar to https://leetcode.com/problems/valid-parentheses/
int balanced(char *expression){

	// write your code here
    //Create a stack
    Stack s;
	char * r = expression;
	char c;
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;

    //Loop through the expression
    while(*r != '\0')
	{
		//Check if it's an opening brace
		if(*r == '(' || *r == '[' || *r == '{')
		{
			//Then we should push into the stack
			push(&s, *r);
		}
		else
		{
			//Else its a closing brace either ), }, ]
			//If empty queue, we can return as we started with a closing bracket
			if(isEmptyStack(&s))
				return -1;

			//Else we pop the stack to see top and if its a valid closing
			c = pop(&s);
			
			//Check if theres a proper closing, else we have incorrectly closed and its not balanced.
			if(*r == ')' && c != '(')
				return 1;
			else if (*r == ']' && c != '[')
				return 1;
			else if (*r == '}' && c != '{')
				return 1;
		}
		r++;
	}
	//This means its balanced.
	return 0;
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