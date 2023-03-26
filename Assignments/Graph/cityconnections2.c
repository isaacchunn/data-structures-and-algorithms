#include <stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
    printf("Enter number of cities \n");
    scanf("%d", &N); //number of cities
    int i_population; //population array
    int *population = (int *)malloc(sizeof(int)*(N)); //population array of size n
    for(i_population = 0; i_population < N; i_population++) //scanf all the populations
        scanf("%d", &population[i_population]);
    int i_road, j_road; //edges and vertices among two points
    int **road = (int **)malloc((N-1)*sizeof(int *));
    for(i_road = 0; i_road < N-1; i_road++)
    {
        road[i_road] = (int *)malloc((2)*sizeof(int)); //malloc another 2d array to show the vertices
    }
    //Scanf all the vertices.
    for(i_road = 0; i_road < N-1; i_road++)
    {
        for(j_road = 0; j_road < 2; j_road++)
        {
            scanf("%d", &road[i_road][j_road]);
        }
    }
    int Q; //number of queries
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
    
    if(out_ != NULL)
    {
        printf("%d", out_[0]);
        int i_out_;
        for(i_out_ = 1; i_out_ < Q; i_out_++)
            printf("\n%d", out_[i_out_]);
    }
    else{
        printf("LOL.\n");
    }

}

void printAdjacentMatrix(int ** matrix, int N)
{
    int i,j;
    //Print the rows first.
      printf("Adjacency Matrix\n");
      //Print divider.
      for(i = 0; i < N; i++)
      {
          printf("---------");
      }
      printf("\n|  \t|");
      for(i = 0; i < N; i++)
      {
          printf("\t%d",i+1);
      }
      printf(" |\n");
      //Print divider.
      for(i = 0; i < N; i++)
      {
          printf("---------");
      }
      printf("\n");
      for(i=0;i<N;i++){
          //Print divider.
          printf("| %d\t|",i+1);
          for(j=0;j<N;j++)
              printf("\t%d", matrix[i][j]);
          printf("  |\n");
      }
      //Print divider.
      for(i = 0; i < N; i++)
      {
          printf("---------");
      }
      printf("\n");
}
//Implement a recursive depth first search that does not use stack.
int dfs(int vertex, int endVertex, int N, int W, int ** adjMatrix, int * visited, int * population, int * count)
{
    int i, pathCount;
    //Update the visited array based on this vertex.
    visited[vertex - 1] = 1;
    
    //Print this vertex.
    //printf("Vertex: %d, W: %d, Population: %d\n", vertex, W,population[vertex-1]);
    
    //If the population of this city is less than or equal to W, we plus one
    if(population[vertex-1] <= W)
        (*count)++;
    
    if(vertex == endVertex)
    {
        //printf("%d -> END\n", vertex);
        return 1;
    }
    //Then for each neighbour, if not visited, we call DFS on that vertex until everything is printed out, and print it all out once we finish returning it all.
    for (i = 0; i < N; i++)
    {
        pathCount = *count;
        //I are the neighbours.
        if(adjMatrix[vertex-1][i] == 1 && visited[i] == 0)
        {
            if(dfs(i + 1, endVertex, N, W, adjMatrix, visited, population, &pathCount))
            {
                *count = pathCount;
                return 1;
            }
        }
    }
    //Then we print out the result
    //printf("%d -> ", vertex);
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
    //Make an adjacency matrix to check
    
    //Populate the adjacency matrix
    int ** adj = (int**)calloc(N,sizeof(int *));
    for(i = 0; i < N; i++)
    {
        adj[i] = (int*)calloc(N,sizeof(int));
    }
    
    //Make a visited matrix
    visited = (int*)calloc(N, sizeof(int));
    answer = (int*)calloc(Q, sizeof(int));
    
   // printAdjacentMatrix(adj, N);
    //Loop through roads (there are n-1 paths) and create our adjacency matrix
    for(i = 0; i < N-1; i++)
    {   //Update our adjacency matrix
        //road[i][0] is our start vertex
        //road[i][1] is our adjacent edge
        U = road[i][0]-1;   //start
        V = road[i][1]-1;   //end
        //printf("%d %d\n", road[i][0], road[i][1]);
        
        //Bidirectional graph?
        adj[U][V] = 1;
        adj[V][U] = 1;
    }
    printAdjacentMatrix(adj, N);
    
    //Now we loop through the queries and solve the question using our adj matrix to figure out the answer
    for (i =0; i < Q; i++)
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
        
        //Call our DFS function.
        dfs(U, V, N, W, adj, visited, population, &count);
        //putchar('\n');
        //Then store into answer the count
        answer[i] = count;
    
    }
    //Free visited and our adj
    free(visited);
    for(i = 0; i < N; i++)
    {
        free(adj[i]);
    }
    free(adj);
    
    return answer;
}
