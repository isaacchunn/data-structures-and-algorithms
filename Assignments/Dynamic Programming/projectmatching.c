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
 int * visited;
 int ** matrix;
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

void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
int matching(Graph g);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

/// @brief Returns min value of two int
/// @param a a
/// @param b b
/// @return min value of two int
int minV(int a, int b)
{
    return (a>b)? b:a; 
}

/// @brief Returns max value of two int
/// @param a a
/// @param b b
/// @return max value of two int
int maxV(int a, int b)
{
    return (a>b)? a:b;
}

/// @brief Copies all content from g to g2 (for residual graph)
/// @param g graph 1
/// @param g2 destination graph
void duplicateGraph(Graph g, Graph *g2)
{
    int i, j;
    g2->E = g.E;
    g2->V = g.V;
    g2->visited = (int*)malloc(g2->V * sizeof(int));
    g2->matrix = (int**)malloc(g2->V * sizeof(int*));
    for(i = 0; i < g2->V; i++)
    {
        //Set visited to be 0
        g2->visited[i] = 0;
        g2->matrix[i] = (int*)malloc(g2->V *sizeof(int));
        for(j = 0; j < g2->V; j++)
        {
            g2->matrix[i][j] = g.matrix[i][j];
        }
    }
}

/// @brief Prints the adjacency matrix of a graph
/// @param g graph
void printGraphMatrix(Graph g)
{
    int i,j;
    //Print the rows first.
    printf("Adjacency Matrix\n");
    //Print divider.
    for(i = 0; i < g.V; i++)
    {
        printf("---------");
    }
    printf("\n|  \t|");
    for(i = 0; i < g.V; i++)
    {
        printf("\t%d",i+1);
    }
    printf(" |\n");
    //Print divider.
    for(i = 0; i < g.V; i++)
    {
        printf("---------");
    }
    printf("\n");
    for(i=0;i<g.V;i++){
        //Print divider.
        printf("| %d\t|",i+1);
        for(j=0;j<g.V;j++)
            printf("\t%d",g.matrix[i][j]);
        printf("  |\n");
    }
    //Print divider.
    for(i = 0; i < g.V; i++)
    {
        printf("---------");
    }
    printf("\n");
}

/// @brief DFS function to find path between two vertices
/// @param g graph
/// @param vertex start vertex
/// @param end end vertex
/// @param parent parent of this vertex
/// @param parents parents array
/// @return 1 if found path, 0 if not
int dfs (Graph g, int vertex, int end, int parent, int * parents)
{
    //Now our graph already holds the visited, as opposed to the iterative version.
    //So mark this vertex as visited first.
    //Rememember to reset visited outside of loop for this to work...
    int i;
    g.visited[vertex-1] = 1;
    //Store parent
    parents[vertex - 1] = parent;

    //We found the path
    if(vertex == end)
        return 1;

    //Then for each neighbour, if not visited, we call DFS on that vertex until everything is printed out, and print it all out once we finish returning it all.
    for (i = 0; i < g.V; i++)
    {
        //I are the neighbours.
        if(g.matrix[vertex-1][i] == 1 && g.visited[i] == 0)
        {
            //If true, we found a path, return
            if (dfs(g,i+1,end,vertex,parents))
                return 1;
        }
    
    }
    return 0;
}

/// @brief Ford Fulkerson algorithm
/// @param graph graph
/// @param s s
/// @param t sink
/// @return max flow of a graph
int fordFulkerson(Graph g, int s, int t)
{
    int i,j;
    //Current flow in loop
    int flow;
    //No initial flow
    int maxFlow = 0;
    //Create a residual graph
    Graph residualGraph;
    //Duplicate the graph using helper function
    duplicateGraph(g, &residualGraph);
    //Initialize a parent array
    int * parents = (int*)malloc(residualGraph.V *sizeof(int));
    for(i =0; i < residualGraph.V; i++)
        parents[i] = 0;

    //While we can find a path to the sink
    while(dfs(residualGraph,s,t,-1,parents))
    {    
        //Find max flow
        flow = 999999;
        //Trace back our path from the sink to the start
        for(i = t; i != s; i = parents[i - 1])
        {
            //Set j as the parent of this i, which was the previous node
            //So the direction we should check is j -> i
            j = parents[i - 1];
            flow = minV(flow, residualGraph.matrix[j-1][i-1]);
        }

        //Update edges and reverse edges along path
        for(i = t; i != s; i = parents[i - 1])
        {
            //Set to be the previous node
            j = parents[i-1];
            //Update flow at matrix, we want to reverse direction.
            //J was the initial source, so [j][i] -, [i][j] +
            residualGraph.matrix[j-1][i-1] -= flow;
            residualGraph.matrix[i-1][j-1] += flow;
        }
        //Add to our max flow (is just a matter of 1 and 0 as we are matching)
        maxFlow += flow;
        //Then reset our visited for our dfs to work again
        for(i = 0; i < residualGraph.V; i++)
        {
            residualGraph.visited[i] = 0;
            parents[i] = -1;
        }
    }
    //printGraphMatrix(residualGraph);
    return maxFlow;
}

