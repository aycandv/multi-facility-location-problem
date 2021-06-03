
def readfile(filename):
   """ Reading the file into an array"""

   with open(filename) as f:
      file = f.read().splitlines()

      vertex_number = int(file[0])
      edge_number = int(file[1])

      vertices = file[2:2+vertex_number]
      edges = file[2+vertex_number:]

      weight_array = [tuple(map(int, vertices[i].split(" "))) for i in range(len(vertices))]

      vertex_array =  [ [0]*vertex_number for i in range(vertex_number)]

      for i in range(len(edges)):
         source, target, weight = map(int, edges[i].split(" "))
         vertex_array[source][target] = weight
         vertex_array[target][source] = weight
      
      return (init_vertex(vertex_array) , weight_array)




def init_vertex(vertices):
   for x in range(len(vertices)):
      for y in range(len(vertices)):
         
         if vertices[x][y] == 0 and x != y:
            vertices[x][y] = float('inf')
   
   return vertices
            