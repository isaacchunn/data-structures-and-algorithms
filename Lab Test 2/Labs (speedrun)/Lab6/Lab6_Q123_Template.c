#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }

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

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

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

void adjM2adjL(Graph *g)
{
    //Error handling as the union is unpopulated
    if(g->type == ADJ_LIST)
        return;

    //We want to assign it carefully as if we assign blindly, the union might be destroyed
    //Make a new adj list representation
    ListNode ** adjList = (ListNode**)malloc(g->V * sizeof(ListNode*));
    for(int i =0; i < g->V; i++)
    {
        //Initializea new list here.
        adjList[i] = NULL;
        for(int j = 0; j < g->V; j++)
        {
            //Get the value in our adj matrix and slot it into the list.
            if(g->adj.matrix[i][j])
            {
                ListNode * newNode = (ListNode*)malloc(sizeof(ListNode));
                newNode->vertex= j + 1;
                newNode->next = NULL;
                //If there exists a link, then we add it to this list...
                if(adjList[i] == NULL)
                {
                    adjList[i] = newNode;
                }
                else
                {
                    ListNode * curr = adjList[i];
                    while(curr->next != NULL)
                    {
                        curr = curr->next;
                    }
                    curr->next = newNode;
                }
            }
        }
    }

    //Then we can free the initial nodes
    for(int i = 0; i < g->V; i++)
    {
        free(g->adj.matrix[i]);
    }
    free(g->adj.matrix);

    //Then sret our new list and type
    g->adj.list = adjList;
    g->type = ADJ_LIST;
}

void adjL2adjM(Graph *g){
	// Question 2
    // Write your code here

    int ** adj = (int**)calloc(g->V , sizeof(int*));
    for (int i = 0; i < g->V ; i++)
    {
        adj[i] = (int*)calloc(g->V , sizeof(int));
    }
    //Loop through all the adhj list
    for(int i = 0; i < g->V; i++)
    {
        ListNode * curr = g->adj.list[i];
        while(curr != NULL)
        {
            //Store the key in the adj matrix
            adj[i][curr->vertex -1] = 1;
            curr = curr->next;
        }
    }


    //Free the initial list
    for(int i = 0; i < g->V; i++)
    {
        free(g->adj.list[i]);
    }
    free(g->adj.list);

    g->adj.matrix = adj;
    g->type = ADJ_MATRIX;

}

void calDegreeV(Graph g, int *degreeV)
{
    //Resret vertex
    for(int i =0; i < g.V; i++)
        degreeV[i] = 0;

	if(g.type == ADJ_MATRIX)
    {
        //Count all the 1.
        for(int i = 0; i < g.V; i++)
        {
            for(int j =0; j < g.V; j++)
            {
                if(g.adj.matrix[i][j])
                    degreeV[i]++;
            }   
        }
    }
    else
    {
        for(int i = 0; i < g.V; i++)
        {
            ListNode * curr = g.adj.list[i];
            while(curr != NULL)
            {
                degreeV[i]++;
                curr =curr->next;
            }
        }
    }
}

