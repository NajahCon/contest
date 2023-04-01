#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAXN 1000
#define MAXK 300000

int N, M, K;
char yard[MAXN][MAXN + 1];  // yard map
int teleports[MAXK][4];     // teleport locations
int teleport_map[MAXN][MAXN];  // mapping teleport locations to indices

int dist[MAXN][MAXN];  // distance from (1, 1) to each point in the yard
bool visited[MAXN][MAXN];  // visited flag for BFS

int dx[] = {1, -1, 0, 0};  // right, left, down, up
int dy[] = {0, 0, 1, -1};

int queue[MAXN * MAXN][2];  // queue for BFS

int bfs(int sx, int sy) {
    // initialize distance and visited arrays
    memset(dist, -1, sizeof(dist));
    memset(visited, false, sizeof(visited));
    dist[sx][sy] = 0;
    visited[sx][sy] = true;

    // initialize queue
    int front = 0, rear = 0;
    queue[rear][0] = sx;
    queue[rear][1] = sy;
    rear++;

    // BFS loop
    while (front != rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        // check if reached the target
        if (x == N-1 && y == M-1) {
            return dist[x][y];
        }

        // check if can teleport from this point
        int k = teleport_map[x][y];
        if (k != -1) {
            int tx = teleports[k][2];
            int ty = teleports[k][3];
            if (!visited[tx][ty]) {
                dist[tx][ty] = dist[x][y] + 1;
                visited[tx][ty] = true;
                queue[rear][0] = tx;
                queue[rear][1] = ty;
                rear++;
            }
        }

        // move in all possible directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < N && ny >= 0 && ny < M &&
                    yard[nx][ny] == '.' && !visited[nx][ny]) {
                dist[nx][ny] = dist[x][y] + 1;
                visited[nx][ny] = true;
                queue[rear][0] = nx;
                queue[rear][1] = ny;
                rear++;
            }
        }
    }

    // target not reachable
    return -1;
}

int main() {
    scanf("%d %d %d", &N, &M, &K);

    // read yard map
    for (int i = 0; i < N; i++) {
        scanf("%s", yard[i]);
    }

    // initialize teleport map
    memset(teleport_map, -1, sizeof(teleport_map));

    // read teleport locations
    for (int i = 0; i < K; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--;
