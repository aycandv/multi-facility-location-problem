# multi-facility-location-problem
Term Project of COMP 305 Course at Koç University | Spring 2021


# Problem Definition

The problem is named as a multi-facility location problem. In a graph of cities, we need to find optimal locations of two hospitals to decrease the overall cost of patients to reach these hospitals. As it is known as a NP-Hard problem, we approached this problem from different perspectives as it is presented below.

# How to Run

Source code of all approaches are put under `/src/` folder in `.ipynb` format for `small` and `large` graphs. As code files are named with the approach used, You can directly get into these files to see results of different approaches. [Jupyter Notebook/Lab](https://jupyter.org) is required to run codes.

 - **Note:** `src/c/` folder could be ignored. At the beginning, we started for implementation using C, but simplicity of Python dominated. However, an instance of our hashmap implementation in C is presented in related directory.

---------
# Approaches Used


## Dynamic Programming

  At the very beginning, we devised a DP algorithm, but could not get it to run efficiently. We then realised that our DP algorithm needed V^2 space, and could not be decreased to O(1) like some bottom-up approaches. We realised that we needed a 1 million times 1 million matrix, which we learned that takes 3.75 TB in Python using C+Fortran implemented numpy arrays. (10 TB in py arrays) Not only that, our single Dijkstra took 2 minutes, whereas we needed a million times of that… We decided to go for it and implemented all heaps and queues and algorithms in C, resulting in a two times faster speed of 1 minute run for a single Dijkstra. Consequently, after we approximated that implementing a fibo-heap would give a 4 times increase, we decided to give up since a million times Dijkstra (for all vertices, that is APSP) would never finish with a 4 times, or anything similar, increase. We learned the hard way that an NP-hard is an NP-hard. We proceeded to divide the graph, and run Floyd-Warshall, tried 3 greedy heuristics, devised a V^4 DP APSP algorithm and finally coded ML implementation to find the best possible parameter weights for optimized facility selection.


## Graph Cut + Dynamic Programming

  We try to divide the problem into 2 subproblems and apply the Floyd-Warshall algorithm to find the cut and optimum places for the hospitals. Therefore, we first found a cutting point for the graph by finding the best place for 1 hospital problem. The solution we find is used as the cut point for the graph, to get 2 sub graphs.  After finding the solution for one hospital problem, we solve the same problem with 2 subgraphs. To guarantee that nodes only visit the nearest hospital in the 2 subgraph case, we decrease the weight of the first node’s edges as 0. Therefore we make nodes to use that road to detect the nodes that would be in the opposite subgraph. Then we hold another 2D marked array to hold whether the node is used to go to the farthest hospital. After we detected this, while calculating the sum for the hospitals, we did not take account of these node values for the respective hospital places value. Then, we took the 2 nodes with the minimum sum and the resulting 2 nodes are our solution for the problem.

```
Time Complexity : O(V^3)
Space Complexity : O(V^2) 
```

  * Elapsed Time:
```
for test2,
9.75 sec.
```

## Greedy Heuristic
After observing that optimal solution for bigger maps cannot be solved optimally (NP-hard), we decided to implement greedy heuristics. First one was to simply greedy add-drop, that is starting with two random nodes, check all other nodes in the graph and swap with the biggest on hand if a contender has a smaller associated cost.
Note: We also included a multi-processed version of this algorithm for future runs, say when graph size is a more realistic 10k, to simply select between the best options after multiple runs.

```
Time Complexity: O(V^3 log(V))
Space Complexity : O(E) 
```
  * Elapsed Time:
```
for test2,
17.03 sec.
```


### Local Optimization on Greedy Heuristic
We decided that previously discussed Greedy Heuristic may be improved by introducing local swap after every global swap, meaning that after every greedy add-drop, we run k-th neighbor subgraph algorithm we devices and swapped within this region if a better contender is present.

```
Time Complexity: O(V^3 log(V))
Space Complexity : O(E) 
```
  * Elapsed Time:
```
for test2,
17.04 sec.
```


### Sub-graph Expansion on Greedy Heuristic
  - This improvement is designed to be used in the largest graph `test3`. By starting from multiple points, It finds k-th neighbor graphs and finds the optimal points of each sub graph. After finding those, it finds the most common points that are encountered by the multiple runs. Then, it selects the subgraphs of the most common 2 points. After that, it merges those two subgraphs. By merging them, it runs APSP algorithm number of vertices times and finds the local optimum points for two hospitals. 
  - Space complexity of this algorithm is approximately close to number of edges because we used an adjacency map to keep vertex-edge information.
  - Time complexity of this algorithm includes an additional K multiplier which is related to number of random bootstrap points.
  - As it is an approximation to the global optimum solution, occasionally it could return a solution that is not global optimum. So, the best use case for this approach is to be used in very large graphs, with one million vertices as in `test3`. 
  - If these two subgraphs are disconnected after merge operation, the algorithm calculates (k+1)-th neighbor subgraphs and tries to merge them again to eliminate disconnection.
```
Time Complexity: O(K * V^3 log(V))
Space Complexity : O(E)
```

  * Elapsed Time:
```
for test2,
65.15 sec. - binary heap implementation for dijkstra
10.42 sec. - queue implementation for dijkstra
```

```
73 sec. - test3 - queue implementation
```



## Dynamic Programming + Combination Brute-Force

  When testing smaller maps, we decided to try to code an algorithm that would definitely give a correct answer, in smaller maps. Our analysis showed that our problem converges to n^n for higher number of hospital selections, due to involvement of combination selections, but we were able to approximate that our 2-median problem may be viewed as a V^4 algorithm, where we first run a V^3 APSP algorithm and construct APSP matrix, then continue to travel this matrix and try all possible combinations of 2 to pick hospital cities. What happens next is while traversing the matrix, for every row, we set the cost of the far-away hospital to zero, resulting in a complete new APSP matrix in every combination selection. Consequently, we sum the relevant columns of those matrices and proceed to pick the smallest.

```
Time Complexity: O(V^4)
Space Complexity: O(V^2)
```
  * Elapsed Time:
```
for test2,
12.82 sec.
```

## Machine Learning
In order to run our algorithms in the third and biggest map we thought we could learn the behaviour of the problem from small worksets and use machine learning to apply this to the last test case.
As machine learning parameters we used weight of the Vertex, distance * weights multiplication of the neighbour Vertex, and the distance * weight multiplication value of the neighbour’s neighbour Vertexes.
We used machine learning to find the necessary parameters using the second map and use these parameters in the biggest map. 
Our machine learning algorithm runs time in  O(V^4) time in the second map to find the parameters and uses  O(V^2) space.
After finding the parameters it runs in O(VlogV) time and uses O(V) space to find the optimum places of the hospitals in the third map. 

Finding Machine Learning Parameters
```
Time Complexity : O(V^4)
Space Complexity : O(V^2) where V is the vertex number of the second map (250 for our case)
```

Finding Optimal Space For 2 Hospitals
```
Time Complexity : O(VlogV)
Space Complexity : O(V) where V is the vertex number of the given map
```

* Elapsed Time:
```
51.4 sec. for test3
```



---------

# Prospective Development Path
  - All code can be implemented in C, 2x running time improvement as we showed for Dijkstra.
  - Fibonacci Heap may be implemented for 4x speed up for our "Greedy" approaches.
  - Graph-cut + DP Algorithm's constant factors can de decreased for faster running time on smaller graphs.
  - Different ML algorithms can both introduce better results and faster running times.
  - KU HPC clusters may be used to introduce parallelization and approximate to best theoretical running times.



# Team

* Alp Canoğlu &emsp;&ensp;&nbsp;     | [@AlpCanoglu](https://github.com/AlpCanoglu)
* Ata Kadirioğlu &emsp;              | [@akadirioglu](https://github.com/akadirioglu)
* Aycan Deniz Vit &nbsp;             | [@aycandv](https://github.com/aycandv)
* Yiğit Ertürk &emsp;&emsp;&nbsp;    | [@YigitErturk](https://github.com/YigitErturk)
