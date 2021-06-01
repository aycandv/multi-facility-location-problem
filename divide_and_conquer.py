import readfile


def floydwarshall2(graph, root, root_index, weight):

    dist = [ [0]*len(graph) for i in range(len(graph))]
    marked = [ [0]*len(graph) for i in range(len(graph))]

    for x in range(len(graph)):
        if graph[x][root_index] == float('inf'):
            continue
        graph[x][root_index] = 0

    for x in range(len(graph)):
        if graph[root_index][x] == float('inf'):
            continue
        graph[root_index][x] = 0

    for x in range(len(graph)):
        for y in range(len(graph)):
            dist[x][y] = graph[x][y]

    for x in range(len(graph)):
        for y in range(len(graph)):
            marked[x][y] = 0

    for x in range(len(graph)):
        for y in range(len(graph)):
            for z in range(len(graph)):

                if dist[x][z] == float('inf') or dist[z][y] == float('inf'):
                    continue

                if dist[x][z] + dist[z][y] < dist[x][y]:
                    dist[x][y] = dist[x][z] + dist[z][y]
                    if z == root_index:  # Bana bu saçma geldi bir daha bakmak lazım yani bu ne

                        marked[x][y] = 1
                        marked[y][x] = 1
                        marked[x][z] = 1
                        marked[z][x] = 1
                        marked[z][z] = 1

                    if marked[x][z] == 1 or marked[z][y] == 1:
                        marked[x][y] = 1

    value = [0 for i in range(len(graph))]
    value[root_index] = float('inf')

    for x in range(len(graph)):
        for y in range(len(graph)):
            if dist[x][y] == float('inf'):
                continue
            if value[x] == float('inf'):
                continue

            if marked[x][y] == 1:
                continue
            value[x] += dist[x][y] * weight[x][1]

    min1 = float('inf')
    min2 = float('inf')
    min2_index = 0
    min1_index = 0

    for x in range(len(graph)):
        if value[x] <= min2:

            if value[x] <= min1:
                min2 = min1
                min2_index = min1_index
                min1 = value[x]
                min1_index = x
            else:
                min2 = value[x]
                min2_index = x

    print("Selected min 1 is : ")
    print(min1_index)
    print("\n")
    print("Selected min 2 is : ")
    print(min2_index)
    print("\n")


def floydwarshall(graph, weight):
    dist = [ [0]*len(graph) for i in range(len(graph))]
    marked = [ [0]*len(graph) for i in range(len(graph))]
    root = float('inf')
    root_index = 0

    for x in range(len(graph)):
        for y in range(len(graph)):
            dist[x][y] = graph[x][y]
            marked[x][y] = 0

    for x in range(len(graph)):
        for y in range(len(graph)):
            for z in range(len(graph)):

                if dist[x][z] == float('inf') or dist[z][y] == float('inf'):
                    continue

                if dist[x][z] + dist[z][y] < dist[x][y]:
                    dist[x][y] = dist[x][z] + dist[z][y]

    value = [0 for i in range(len(graph))]
    root = float('inf')

    for x in range(len(graph)):
        for y in range(len(graph)):
            if dist[x][y] == float('inf'):
                continue
            value[x] += dist[x][y] * weight[y][1]

    for x in range(len(graph)):
        if value[x] <= root:
            root = value[x]
            root_index = x

    print("Root value for the graph is ")
    print(root_index)
    print("\n")
    floydwarshall2(graph, root, root_index, weight)


if __name__ == '__main__':
    graph, weight = readfile.readfile("tests/test2_new.txt")
    
    floydwarshall(graph, weight)
