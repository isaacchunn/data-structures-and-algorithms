#include <stdio.h>
#include <stdlib.h>
  
int* city_population (int N, int* population, int** road, int Q, int** cities) ;

int main() {
    int N;
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
    for( i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d", matrix[i][j]);
        }
        putchar('\n');
    }
}

int* city_population (int N, int* population, int** road, int Q, int** cities)
{
    // if(road == NULL || population == NULL || cities == NULL)
     //     return NULL;
     // if(N == 0 || Q == 0)
     //     return NULL;
     int i, j;
     //Make an adjacency matrix to check
     int ** adj;
     //Populate the adjacency matrix
     adj = (int**)calloc(N, sizeof(int));
     for(i =0 ; i < N; i++)
     {
         adj[i] = (int*)calloc(N, sizeof(int));
     }
     //Loop through roads (there are n-1 paths) and create our adjacency matrix
     for(i = 0; i < N-1; i++)
     {
         //Update our adjacency matrix
         //road[i][0] is our start vertex
         //road[i][1] is our adjacent edge
         adj[road[i][0]][road[i][1]] = 1;
     }
    
    printAdjacentMatrix(adj, N);
     
    return NULL;
}

