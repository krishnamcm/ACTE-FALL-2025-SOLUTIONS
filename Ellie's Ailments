from collections import deque

N = int(input())
grid = [list(input().strip()) for _ in range(N)]

houses = []
num_hospitals = 0

for i in range(N):
    for j in range(N):
        if grid[i][j] == 'E':
            houses.append((i, j))
        elif grid[i][j] == 'H':
            num_hospitals += 1

#using bfs to get the distances from each house to every cell
dist_sum = [[0]*N for _ in range(N)]

for hx, hy in houses:
    visited = [[False]*N for _ in range(N)]
    q = deque([(hx, hy, 0)])
    while q:
        x, y, d = q.popleft()
        if visited[x][y]:
            continue
        visited[x][y] = True
        dist_sum[x][y] += d
        for dx, dy in [(-1,0),(1,0),(0,-1),(0,1)]:
            nx, ny = x+dx, y+dy
            if 0<=nx<N and 0<=ny<N and not visited[nx][ny]:
                q.append((nx, ny, d+1))


cells = [(dist_sum[i][j], i, j) for i in range(N) for j in range(N) if grid[i][j] != 'E']
cells.sort() 
best_positions = cells[:num_hospitals]

#just making the grid for the output
output_grid = [['#']*N for _ in range(N)]
for x, y in houses:
    output_grid[x][y] = 'E'
for _, x, y in best_positions:
    output_grid[x][y] = 'H'

for row in output_grid:
    print(''.join(row))