int main()
{
    int i, j;
    int Prj, Std, Mtr; //Project, Student and Mentor;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);
    scanf("\n");
    int projNumber;
    int mentorNumber;
    int np,nm; //number of projects and number of mentors
    //Nodes in graph is Prj + Std + Mtr without source and sink
    //Std *2 to create "two" seperate graphs
    int nodes = Prj + (Std*2) + Mtr;
    //Set the source to be first vertex
    int source = 1;
    //The sink to be 1 + Prj + Std + Mtr + 1
    int sink = nodes + 2;

    //build graph
    //Let source vertex be total + 1, sink be total + 2  
    Graph g;
    g.E = 0;
    g.V = nodes + 2;
    g.visited = (int*)malloc(g.V * sizeof(int));
    g.matrix = (int**)malloc(g.V * sizeof(int*));
    for(i = 0; i < g.V; i++)
    {
        //Update visited
        g.visited = 0;
        //Create a new matrix
        g.matrix[i] = (int*)malloc(g.V *sizeof(int));
        //Then initialize it to zero.
        for(j =0; j < g.V; j++)
        {
            g.matrix[i][j] = 0;
        }
    }
    //Handle the source connection to all projects
    for(i = 0; i < Prj; i++)
    {
        //Update our matrix
        g.matrix[source - 1][source + i] = 1;
        g.E++;
    }
    //Gather our inputs first
    //Loop through the inputs to get the desired outputs.
    for(i = 0; i < Std; i++)
    {
        //Gather the number of projects and number of mentors this student wants
        scanf("%d %d", &np, &nm);
        //printf("Student %d: Project Count: %d, Mentors Count: %d | Projects:", i + 1, np, nm);
        //The next entries are the projects to the students
        for(j = 0; j < np; j++)
        {
            scanf("%d", &projNumber);
            //printf("%d ", projNumber);
            //Then insert based on the proj number this student wants
            g.matrix[projNumber][(Prj + 1 +i)] = 1;
            g.E++;
        }
        //printf("Mentors:");

        //Handle student to student flow so each student's flow is limited to 1 
        g.matrix[(Prj + 1 +i)][(Prj + Std + 1 +i)] = 1;
        g.E++;


        for(j=0; j < nm; j++)
        {
            scanf("%d", &mentorNumber);
            //printf("%d ", mentorNumber);
            g.matrix[(Prj + Std + 1 +i)][(Prj + (Std*2) + mentorNumber)] = 1;
            g.E++;
        } 
        //putchar('\n');
    }

    //Starting index for mentors          
    i = Prj + (Std * 2) + 1;
    //Then handle the links from all mentors to source
    for(i; i < nodes + 1; i++)
    {          
        g.matrix[i][sink - 1] = 1;
        g.E++;
    }
    //printGraphMatrix(g);
    //apply Ford Fulkerson algorithm
    // use DFS or BFS to find a path
    maxMatch = matching(g);
    printf("%d\n", maxMatch);
    return 0;
}

int matching(Graph g)
{
    //Source node is 1
    //Sink node is last node
    return(fordFulkerson(g, 1, g.V));
}

void removeAdjVertex(ListNode** AdjList,int vertex)
{
 ListNode *temp, *preTemp;
 if(*AdjList != NULL)
 {
    if((*AdjList)->vertex ==vertex){//first node
      temp = *AdjList;
      *AdjList = (*AdjList)->next;
      free(temp);
      return;
    }
    preTemp = *AdjList;
    temp = (*AdjList)->next;
    while(temp!=NULL && temp->vertex != vertex)
    {
      preTemp= temp;
      temp = temp->next;
    }
    preTemp->next = temp->next;
    free(temp);
   }
}

void insertAdjVertex(ListNode** AdjList,int vertex)
{
  ListNode *temp;
  if(*AdjList==NULL)
  {
     *AdjList = (ListNode *)malloc(sizeof(ListNode));
     (*AdjList)->vertex = vertex;
     (*AdjList)->next = NULL;
  }
  else{
     temp = (ListNode *)malloc(sizeof(ListNode));
     temp->vertex = vertex;
     temp->next = *AdjList;
     *AdjList = temp;
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

void printQ(QueueNode *cur){
 if(cur==NULL) printf("Empty");

 while (cur != NULL){
    printf("%d ", cur->vertex);
    cur = cur->next;
  }
 printf("\n");
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