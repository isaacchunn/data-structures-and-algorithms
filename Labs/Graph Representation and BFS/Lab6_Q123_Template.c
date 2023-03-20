#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

/// @brief ListNode structure.
typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

//Stores different data types in the same memory location.
//Only one can be used at one time.
union GraphForm{
    //Make a 2D array of integers. (adj matrix)
    int **matrix;
    //Make an array of list nodes, each with their own (adj list) 
    ListNode **list;
};

/// @brief Graph struct for each graph.
typedef struct _graph{
    int V;                  //Vertice count
    int E;                  //Edge count
    enum GraphType type;    //Type of graph
    union GraphForm adj;    //Adj matrix/list.
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );
void insertVertices(Graph *, int, int);

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    //Input the number of vertices.
    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    //12 vertices manual input
    //g.V = 12;
    printf("Vertices: %d\n", g.V);

    //Set number of edges to be 0.
    g.E = 0;
    //Initialize the 2d matrix times the number of vertices
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    //Initialize each row up to V.
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    //Set all to 0 by initializing (0 means no edge)
    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;

    //Set the type to adj matrix mode.
    g.type = ADJ_MATRIX;

    //Result answer.
    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    //Scanf returns the number of items of the arguments list successfully filled on success.
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            //Set on both matrix 1, as it is symmetric.
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            //Increase the number of edges.
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }
    

    //Manual input (graph from slides)
    // insertVertices(&g, 11,1);
    // insertVertices(&g, 11,2);
    // insertVertices(&g, 1,2);
    // insertVertices(&g, 1,3);
    // insertVertices(&g, 1,4);
    // insertVertices(&g, 2,5);
    // insertVertices(&g, 2,6); 
    // insertVertices(&g, 6,9); 
    // insertVertices(&g, 6,10); 
    // insertVertices(&g, 3,7);
    // insertVertices(&g, 3,8);
    // insertVertices(&g, 8,12);

    calDegreeV(g,degreeV);

    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);

    adjM2adjL(&g);

    calDegreeV(g,degreeV);

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g);
    printGraphMatrix(g);

    return 0;
}

/// @brief Prints the adjacency matrix of a graph
/// @param g graph
void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

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
            printf("\t%d",g.adj.matrix[i][j]);
        printf("  |\n");
    }
    //Print divider.
    for(i = 0; i < g.V; i++)
    {
        printf("---------");
    }
    printf("\n");
}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}

