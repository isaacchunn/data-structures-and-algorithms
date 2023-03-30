#include<stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    printf("-");
    scanf("%d", &N);
    int i_population;
    int *population = (int *)malloc(sizeof(int)*(N));
    for(i_population = 0; i_population < N; i_population++)
        scanf("%d", &population[i_population]);
    int i_road, j_road;
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
        road[i_road] = (int *)malloc((2)*sizeof(int));
    }
    for(i_road = 0; i_road < N-1; i_road++)
    {
        for(j_road = 0; j_road < 2; j_road++)
        {
            scanf("%d", &road[i_road][j_road]);
        }
    }
    int Q;
    scanf("%d", &Q);
    int i_cities, j_cities;
    int **cities = (int **)malloc((Q)*sizeof(int *));
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
        cities[i_cities] = (int *)malloc((3)*sizeof(int));
    }
    for(i_cities = 0; i_cities < Q; i_cities++)
    {
        for(j_cities = 0; j_cities < 3; j_cities++)
        {
            scanf("%d", &cities[i_cities][j_cities]);
        }
    }

    int* out_ = city_population(N, population, road, Q, cities);
    printf("%d", out_[0]);
    int i_out_;
    for(i_out_ = 1; i_out_ < Q; i_out_++)
        printf("\n%d", out_[i_out_]);
}
#include<math.h>

/// @brief ListNode structure.
typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

//Implement a recursive depth first search that does not use stack.
void dfs(int vertex, ListNode ** list, int level, int parent, int *levels, int *parents)
{
    //Store the levels and parents
    levels[vertex - 1]= level;
    parents[vertex - 1] = parent;
    
    ListNode * currentNode = list[vertex-1];
    //Loop through all the adjacent nodes
    while(currentNode != NULL)
    {
        //Find out if this node has been visited yet or not.
        if(currentNode->vertex != parent)
        {
            //Conduct DFS again with this current vertex as parent, increasing level as 1 and the current node to be the vertex to dfs.
            dfs(currentNode->vertex, list, level+1, vertex, levels, parents);
        }
        currentNode = currentNode->next;
    }
}

void calculateAncestors(int ** ancestors, int* parent, int N)
{
    int i,j;
    int length = log2(N);
    //Set the first index of the ancestors array to be the parent.
    for(i = 1; i <= N; i++)
    {
        ancestors[0][i] = parent[i-1];
    }
    
    //Then update the rest completely via pre computation
    for(i = 1; i < length; i++)
    {
        for(j = 1; j <= N; j++)
        {
            //printf("%d:%d|%d\n",i,j, ancestors[i-1][ancestors[i-1][j]]);
            //Update the ancestors table.
            ancestors[i][j] = ancestors[i-1][ancestors[i-1][j]];
        }
    }
}

