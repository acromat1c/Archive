from Graph import Graph
from Graph import Tree
from WeightedEdge import WeightedEdge

INFINITY = 1e+308 # Infinity value

class WeightedGraph(Graph):
    def __init__(self, vertices=[], edges=[]):
        super().__init__(vertices, edges)
        self.adjacencyMatrix = [[0] * len(vertices) for _ in range(len(vertices))]

    # Override this method in the Graph class
    def getAdjacencyMatrix(self, edges):
        for edge in edges:
            u = edge[0]
            v = edge[1]
            w = edge[2]
            # Insert an edge (u, v, w) into the adjacency matrix
            self.adjacencyMatrix[u][v] = w
            self.adjacencyMatrix[v][u] = w  # Assuming undirected graph

    # Display edges with weights
    def printWeightedEdges(self):
        for i in range(len(self.vertices)):
            print(str(self.getVertex(i))
                  + " (" + str(i), end="): ")
            for j in range(len(self.vertices)):
                if self.adjacencyMatrix[i][j] != 0:
                    print("(" + str(i) + ", " + str(j)
                          + ", " + str(self.adjacencyMatrix[i][j]), end=") ")
            print()

    # Return the weight between two vertices
    def getWeight(self, u, v):
        return self.adjacencyMatrix[u][v]

    # Override the addEdge method to add a weighted edge
    def addEdge(self, u, v, w):
        if u in self.vertices and v in self.vertices:
            # Add an edge (u, v, w) to the adjacency matrix
            self.adjacencyMatrix[u][v] = w
            self.adjacencyMatrix[v][u] = w  # Assuming undirected graph

    # Get a minimum spanning tree rooted at the specified vertex
    def getMinimumSpanningTree(self, startingVertex=0):
        # Implementation of MST remains unchanged
        pass

    # Find single source shortest paths
    def getShortestPath(self, sourceVertex):
        # cost[v] stores the cost of the path from v to the source
        cost = [INFINITY] * len(self.vertices)  # Initial cost to infinity
        cost[sourceVertex] = 0  # Cost of source is 0

        # parent[v] stores the previous vertex of v in the path
        parent = [-1] * len(self.vertices)

        # T stores the vertices whose path found so far
        T = []

        # Expand T
        while len(T) < len(self.vertices):
            # Find smallest cost v in V - T
            u = -1  # Vertex to be determined
            currentMinCost = INFINITY
            for i in range(len(self.vertices)):
                if i not in T and cost[i] < currentMinCost:
                    currentMinCost = cost[i]
                    u = i

            if u == -1:
                break
            else:
                T.append(u)  # Add a new vertex to T

            # Adjust cost[v] for v that is adjacent to u and v in V - T
            for v in range(len(self.vertices)):
                if v not in T and self.adjacencyMatrix[u][v] != 0 and cost[v] > cost[u] + self.adjacencyMatrix[u][v]:
                    cost[v] = cost[u] + self.adjacencyMatrix[u][v]
                    parent[v] = u

        # Create a ShortestPathTree
        return ShortestPathTree(sourceVertex, parent, T, cost,
                                self.vertices)


# MST is a subclass of Tree, defined in the preceding chapter
class MST(Tree):
    def __init__(self, startingIndex, parent, T,
                 totalWeight, vertices):
        super().__init__(startingIndex, parent, T, vertices)
        # Total weight of all edges in the tree
        self.totalWeight = totalWeight

    def getTotalWeight(self):
        return self.totalWeight


# ShortestPathTree is an inner class in WeightedGraph
class ShortestPathTree(Tree):
    def __init__(self, sourceIndex, parent, T, costs, vertices):
        super().__init__(sourceIndex, parent, T, vertices)
        self.costs = costs

    # Return the cost for a path from the root to vertex v
    def getCost(self, v):
        return self.costs[v]

    # Print paths from all vertices to the source
    def printAllPaths(self):
        print("All shortest paths from "
              + str(self.vertices[self.root]) + " are:")
        for i in range(len(self.costs)):
            self.printPath(i)  # Print a path from i to the source
            print("(cost: " + str(self.costs[i]) + ")")  # Path cost