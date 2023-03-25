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
    ListNode **list;  //adjacency list implementation
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int BFS (Graph G, int v, int w);

void printGraphList(Graph );

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
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    //Initialization of graph list.
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
    printf("Enter two vertices for finding their shortest distance:\n");
    scanf("%d %d", &i, &j);
    int d = BFS(g,i,j);
	
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
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

void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc( sizeof(QueueNode));
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

/// @brief Finds the shortest distance from vertex v to vertex w in a directed graph
/// @param g graph
/// @param v initial vertex
/// @param w destination vertex 
/// @return shortest distance measured by number of edges.
int BFS (Graph g, int v, int w){
   //Create a queue for breadth first search.
    Queue q;
    ListNode * currentNode;
    int i, currVertex, distance;
    //Store visited nodes and the path cost so far
    int * visited, * pathCost;

    //If both vertices are the same, then the distance is 0
    if(v == w)
        return 0;
    
    //Since its an adjacency list, if this node is NULL, then theres no outgoing list from our start node, so we can return
    if(g.list[v-1] == NULL)
        return -1;

    //Initialize our queue
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    //Malloc the visited array
    visited = (int *)calloc(g.V, sizeof(int));
    //Make a distance array to store the edges (idea from SC1015 to calculate path costs)
    pathCost = (int*)calloc(g.V, sizeof(int));

    //Mark the current vertex as visited
    visited[v-1] = 1;
    //Mark the path cost to the current vertex 0.
    pathCost[v-1] = 0;

    //Enqueue the first vertex which is v
    enqueue(&q, v);

    //This does not mean that we have visited all the nodes! Only for directed graph though
    while(!isEmptyQueue(q))
    {
        //Store the index of this curr vertex
        currVertex = getFront(q);
        //Get the current node based on the front vertex
        currentNode = g.list[currVertex - 1];
        //Then we can dequeue our queue.
        dequeue(&q);

        //This means that there are no outgoing links.
        if(currentNode == NULL)
            continue;
        
        //Loop through the links at this node
        while(currentNode != NULL)
        {
            //If this node has not been visited yet
            if(visited[currentNode->vertex - 1] == 0)
            {
                //Set this node to be visited
                visited[currentNode->vertex - 1] = 1;
                //Update the path cost (+1 as we are counting edges, can be changed to any other weight)
                pathCost[currentNode->vertex - 1] = pathCost[currVertex - 1] + 1;

                //If the current node is found and is equals to w, then we can return the distance calculated so far.
                if(currentNode->vertex == w)
                {
                    distance = pathCost[currentNode->vertex - 1];
                    //Free the visited and path cost arrays
                    free(visited);
                    free(pathCost);
                    //Return distance
                    return distance;
                }
                //Else we can enqueue this node as we have not found the resultant node yet.
                enqueue(&q, currentNode->vertex);
            }
            //And then go to next node in this link
            currentNode = currentNode->next;
        }
    }

    //Node was not found.
    free(visited);
    free(pathCost);
    return -1;
}

