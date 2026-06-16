#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INF 0x3f3f3f3f
#define MAXN 505

int g[MAXN][MAXN];
int dist[MAXN];
bool vis[MAXN];
int cnt[MAXN];          // 记录每个节点当前最小边的条数
bool vis_all[MAXN];
int n, m;

void dfs(int u) {
    vis_all[u] = true;
    for (int v = 1; v <= n; v++) {
        if (g[u][v] != INF && !vis_all[v]) {
            dfs(v);
        }
    }
}

int main() {
    
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) g[i][j] = INF;
        g[i][i] = 0;
    }

    bool has_multiple = false;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (w < g[u][v]) {
            g[u][v] = g[v][u] = w;
        } else if (w == g[u][v]) {
            has_multiple = true;   // 存在权值相同的重边
        }
    }

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = false;
        cnt[i] = 0;
    }
    dist[1] = 0;
    int total = 0;
    bool unique = true;

    for (int i = 0; i < n; i++) {
        int min_dist = INF, u = -1;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) { // 图不连通
            int cnt_block = 0;
            for (int i = 1; i <= n; i++) vis_all[i] = false;
            for (int i = 1; i <= n; i++) {
                if (!vis_all[i]) {
                    cnt_block++;
                    dfs(i);
                }
            }
            printf("No MST\n%d\n", cnt_block);
            return 0;
        }

        vis[u] = true;
        total += dist[u];

        // 若 u 不是起点且存在多条最小边到达 u，则不唯一
        if (u != 1 && cnt[u] > 1) {
            unique = false;
        }

        // 更新其他节点的距离
        for (int v = 1; v <= n; v++) {
            if (vis[v]) continue;
            if (g[u][v] < dist[v]) {
                dist[v] = g[u][v];
                cnt[v] = 1;          // 更小边，重置计数
            } else if (g[u][v] == dist[v] && dist[v] != INF) {
                cnt[v]++;            // 等权边，计数增加
            }
        }
    }

    printf("%d\n", total);
    if (unique && !has_multiple)
        printf("Yes\n");
    else
        printf("No\n");

    return 0;
}