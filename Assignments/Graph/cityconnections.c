#include<stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
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
/// @brief ListNode structure.
typedef struct _listnode
{
    int vertex;
    struct _listnode *next;
} ListNode;

//Implement a recursive depth first search that does not use stack.
int dfs(int vertex, int endVertex, int N, int W, ListNode ** list, int * visited, int * population, int * count)
{
    //Temporary stored path count
    int pathCount;

    //Declare a current node to start traversing through.
    ListNode * currentNode = list[vertex-1];
    
    //If the population of this city is less than or equal to W, we plus one
    if(population[vertex-1] <= W)
        (*count)++;
    
    if(vertex == endVertex)
        return 1;

    //No outgoing paths.
    if(currentNode == NULL)
        return 0;
    
    //Loop through all the adjacent nodes
    while(currentNode != NULL)
    {
        pathCount = *count;
        //Find out if this node has been visited yet or not.
        if(!visited[currentNode->vertex - 1])
        {
            //printf("Visited %d ->", currentNode->vertex);
            visited[currentNode->vertex - 1] = 1;
            if(dfs(currentNode->vertex, endVertex, N, W, list, visited, population, &pathCount))
            {
                *count = pathCount;
                return 1;
            }
        }
        currentNode = currentNode->next;
    }
    return 0;
}
         
int* city_population (int N, int* population, int** road, int Q, int** cities)
{
    // if(road == NULL || population == NULL || cities == NULL)
     //     return NULL;
     // if(N == 0 || Q == 0)
     //     return NULL;
    int i, j, count;
    int U, V, W;
    int * visited, *answer;
    ListNode * newNode, *newNode2;
    //Make an adjacency matrix to check
    
    //Populate the adjacency list
    ListNode ** list = (ListNode**)calloc(N , sizeof(int *));
    
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
        newNode->next = NULL;
        
        newNode2 = (ListNode*)malloc(sizeof(ListNode));
        newNode2->vertex = U + 1;
        newNode2->next = NULL;
        
        if(list[U] == NULL)
            list[U] = newNode;
        else
        {
            newNode->next = list[U];
            list[U] = newNode;
        }
        
        if(list[V] == NULL)
            list[V] = newNode2;
        else
        {
            newNode2->next = list[V];
            list[V] = newNode2;
        }
    }
    //Now we loop through the queries and solve the question using our adj list to figure out the answer
    for (i = 0; i < Q; i++)
    {
        count = 0;
        //Get the relevant infos from the cities
        U = cities[i][0];
        V = cities[i][1];

        //The subsequent must be less than this W
        W = cities[i][2];
        
        //Reset our visited array before we conduct DFS again
        for(j = 0; j < N; j++)
            visited[j] = 0;
        
        //Set the u to be visited
        visited[U-1] = 1;
        
        //printf("START: %d -> ", U);
        //Call our DFS function.
        dfs(U, V, N, W, list, visited, population, &count);
        //Then store into answer the count
        answer[i] = count;
    }
    //Free visited and our adj
    free(visited);
    for(i = 0; i < N; i++)
    {
        free(list[i]);
    }
    free(list);
    
    return answer;
}
