from WeightedGraph import WeightedGraph

# Define the vertices
vertices = ["A", "B", "C", "D", "E"]

# Define the edges with weights
edges = [(0, 1, 2), (0, 3, 8), (1, 2, 3), (1, 3, 5), (1, 4, 1), (2, 4, 7), (3, 4, 4)]

# Create a weighted graph
graph = WeightedGraph(vertices, edges)

# Display the weighted edges
print("Weighted Edges:")
graph.printWeightedEdges()
print()

# Perform some operations
sourceVertex = 0
print("Shortest Path Tree from", graph.getVertex(sourceVertex))
shortestPathTree = graph.getShortestPath(sourceVertex)
shortestPathTree.printAllPaths()
print()

# Get the minimum spanning tree
print("Minimum Spanning Tree:")
minimumSpanningTree = graph.getMinimumSpanningTree()
minimumSpanningTree.printTree()
print("Total weight of the minimum spanning tree:", minimumSpanningTree.getTotalWeight())