//LCA function to find the LCA of two nodes, so we do not have to DFS the entire graph each time
int LCA(int firstVertex, int secondVertex, int ** ancestors, int * parents, int*levels)
{
    //printf("Calculating LCA from %d to %d\n", firstVertex, secondVertex);
    int temp, diff, index;
    //Check if first vertex level is more as we are finding differences
    //I do this so I can just return first vertex instead of keep knowing which is more.
    //Swap the levels.
    if(levels[firstVertex -1] > levels[secondVertex-1])
    {
        temp = firstVertex;
        firstVertex = secondVertex;
        secondVertex = temp;
    }
    
    //Find difference in levels to climb up to the same level.
    diff = levels[secondVertex-1] - levels[firstVertex-1];
    
    //Move the deeper node to the same level.
    while(diff > 0)
    {
        //Log the diff so we can figure out how much to jump if possible.
        index = log2(diff);
        //secondVertex = parents[secondVertex -1];
        //Update our second vertex using our parent log table
        secondVertex = ancestors[index][secondVertex];
        //printf("diff %d, Log Diff: %d, Second: %d\n", diff, index, secondVertex);
        //diff--;
        //Now we have to minus our diff in a different way
        diff -= (1 <<index); //Shift left to to multiply by 2 our index so the difference becomes greater.
    }
    //printf("Same Level LCA from %d to %d, Diff:%d\n", firstVertex, secondVertex, diff);
    //Else, they are not the LCA yet, as they are at the same level
    while(firstVertex != secondVertex)
    {
        //printf("Before While Level LCA from %d to %d\n", firstVertex, secondVertex);
        index = log(levels[firstVertex-1]);

       // printf("Log Level: %d\n", index);
        for(;index >0 && ancestors[index][firstVertex] == ancestors[index][secondVertex];)
        {
            index--;
        }
        
        //Then we found the max so we can just  assign first and second
        firstVertex = ancestors[index][firstVertex];
        secondVertex = ancestors[index][secondVertex];
        //Then keep minusing until we reach the top.
        //So keep making both vertexes go up until we find a common ground
        //Worst case will be root?
        //firstVertex = parents[firstVertex-1];
        //secondVertex = parents[secondVertex -1];
        //printf("After While Level LCA from %d to %d\n", firstVertex, secondVertex);
    }
   // printf("Done!\n");
    //Return the LCA
    return firstVertex;
}
int* city_population (int N, int* population, int** road, int Q, int** cities)
{
    int i, j, count;
    int U, V, W;
    int * visited, *answer;
    ListNode * newNode, *newNode2;
    //Answer variables
    int lca, startVertice, endVertice;
    int dpLength = log2(N);
    
    //Populate the adjacency list
    ListNode ** list = (ListNode**)malloc(N * sizeof(int *));
    //Malloc levels and parents to store the levels and parents so we can use LCA to make the search faster
    int * levels = (int*)calloc(N, sizeof(int));
    int * parents = (int*)calloc(N, sizeof(int));
    
    //Initialize the ancestors list for precomputation
    int ** ancestors = (int**)calloc(dpLength + 1, sizeof(int*));
    
    for(i = 0; i < N; i++)
    {
        //Initialize lsit
        list[i] = NULL;
    }
    for(i = 0; i < dpLength + 1; i++)
    {
        //Initialize ancestors
        ancestors[i] = (int*)calloc(N + 1, sizeof(int));
    }
    
    //Make a visited matrix
    visited = (int*)calloc(N, sizeof(int));
    //Generate our answer array
    answer = (int*)calloc(Q, sizeof(int));
    
    //Loop through roads (there are n-1 paths) and create our adjacency list
    for(i = 0; i < N - 1; i++)
    {
        //road[i][0] is our start vertex
        //road[i][1] is our adjacent edge
        U = road[i][0]-1;   //start
        V = road[i][1]-1;   //end
        //printf("%d %d\n", road[i][0], road[i][1]);
        
        //Adjacency list to store at both index
        newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->vertex = V + 1;
        newNode->next = list[U];
        list[U]= newNode;
        
        newNode2 = (ListNode*)malloc(sizeof(ListNode));
        newNode2->vertex = U + 1;
        newNode2->next = list[V];
        list[V] = newNode2;
    }

    //DFS once to update our levels and parents so we can calculate our lca
    dfs(1, list, 0, 0, levels, parents);
    //Calculate the ancestors in logn
    calculateAncestors(ancestors, parents, N);
    
    printf("\nLevels\n");
    for(i = 0; i < N; i++)
    {
        printf("%d ", levels[i]);
    }
    printf("\nParents\n");
    for(i = 0; i < N; i++)
    {
        printf("%d ", parents[i]);
    }
    
    printf("\nAncestors\n");
    for(i = 0; i < dpLength + 1; i++)
    {
        printf("%d: ", i);
        for(j = 0; j < N + 1; j++)
        {
            printf("%d ", ancestors[i][j]);
        }
        putchar('\n');
    }
     
        
    for (i = 0; i < Q; i++)
    {
        //Reset count
        count = 0;
        //Get the relevant infos from the cities
        U = cities[i][0];
        V = cities[i][1];
        //The subsequent must be less than this W
        W = cities[i][2];
        
        //Find the LCA of these 2 nodes
        lca =  LCA(U, V,ancestors, parents, levels);
        
        startVertice = U;
        endVertice = V;
        //Propagate both vertice to the LCA and find the population
        while(startVertice != lca)
        {
            if(population[startVertice - 1] <= W)
                count++;
            startVertice = parents[startVertice - 1];
        }
        while(endVertice != lca)
        {
            if(population[endVertice - 1] <= W)
                count++;
            endVertice = parents[endVertice - 1];
        }
        //Do one last check for LCA
        if(population[lca - 1] <= W)
            count++;
        //Then store into answer the count
        answer[i] = count;
    }
     
    //Free visited and our adj
    free(visited);
    for(i = 0; i < N; i++)
    {
        //free(ancestors[i]);
        free(list[i]);
    }
    //free(ancestors);
    free(list);
    free(levels);
    free(parents);
    return answer;
}

