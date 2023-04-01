#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_N 1000
#define MAX_K 300000

int n, m, k;
char yard[MAX_N][MAX_N + 1];
int teleporter[MAX_K][4]; // x1, y1, x2, y2
bool visited[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool in_range(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void bfs(int sx, int sy) {
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    int queue[MAX_N * MAX_N][2];
    int front = 0, rear = 0;
    queue[rear][0] = sx;
    queue[rear][1] = sy;
    visited[sx][sy] = true;
    dist[sx][sy] = 0;
    while (front <= rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (in_range(nx, ny) && !visited[nx][ny] && yard[nx][ny] == '.') {
                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                queue[++rear][0] = nx;
                queue[rear][1] = ny;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%s", yard[i]);
    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d %d %d", &teleporter[i][0], &teleporter[i][1], &teleporter[i][2], &teleporter[i][3]);
        teleporter[i][0]--; // adjust 0-based index
        teleporter[i][1]--;
        teleporter[i][2]--;
        teleporter[i][3]--;
    }
    bfs(0, 0);
    int ans = dist[n - 1][m - 1];
    for (int i = 0; i < k; i++) {
        int x1 = teleporter[i][0], y1 = teleporter[i][1];
        int x2 = teleporter[i][2], y2 = teleporter[i][3];
        if (visited[x1][y1]) {
            ans = min(ans, dist[x1][y1] + abs(x1 - x2) + abs(y1 - y2) + dist[x2][y2]);
        }
        if (visited[x2][y2]) {
            ans = min(ans, dist[x2][y2] + abs(x1 - x2) + abs(y1 - y2) + dist[x1][y1]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
