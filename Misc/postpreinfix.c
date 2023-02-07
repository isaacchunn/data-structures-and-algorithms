//////////////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include <stdlib.h>
#include <string.h>

////////////////////////////////// Precedence Table ///////////////////////////////////////////

#define SIZE 10
char precedenceTable [SIZE] = {'*','/','%','+','-','<','>','&','=','\0'};

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

////////////////////////////////////////////////////////////////////////////////
void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);
void reversePrintListInt(ListNode * head);
void reversePrintListChar(ListNode * head);

//////////////////////////////////////////////////

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

///////////////////////////////////////////////////////////////

//Post-prefix algorithms
char* infixToPostfix (char* infix);
int evaluatePostFix(char * postfix);
int checkPrecedence(char c1, char c2);
int evaluate (int operand1, char operator, int operand2);

//////////////////////////////////////////////////////////////////
/////

int main()
{
    char * infix = "7 - ((3*4) + 8) / 5";
    char * tut4a= "x=a+b∗c%d>>e";
    char * tut4b= "= y&& << ab >> c + de";
    char * tut4c= "xabc ∗ d% + e >>=";
    char * postfix = infixToPostfix(infix);
    puts(postfix);
    printf("Result: %d\n", evaluatePostFix(postfix));
    //puts(infixToPostfix(tut4b));
    //puts(infixToPostfix(tut4c));
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

//////////////////////////////////////////////////////////////////////////////////

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

void reversePrintListInt(ListNode * head)
{
    if(head == NULL)
        return;

    int c = head->item;
    reversePrintListInt(head->next);
    //Then print all
    printf("%d ", head->item);
}

void reversePrintListChar(ListNode * head)
{
    if(head == NULL)
        return;

    char c = head->item;
    reversePrintListChar(head->next);
    //Then print all
    putchar(c);
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


//Post-preinfix, I hope the malloc works
char* infixToPostfix (char* infix)
{
    int len = strlen(infix);  
    char * postfix = malloc(len+2); // for the '\0' and '('
    int i, w = 0;
    char item;
   //Initialization of stack
    Stack s;
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;

    //Step 1: Add ‘)” to the end of the infix expression
    *(infix + len) = ')';
    *(infix + len + 1) = '\0';

    //Handle the transferring of characters
    //Initialize post fix
    for(i = 0; i < len + 2; i++)
    {
        *(postfix+i) = '\0';
    }

    //Step 2: Push “(“ on to the stack
    push(&s,'(');
    /*Step 3: Repeat until each character in the infix notation is scanned
        IF a “(“ is encountered, push it on the stack
        IF an operand (whether a digit or an alphabet) is encountered,  
        add it to the postfix expression.
        IF a “)” is encountered, then;
    . Repeatedly pop from stack and add it to the postfix expression until a “(” is encountered.
            b. Discard the “(“. That is, remove the “(“ from stack and do not
            add it to the postfix expression
        IF an operator X is encountered, then;
    Repeatedly pop from stack and add each operator (popped from the   stack) to the postfix expression which has the same precedence or a higher precedence than X
            b. Push the operator X to the stack*/
    char * r = infix;
    //Read through infix.
    while(*r != '\0')
    {
         //Ignore if space as we only want to evaluate the things that mater
        if(*r != ' ')
        {      
            //Check for braces
            if(*r == '(')
            {
                //Push on to the stack
                push(&s,'(');
            }
            else if (*r == ')')
            {
                while(peek(&s) != '(')
                {
                    //Else we add it to postfix
                    *(postfix + (w++)) = pop(&s);
                    //Add space to the post fix expression
                    *(postfix + (w++)) = ' ';
                }
                pop(&s);
            }
            else if((*r >= 48 && *r <= 57) || (*r >= 65 && *r <= 90) || (*r >= 97 && *r <= 122) || (*r == ' ')) //Operand 
            {
                //It's a number
                *(postfix + (w++)) = *r;
                //Add space to the post fix expression
                *(postfix + (w++)) = ' ';
            }
            else
            {
                //This is a operator X, so we handle it based on precedence
                // 
                while(!isEmptyStack(&s) && peek(&s) != '(' && checkPrecedence(peek(&s), *r))
                {
                    *(postfix + (w++)) = pop(&s);
                    //Add space to the post fix expression
                    *(postfix + (w++)) = ' ';   
                }
                //Push operator into stack
                push(&s, *r);
            }
        }     
        //printf("Postfix: %s | Stack:", postfix);
        //reversePrintList(s.ll.head);
        //putchar('\n');
        r++;
    }  
    /*Step 4: Repeatedly pop from the stack and add it to the postfix expression
            until the stack is empty*/
    while(!isEmptyStack(&s))
    {
        item = pop(&s);
        //Else we add it to postfix
        *(postfix + (w++)) = item;
        //Add space to the post fix expression
        //*(postfix + (w++)) = ' ';
    }
    //Handle the last char
    *(postfix + (w)) = '\0';
    //Step 5: EXIT
   return postfix;
}

int evaluatePostFix(char * postfix)
{
    //Step 1: Add ‘)” to the end of the infix expression
    int len = strlen(postfix);
    *(postfix + len) = ')';
    *(postfix + len + 1) = '\0';

    //Initialize stack
    Stack s;
    s.ll.head = NULL;
    s.ll.tail = NULL;
    s.ll.size = 0;

    char * r = postfix;
    int operand1, operand2, temp, result;
    /*
        Step 1: Add a “)” at the end of the postfix expression
        Step 2: Scan every character of the postfix expression and  repeat
                steps 3 and 4 until “)”is encountered

    */
    while(*r != '\0')
    {
        /*
        Step 3: IF an operand is encountered, push it on the stack
            IF an operator X is encountered, then
        a. pop the top two elements from the stack as A and B
            b. Evaluate B X A, where A was the topmost element and B was the element below A.
            c. Push the result of evaluation on the stack
        [END OF IF] 
        */
       if(*r != ' ')
       {
            //This is an operand
            if(*r >= 48 && *r <= 57) //Just numbers for now!
            {
                 //The value is *r - 48
                push(&s, (*r) - 48);
            }
            else
            {
                //It's an operator
                if(s.ll.size >= 2)
                {
                    operand1 = pop(&s);
                    operand2 = pop(&s);
                    temp = evaluate(operand2, *r, operand1);
                    push(&s, temp);
                    result = temp;
                }
            }
        }
        r++;
    }
    /*


        Step 4: SET RESULT equal to the topmost element of the stack
        Step 5: EXIT
    */

   return result;
}

//Check c1 against c2
int checkPrecedence(char c1, char c2)
{
    //Lower the number the higher the precedence
    int r1 = SIZE;
    int r2 = SIZE;
    int i;
    for(i = 0; i < SIZE; i++)
    {
        if(c1 == precedenceTable[i])
            r1 = i;
        if(c2 == precedenceTable[i])
            r2 = i;
    }
    return r1 <= r2;
}

int evaluate (int operand1, char operator, int operand2)
{
    switch (operator)
    {
        case '+':
        {
            return operand1 + operand2;
            break;
        }
        case '-':
        {
            return operand1 - operand2;
            break;
        }
        case '*':
        {
            return operand1 * operand2;
            break;
        }
        case '/':
        {
            return operand1 / operand2;
            break;
        }
        default:
        {
            break;
        }
    }
    return -1;
}