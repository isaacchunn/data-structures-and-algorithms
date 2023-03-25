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
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

void DFS_I (Graph , int );

int main()
{
    Graph g;
    int i,j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    scanf("%*c");
    printf("Enter a start vertex for DFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    DFS_I(g,i);

    return 0;
}

/// @brief Performs depth first search and prints the search order
/// @param g graph
/// @param v vertex to start
void DFS_I (Graph g, int v)
{
    //Create a stack s
    Stack s;
    int w, u;
    int * visited;
    int adjacentVertex = 0;

    //If the number of vertices are 0
    if(g.V == 0)
        return;

    //Initialize the stack
    s.head = NULL;
    s.size = 0;

    //Initialize the visited array
    visited = calloc(g.V, sizeof(int));
    //Then push v into s
    push(&s, v);
    visited[v - 1] = 1;
    //printf("%d ->", v);           //UNCOMMENT FOR THE NORMAL WAY
    while(!isEmptyStack(s))
    {
        //Peek the stack, since we are doing a greedy strategy
        w = peek(s);
        adjacentVertex = 0;
        //Find all unvisited vertex to w
        for (u = 0; u< g.V; u++)
        {
            //If theres a link to from this node to another node, and not visited yet
            if(g.matrix[w-1][u] == 1 && visited[u] == 0)
            {
                //We want to push this unvisited vertex u adjacent to w and mark as visited
                push(&s, u + 1);
                visited[u] = 1;
                //Set that we have pushed something
                adjacentVertex = 1;
                //We break as we are trying to be greedy, we want to push the first known unvisited vertex
                //printf("%d ->", u + 1); //UNCOMMENT FOR THE NORMAL WAY OF TRAVERSING
                break;
            }
        }
        //Then check if we have pushed something over here
        if(adjacentVertex == 0)
        {
            //If it is 0, there are no unvisited adjacent vertexes  
            printf("%d -> ", peek(s)); // THIS IS TO GET THE OUTPUT STATED IN THE LAB SHEET, BUT IDK IF CORRECT.
            pop(&s);     
        }
    }
    putchar('\n');
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

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
