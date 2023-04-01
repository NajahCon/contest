#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 1000
#define MAXK 300000
#define INF 1000000000

int n, m, k;
char yard[MAXN+1][MAXN+1];
int dist[MAXN+1][MAXN+1];
bool visited[MAXN+1][MAXN+1];
int tele_x1[MAXK], tele_y1[MAXK], tele_x2[MAXK], tele_y2[MAXK];
int queue[MAXN*MAXN+1][2];

// Function to check if a point is inside the yard
bool isInside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

// Function to add a point to the queue if it hasn't been visited yet
void addPointToQueue(int x, int y, int d, int *front, int *rear) {
    if (isInside(x, y) && !visited[x][y]) {
        visited[x][y] = true;
        dist[x][y] = d;
        queue[*rear][0] = x;
        queue[*rear][1] = y;
        (*rear)++;
    }
}

// Function to do a BFS traversal of the yard
void bfs() {
    int front = 0, rear = 0;
    memset(visited, false, sizeof(visited));
    visited[1][1] = true;
    dist[1][1] = 0;
    queue[rear][0] = 1;
    queue[rear][1] = 1;
    rear++;

    while (front != rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        // Check if we have reached the destination
        if (x == n && y == m) {
            printf("%d\n", dist[n][m]);
            return;
        }

        // Add the adjacent points to the queue
        addPointToQueue(x+1, y, dist[x][y]+1, &front, &rear);
        addPointToQueue(x-1, y, dist[x][y]+1, &front, &rear);
        addPointToQueue(x, y+1, dist[x][y]+1, &front, &rear);
        addPointToQueue(x, y-1, dist[x][y]+1, &front, &rear);

        // Check if there is a teleporter at the current point
        for (int i = 0; i < k; i++) {
            if (x == tele_x1[i] && y == tele_y1[i]) {
                addPointToQueue(tele_x2[i], tele_y2[i], dist[x][y]+1, &front, &rear);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%s", yard[i]+1);
    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d %d %d", &tele_x1[i], &tele_y1[i], &tele_x2[i], &tele_y2[i]);
    }
    bfs();
    return 0;
}
