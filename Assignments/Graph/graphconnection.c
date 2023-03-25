#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list; //adjacency list implementation, so we cannot just do adjacency matrix checking.
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;

int CC (Graph g);

void printGraphList(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
    Graph g;
    int i,j;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));

    for(i=0;i<g.V;i++)
        g.list[i] = NULL;

    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&i,&j)==2)
    {
        i=i-1;

        if(g.list[i]==NULL){
            g.list[i] = (ListNode *)malloc(sizeof(ListNode));
            g.list[i]->vertex = j;
            g.list[i]->next = NULL;
        }
        else{
            temp = (ListNode *)malloc(sizeof(ListNode));
            temp->next = g.list[i];
            temp->vertex = j;
            g.list[i] = temp;
        }
        g.E++;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");

    int res = CC(g);
    if(res ==1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    printGraphList(g);
    return 0;
}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}

/// @brief Function that checks if a graph is strongly connected
/// @param g graph
/// @return 1 if strongly connected, 0 otherwise.
int CC (Graph g)
{
    //A directed graph is strongly connected if there is a path from any vertex to any other vertex.
    //We have to loop through all the nodes, conduct dfs, and then check if all the nodes has been visited for every array.
    //Create a stack s for our DFS
    Stack s;
    ListNode * currentNode;
    int i, u, currVertex, connected, adjacentVertex;
    int * visited;

    //If the number of vertices are 0, the graph is automatically strongly connected
    if(g.V == 0)
        return 1;

    //Initialize the stack
    s.head = NULL;
    s.size = 0;

    //Initialize our visited array
    visited = (int *)calloc(g.V, sizeof(int));
    
    //For the number of vertices in g, we have to conduct DFS on all of them.
    //Starting from vertex 1
    for (i = 1; i <= g.V; i++)
    {
        //Empty all items from stack first
        removeAllItemsFromStack(&s);
        //This is our DFS function. -----
        //Then push i into s, where i is the current vertex we are checking
        push(&s, i);
        //Update this vertex to be visited
        visited[i - 1] = 1;
        //printf("%d ->", i);  
        while(!isEmptyStack(s))
        {
            //Peek the stack, since we are doing a greedy strategy
            currVertex = peek(s);
            //Get the current node based on the curr Vertex
            currentNode = g.list[currVertex - 1];
            //Set the adjacent vertex
            adjacentVertex = 0;

            //The starting node of this vertex has no links to other places, just stop it here as it can never be strongly connected.
            if(currentNode == NULL)
                return 0;

            while(currentNode != NULL)
            {
                if(visited[currentNode->vertex - 1] == 0)
                {
                    //Set this node to be be visited
                    visited[currentNode->vertex - 1] = 1;
                    //Push into the stack this vertex that is unvisited
                    push(&s, currentNode->vertex);
                    //Update adj vertex to show we have pushed something
                    adjacentVertex = 1;
                    //printf("%d ->", currentNode->vertex); //UNCOMMENT FOR THE NORMAL WAY OF TRAVERSING
                }
                currentNode = currentNode->next;
            }
            //If this has no more other adj unvisited vertexes, then we pop it out.
            if(adjacentVertex == 0)
            {
                pop(&s);
            }
        }
        //END DFS ---------

        //For loop check to see if all the nodes are visited
        connected = 1;
        for (u =0; u < g.V; u++)
        {
            //If any of the nodes are not visited, means we do not have a strongly connected graph
            if(visited[u] == 0)
                connected = 0;
            
            //Then just reset the rest
            visited[u] = 0;
        }
        //If not connected, we can return. I did this to save two linear loops to check and reset.
        if(!connected)
            return 0;
        //Go to next repetition      
    }
    //Return 1 by default that the graph is strongly connected.
    return 1;
}
