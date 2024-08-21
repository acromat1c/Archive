def getShortestPath(s):
    T = {s}  # Set containing vertices whose paths to s are known
    cost = {vertex: float('inf') for vertex in graph}  # Initialize costs
    cost[s] = 0  # Cost from s to s is 0 initially
    parent = {}  # To store parent vertices

    while len(T) < len(graph):  # While T doesn't contain all vertices
        min_cost = float('inf')
        v = None
        for u in T:
            for neighbor in graph[u]:
                if neighbor not in T:
                    if cost[u] + graph[u][neighbor] < min_cost:
                        min_cost = cost[u] + graph[u][neighbor]
                        v = neighbor
                        parent[v] = u  # Update parent of v
        if v is None:
            break
        T.add(v)
        cost[v] = min_cost

    return cost, parent

# Example graph representation (assuming graph is a dictionary of dictionaries)
graph = {
    'A': {'B': 3, 'C': 1},
    'B': {'A': 3, 'C': 7, 'D': 5},
    'C': {'A': 1, 'B': 7, 'D': 2},
    'D': {'B': 5, 'C': 2}
}

# Example usage
source_vertex = 'A'
shortest_costs, parents = getShortestPath(source_vertex)
print("Shortest Costs:", shortest_costs)
print("Parents:", parents)