/// @brief Prints the adjacency list of a graph
/// @param g graph
void printGraphList(Graph g){
    //Variable declaration
    int i;
    ListNode* temp;
    //Sanity check
    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    //Print at each index.
    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


/// @brief Converts the adjacency matrix of a graph to adjacency list form
/// @param g graph
void adjM2adjL(Graph *g)
{
    //Variable declaration.
    int i, j;
    ListNode * newNode;
    ListNode * tail;        //To insert at back to make it nicer and sorted. (NOT NECESSARY!)
    ListNode ** adjList;
    //Sanity check
    if(g == NULL || g->V == 0)
        return;

    //Initialize memory for the adj list
    //We have V entries of list nodes, temporary variable.
    adjList = (ListNode **)malloc(g->V * sizeof(ListNode));
    //Initialize each variable.
    for(i = 0; i < g->V; i++)
    {
        //Set this node to be NULL first.
        adjList[i] = NULL;
    }

  //Loop through the adjacency matrix to the and append
    for(i = 0; i < g->V; i++)
    {
        for (j = 0; j < g->V; j++)
        {
            //Check if it is 1, 1 means theres an edge
            if(g->adj.matrix[i][j] == 1)
            {
                //Then at the ith index we must add, we can skip the jth later on as it is n^2 check.
                newNode = (ListNode*)malloc(sizeof(ListNode));
                //The vertex is j as we are comparing it to i.
                newNode->vertex = j + 1;
                //Set the newNode's next to be NULL
                 newNode->next = NULL;
                //Check if node NULL or not.
                if(adjList[i] == NULL)
                {        
                    //Set as new head.
                    adjList[i] = newNode;
                    //Update temp
                    tail = adjList[i];
                }
                else
                {
                    //Add infront of previous tail
                    tail->next = newNode;
                    //Update tail to go next
                    tail = tail->next; //Can do tail = newNode, same.
                }
            }
        }
    }
  
    //Then free the adj matrices to prevent memory leak as we want to use the spaces we need.
    for(i = 0; i < g->V; i++)
    {
        //Free each array
        free(g->adj.matrix[i]);
    }
    //Free overall matrix
    free(g->adj.matrix);

    //SET THIS AFTER! AS IF WE SET IT FIRST AND FREE THE ADJ MATRIX, WE ARE EFFECTIVELY FREEING THE SAME MEMORY SPACE
    //THAT WAS USED TO UPDATE ADJ LIST!
    g->adj.list = adjList;
    
    //Set mode to be adj list
    g->type = ADJ_LIST;
}

/// @brief Converts the adjacency list of a graph to adjacency matrix form
/// @param g graph
void adjL2adjM(Graph *g){
	
    //
    int i, j;
    int ** adjMatrix;
    ListNode * curr;
    //Sanity check
    if(g == NULL || g->V == 0)
        return;
    
    //Make a temporary 2d array for the adjacency matrix
    adjMatrix = (int**)malloc(g->V * sizeof(int));
    for(i = 0; i < g->V; i++)
    {
       adjMatrix[i] = (int *)malloc(g->V*sizeof(int));
    }
    //Set all to 0 by initializing (0 means no edge)
    for(i=0;i<g->V;i++)
        for(j=0;j<g->V;j++)
            adjMatrix[i][j] = 0;

    //Then loop through each list and update the adjMatrix.
    for(i = 0; i < g->V; i++)
    {
        //Check if null, else can continue
        if(g->adj.list[i] == NULL)
            continue;
        
        //Else its not null
        curr = g->adj.list[i];
        while(curr != NULL)
        {
            //Add the current into adjmatrix
            adjMatrix[i][curr->vertex-1] = 1;
            //Traverse.
            curr = curr->next;
        }
    }

    //Then free the lists (there must be one free for one malloc. I used it twice, so I free twice.)
    for(i = 0; i < g->V; i++)
    {
        free(g->adj.list[i]);
    }
    free(g->adj.list);

    //SET THIS AFTER! AS IF WE SET IT FIRST AND FREE THE ADJ LIST, WE ARE EFFECTIVELY FREEING THE SAME MEMORY SPACE
    //THAT WAS USED TO UPDATE ADJ MATRIX!
    g->adj.matrix = adjMatrix;
    //Update the mode to adj matrix.
    g->type = ADJ_MATRIX;
}

void calDegreeV(Graph g, int *degreeV)
{
    int i, j;
    ListNode * curr;

    if(degreeV == NULL)
        return;

    //Reset degreeV
    for(i = 0; i < g.V; i++)
    {
        degreeV[i] = 0;
    }

	//Check the graph mode
    if(g.type == ADJ_LIST)
    {
        //Its adj list mode
        for(i = 0; i < g.V; i++)
        {
            if(g.adj.list[i] == NULL)
                continue;

            //Loop through each time
            curr = g.adj.list[i];
            while(curr != NULL)
            {
                degreeV[i]++;
                curr = curr->next;
            }
        }
        
    }
    else
    {
        //It's adj matrix  mode, so we can just n^2 it
        for (i = 0;i < g.V; i++)
        {
            for(j = 0; j < g.V; j++)
            {
                if(g.adj.matrix[i][j] == 1)
                    degreeV[i]++;
            }
        }
    }
}

void insertVertices(Graph * g, int V1, int V2)
{
    if(V1>0 && V1<=g->V && V2>0 && V2<=g->V)
    {
        //Set on both matrix 1, as it is symmetric.
        g->adj.matrix[V1-1][V2-1] = 1;
        g->adj.matrix[V2-1][V1-1] = 1;
        //Increase the number of edges.
        g->E++;
    }
}