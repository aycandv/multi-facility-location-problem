// C Program for Floyd Warshall Algorithm
#include <stdio.h>
#include "readfile.c"
// Number of vertices in the graph
#define V size

/* Define Infinite as a large enough
  value. This value will be used
  for vertices not connected to each other */
#define INF 99999



int firstDivision = 0;
char * filename = "tests/test1_new.txt";		//char * filename = "tests/test2_new.txt";
int * weight;
int size;
int ** vertex;
int root = INF;
int root_index = 0;


// A function to print the solution matrix
void printSolution(int dist[][V]);
void floydWarshall2 (int ** graph);

// Solves the all-pairs shortest path
// problem using Floyd Warshall algorithm
void floydWarshall (int ** graph)
{
    printf("Task0 \n");
//	int V = size;
    int dist[V][V], i, j, k;
    int marked[V][V];



    // (dist) = malloc(size_intptr*size);

    // for (size_t i = 0; i < size; i++)
    // {
    //     (dist)[i] = malloc(size_int*size);
    // }

    // (dist) = malloc(size_intptr*size);

    // for (size_t i = 0; i < size; i++)
    // {
    //     (dist)[i] = malloc(size_int*size);
    // }


    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = *( *(graph + i) + j);

    for (i = 0; i < V; i++)
           for (j = 0; j < V; j++)
        	   marked[i][j] = 0;

    printf("Task1 \n");

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
                if (dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int value[V];
    for (int i = 0; i <V ; i++) {
        value[i] = 0;
    }
    //print_array(size,value);
    //print_array(size,weight);
   // print2d_array(size,dist);
    // Print the shortest distance matrix
     i = 0;
     j= 0;

     printSolution(dist); //marked);
     printf("Task2 \n");

     for (i = 0; i < V; i++)
    {
        // Pick all vertices as source one by one
        for (j = 0; j < V; j++)
        {
            if (dist[i][j] == INF )
				{
					continue;
				}
            value[i] += dist[i][j]* weight[j];
            printf("%d \n",value[i]);
        }
    }


    for(int v = 0 ;v<V; v++){
        if (value[v]<=root){
            	root = value[v];
            	root_index = v;
        }
    }

    printf("Selected root is %d\n", root_index);
    floydWarshall2 (graph);
}

void floydWarshall2 (int **graph)
{
	//adjust the graph after division
    int dist[V][V], i, j, k;
    int marked[V][V];

    for (i = 0; i < V; i++){
    	if (*( *(graph + i) + root_index) == INF )
			{
				continue;
			}
		*( *(graph + i) + root_index) = 0;
    }

    for (i = 0; i < V; i++){
      	if (*( *(graph + root_index) + i) == INF )
  			{
  				continue;
  			}
  		*( *(graph + root_index) + i) = 0;
    }


    /* dist[][] will be the output matrix
      that will finally have the shortest
      distances between every pair of vertices */


    /* Initialize the solution matrix
      same as input graph matrix. Or
       we can say the initial values of
       shortest distances are based
       on shortest paths considering no
       intermediate vertex. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = *( *(graph + i) + j);

    for (i = 0; i < V; i++)
           for (j = 0; j < V; j++)
        	   marked[i][j] = 0;


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

                if ((dist[i][k] == -INF) ||  dist[k][j] == -INF)
                {
                	continue;
                }

                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j]){

                    dist[i][j] = dist[i][k] + dist[k][j];

                    if(k == root){	//	if(i==3 || j == 3 || k == 3){
						marked[i][j] = 1;
						marked[j][i] = 1;
						marked[i][k] = 1;
						marked[k][i] = 1;
						marked[k][k] = 1;
					}
                    if(marked[i][k] || marked[k][j]){
            			marked[i][j] = 1;
            		}
                }
            }
        }
    }

    int value[size];
    value [root_index] = INF;
    // Print the shortest distance matrix
     i = 0;
     j= 0;

//    printSolution(dist, marked);

     for (i = 0; i < V; i++)
    {
        // Pick all vertices as source one by one
        for (j = 0; j < V; j++)
        {
            if (dist[i][j] == INF )
				{
					continue;
				}
            if(marked[i][j] == 1) continue;
            value[i] += dist[i][j]* weight[j];
        }
    }

    int min1 = INF;
    int min2 = INF;
    int min1_index = 0;
    int min2_index = 0;
    for(int v = 0 ;v<V; v++){
        if (value[v]<=min2){
            if (value[v]<=min1){
				min2 = min1;
				min2_index = min1_index;
				min1 = value[v];
				min1_index = v;
            }else{
            	min2 = value[v];
            	min2_index = v;
            }
        }
    }

    printf("Selected min 1 is %d\n", min1_index);
    printf("Selected min 2 is %d\n", min2_index);

}

/* A utility function to print solution */
void printSolution(int dist[][V]) //int marked[][V])
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

    // printf ("The following matrix shows marked vertices \n");
    //    for (int i = 0; i < V; i++)
    //    {
    //        for (int j = 0; j < V; j++)
    //        {
    //            if (marked[i][j] == INF)
    //                printf("%7s", "INF");
    //            else
    //                printf ("%7d ", marked[i][j]);
    //        }
    //        printf("\n");
    //    }
}

// driver program to test above function
int main()
{
	/*
    int graph[V][V] = {{0,INF,5,INF,INF,INF,INF},
                         {INF,0,3,INF,INF,INF,INF},
                         {5,3,0,6,INF,INF,INF},
                         {INF,INF,6,0,6,INF,INF},
                         {INF,INF,INF,6,0,4,2},
                         {INF,INF,INF,INF,4,0,INF},
                         {INF,INF,INF,INF,2,INF,0}
                          };
	*/

	/*
    int graph[V][V] = {{0,INF,5,INF,INF,INF,INF,INF},
                        {INF,0,3,INF,INF,INF,INF,INF},
                        {5,3,0,0,INF,INF,INF,20},
                        {INF,INF,0,0,0,INF,INF,INF},
                        {INF,INF,INF,0,0,4,2,20},
                        {INF,INF,INF,INF,4,0,INF,INF},
                        {INF,INF,INF,INF,2,INF,0,INF},
                        {INF,INF,20,INF,20,INF,INF,0}
                         };
	*/

    //  int graph[V][V] = {{0,INF,5},
    //                     {INF,0,3},
    //                     {5,3,0}
    //                      };

                    //   int graph[V][V] = { {0,   5,  INF, 10},
                    //     {INF, 0,   3, INF},
                    //     {INF, INF, 0,   1},
                    //     {INF, INF, INF, 0}
                    //   };

    // int graph[V][V] = {{0,INF,5,INF,INF,INF,INF},
    //                      {INF,0,3,INF,INF,INF,INF},
    //                      {5,3,0,6,INF,INF,INF},
    //                      {INF,INF,6,0,6,INF,INF},
    //                      {INF,INF,INF,6,0,4,2},
    //                      {INF,INF,INF,INF,4,0,INF},
    //                      {INF,INF,INF,INF,2,INF,0}
    //                       };


	readFile(&size, &weight, &vertex, filename);

//	print_array(size, weight);
	print2d_array(size, vertex);
    // Print the solution

    printf("Floyd0 \n");
    floydWarshall(vertex);
  // floydWarshall(graph);

    return 0;
}
