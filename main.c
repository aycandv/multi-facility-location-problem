// C Program for Floyd Warshall Algorithm
#include<stdio.h>
 
// Number of vertices in the graph
#define V 8
 
/* Define Infinite as a large enough
  value. This value will be used
  for vertices not connected to each other */
#define INF 99999
 
// A function to print the solution matrix
void printSolution(int dist[][V]);
 
// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall (int graph[][V])
{
    /* dist[][] will be the output matrix
      that will finally have the shortest
      distances between every pair of vertices */
    int dist[V][V], i, j, k;
 
    /* Initialize the solution matrix
      same as input graph matrix. Or
       we can say the initial values of
       shortest distances are based
       on shortest paths considering no
       intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
 
    /* Add all vertices one by one to
      the set of intermediate vertices.
      ---> Before start of an iteration, we
      have shortest distances between all
      pairs of vertices such that the shortest
      distances consider only the
      vertices in set {0, 1, 2, .. k-1} as
      intermediate vertices.
      ----> After the end of an iteration,
      vertex no. k is added to the set of
      intermediate vertices and the set
      becomes {0, 1, 2, .. k} */
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++)
            {

                if ((dist[i][k] == INF) ||  dist[k][j] == INF)  
				{
					continue;
				}  

                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
                    
                  
            }
        }
    }
 
    // distance[] = [5, 3, 6,0, 6, 4, 2]
    int node_weight[] = {3, 5 ,7 ,6 ,9 ,2 ,4,6};
    int value[10000];
    value [3] = INF;
    // Print the shortest distance matrix
     i = 0;
     j= 0;
    printSolution(dist);
    for (i = 0; i < V; i++)
    {

        // Pick all vertices as source one by one
        for (j = 0; j < V; j++)
        {
            if (dist[i][j] == INF )
				{
					continue;
				}  

             value[i] += dist[i][j]* node_weight[j];
            

        }
    }

    // int min = 999999;
    // int root = 0;
    // for(int v = 0 ;v<V; v++){
    //     printf("value that is found for %d : %d\n",v,value[v]);
    //     if (value[v]<min){

    //         min = value[v];
    //         root = v;

    //     }

    // }


    int min1 = 999999;
    int min2 = 999999;
    int root1 = 0;
    int root2 = 0;
    for(int v = 0 ;v<V; v++){
        printf("value that is found for %d : %d\n",v,value[v]);
        if (value[v]<min1){
            

            min1 = value[v];
            root1 = v;

        }

    }



    // ikiye böldük
    printf("Selected root is %d\n",root1);


   
}
 
/* A utility function to print solution */
void printSolution(int dist[][V])
{
    printf ("The following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d ", dist[i][j]);
        }
        printf("\n");
    }
}
 
// driver program to test above function
int main()
{
    /* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)
            3           */
    // int graph[V][V] = { {0,   5,  INF, 10},
    //                     {5, 0,   3, INF},
    //                     {INF, 3, 0,   1},
    //                     {10, INF, 1, 0}
    //                   };


    // int graph[V][V] = {{0,INF,5,INF,INF,INF,INF},
    //                     {INF,0,3,INF,INF,INF,INF},
    //                     {5,3,0,6,INF,INF,INF},
    //                     {INF,INF,6,0,6,INF,INF},
    //                     {INF,INF,INF,6,0,4,2},
    //                     {INF,INF,INF,INF,4,0,INF},
    //                     {INF,INF,INF,INF,2,INF,0}
    //                      };

    int graph[V][V] = {{0,INF,5,INF,INF,INF,INF,INF},
                        {INF,0,3,INF,INF,INF,INF,INF},
                        {5,3,0,INF,INF,INF,INF,7},
                        {INF,INF,INF,INF,INF,INF,INF,INF},
                        {INF,INF,INF,INF,0,4,2,7},
                        {INF,INF,INF,INF,4,0,INF,INF},
                        {INF,INF,INF,INF,2,INF,0,INF},
                        {INF,INF,7,INF,7,INF,0,INF}
                         };

    //  int graph[V][V] = {{0,INF,5},
    //                     {INF,0,3},
    //                     {5,3,0}
    //                      };

                    //   int graph[V][V] = { {0,   5,  INF, 10},
                    //     {INF, 0,   3, INF},
                    //     {INF, INF, 0,   1},
                    //     {INF, INF, INF, 0}
                    //   };
 
    // Print the solution
    floydWarshall(graph);
    
    return 0;
}