import heapq
import numpy as np
from collections import defaultdict
import time
import random as r

with open("tests/test2_new.txt") as f:
    lines = f.read().splitlines()

number_of_vertices = int(lines[0])
number_of_edges = int(lines[1])

vertices = lines[2:2+number_of_vertices]
edges = lines[2+number_of_vertices:]

ids_and_populations = [tuple(map(int, vertices[i].split(" "))) for i in range(len(vertices))]
populations = dict(ids_and_populations)

mydict = lambda: defaultdict(lambda: defaultdict())
G = mydict()

for i in range(len(edges)):
    source, target, weight = map(int, edges[i].split(" "))
    G[source][target] = weight
    G[target][source] = weight

def dijkstra(G, source):
    #start_time1 = time.time()
    costs = dict()
    for i in range(number_of_vertices):
        costs[i] = np.inf
    costs[source] = 0
    #print(f"Costs dict: {time.time() - start_time1}")
    
    #start_time = time.time()
    pq = []
    
    for node in G:
        heapq.heappush(pq, (node, costs[node]))
    #print(f"Heap Push: {time.time() - start_time}")
    
    #start_time = time.time()
    while len(pq) != 0:
        current_node, current_node_distance = heapq.heappop(pq)
        for neighbor_node in G[current_node]:
            weight = G[current_node][neighbor_node]
            distance = current_node_distance + weight
            if distance < costs[neighbor_node]:
                costs[neighbor_node] = distance
                heapq.heappush(pq, (neighbor_node, distance))
    #print(f"While Pop: {time.time() - start_time}")
    #print(f"Total Time: {time.time() - start_time1} sec")
    return np.sum(np.array(list(costs.values())) * np.array(list(populations.values())))


    import random as r

def random_start():
    res = [r.randint(0,number_of_vertices-1),r.randint(0,number_of_vertices-1)]
    if res[0] == res [1]:
        return random_start()
    return res

#//2 * O((V+E)*logV) = O(E*logV) //
def allocation_cost(G,i,j):
    return [dijkstra(G,i),dijkstra(G,j)]


# 2*O(V)*O(E*logV) = O(E*V*logV) #
def algo(G):
    selected_vertices = random_start() #TODO np.array
    selected_costs = allocation_cost(G,selected_vertices[0],selected_vertices[1]) #TODO np.array
    
    for not_selected in G.keys():
        if not_selected not in selected_vertices:
            bigger = max(selected_costs)
            this_cost = dijkstra(G,not_selected) 
            if this_cost < bigger:
                bigger_index = selected_costs.index(bigger)
                selected_costs[bigger_index] = this_cost
                selected_vertices[bigger_index] = not_selected
    return(selected_vertices,selected_costs)


#%timeit algo(G)
#[algo(G) for i in range(20)]
start_time = time.time()
algo(G)
elapsed_time = time.time() - start_time

with open("output.txt", "w+") as f:
    f.write(f"Elapsed time in sec: {elapsed_time}")
f.close()