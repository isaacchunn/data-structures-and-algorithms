#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

void BFS (Graph G, int v);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

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

    g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0;

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
    printf("Enter a start vertex for BFS:\n");
    scanf("%d", &i);
    printGraphMatrix(g);
    BFS(g,i);

    return 0;
}

/// @brief Does breadth first search and prints the order of visiting of visiting.
/// @param g graph
/// @param v vertice to start
void BFS(Graph g, int v){
    //Create a Queue
    Queue q;
    int i, w;
    //Initialization of variables
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;
    
    //Reset visited as we want to keep using this functions
    for(i = 0; i < g.V; i++)
    {
        g.visited[i] = 0;
    }

    //Enqueue first vertex
    enqueue(&q, v);
    //Mark v as visited
    g.visited[v - 1] = 1;
    //Print the current vertex for w
    printf("%d -> ", v);
    //This does not mean that you have visited all the nodes! Only for directed graph though.
    while(!isEmptyQueue(q))
    {
        //Dequeue a vertex noted as w
        w = dequeue(&q);

        //Then for each vertex adjacent to w (loop through the adj matrix!)
        for(i = 0; i < g.V; i++)
        {
            //Loop through entire row and check the adj matrix for neighbours that are not visited.
            //We use w as the matrix row index, looping like that ensures first found in ascending order.
            if(g.matrix[w-1][i] == 1 && g.visited[i] == 0)
            {    
                printf("%d -> ", i + 1);
                //If its adj, and vertex still not visited.
                g.visited[i] = 1;
                enqueue(&q, i + 1);
            }
        }
    }
    putchar('\n');
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d ",g.matrix[i][j]);
        printf("\n");
    }

}


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
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
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
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
