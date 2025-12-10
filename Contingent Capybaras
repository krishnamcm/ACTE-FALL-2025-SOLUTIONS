from itertools import permutations
from collections import deque

N = int(input())
grid = [list(input().strip()) for _ in range(N)]

capybaras = {}
cats = set()
E_pos = None

for i in range(N):
    for j in range(N):
        cell = grid[i][j]
        if cell == 'E':
            E_pos = (i, j)
        elif cell == '#':
            cats.add((i, j))
        elif cell.isdigit():
            capybaras[int(cell)] = (i, j)

dirs = [(-1,0),(1,0),(0,-1),(0,1)]

def in_bounds(x,y):
    return 0<=x<N and 0<=y<N

def bfs(start, allow_adjacent=False):
    visited = [[False]*N for _ in range(N)]
    dist = [[float('inf')]*N for _ in range(N)]
    q = deque()
    x0,y0 = start
    q.append((x0,y0,0))
    visited[x0][y0] = True
    dist[x0][y0] = 0
    
    while q:
        x, y, d = q.popleft()
        for dx, dy in dirs:
            nx, ny = x+dx, y+dy
            if in_bounds(nx, ny) and not visited[nx][ny]:
                if grid[nx][ny] == '#':
                    continue
                if not allow_adjacent:
                    if any((nx+dx2,ny+dy2) in cats for dx2,dy2 in dirs):
                        continue
                visited[nx][ny] = True
                dist[nx][ny] = d+1
                q.append((nx, ny, d+1))
    return dist

points = [E_pos] + [capybaras[k] for k in sorted(capybaras.keys())]
num_points = len(points)
dist_matrix = [[0]*num_points for _ in range(num_points)]

bfs_results = []
for p in points:
    bfs_results.append(bfs(p, allow_adjacent=False))

all_reachable = True
for i in range(1,num_points):
    if bfs_results[0][points[i][0]][points[i][1]] == float('inf'):
        all_reachable = False
        break

if not all_reachable:
    bfs_results = []
    for p in points:
        bfs_results.append(bfs(p, allow_adjacent=True))

for i in range(num_points):
    for j in range(num_points):
        xi, yi = points[j]
        dist_matrix[i][j] = bfs_results[i][xi][yi]

capy_keys = sorted(capybaras.keys())
best_order = None
best_dist = float('inf')

for perm in permutations(range(1,num_points)):
    total = dist_matrix[0][perm[0]] 
    for i in range(len(perm)-1):
        total += dist_matrix[perm[i]][perm[i+1]]
    if total < best_dist:
        best_dist = total
        best_order = perm

result = [capy_keys[i-1] for i in best_order] 
print(' '.join(map(str, result)))
