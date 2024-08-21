def orientation(p, q, r):
    val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1])
    if val == 0:
        return 0
    return 1 if val > 0 else 2 


def getConvexHull(points):
    if len(points) < 3: return points
    
    n = len(points)
    if n < 3:
        return "Convex hull not possible"

    hull = []

    l = min(range(n), key=lambda i: points[i][0])
    p = l
    q = 0

    while True:
        hull.append(p)
        q = (p + 1) % n
        for i in range(n):
            if orientation(points[p], points[i], points[q]) == 2:
                q = i
        p = q
        if p == l:
            break

    return [points[i] for i in hull]