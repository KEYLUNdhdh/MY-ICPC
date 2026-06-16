#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define INF 0x3f3f3f3f
#define MAXN 505

int g[MAXN][MAXN];      // 邻接矩阵存图
int dist[MAXN];         // 存s到各点最短距离
int cnt[MAXN];           // 存最短路径的条数
int max_rescue[MAXN];    // 存最短路径下的最大救援队数
int pre[MAXN];           // 存前驱节点，用于输出路径
bool vis[MAXN];          // Dijkstra标记已确定最短路的节点
int team[MAXN];          // 每个城市的救援队数量

int main() {
    int n, m, s, d;
    scanf("%d%d%d%d", &n, &m, &s, &d);
    // 初始化邻接矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g[i][j] = INF;
        }
    }
    // 读入每个城市救援队
    for (int i = 0; i < n; i++) {
        scanf("%d", &team[i]);
    }
    // 读入边
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u][v] = g[v][u] = w;
    }

    // 初始化所有数组
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        cnt[i] = 0;
        max_rescue[i] = team[s]; // 初始都带上起点的救援队
    }
    dist[s] = 0;
    cnt[s] = 1;

    // 朴素Dijkstra核心
    for (int i = 0; i < n; i++) {
        // 找当前未访问的距离最小的节点
        int u = -1, min_d = INF;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && dist[j] < min_d) {
                min_d = dist[j];
                u = j;
            }
        }
        if (u == -1) break; // 没有更多可达节点
        vis[u] = true;

        // 松弛所有邻接边
        for (int v = 0; v < n; v++) {
            if (!vis[v] && g[u][v] != INF) {
                // 情况1：找到更短的路径 → 更新距离、条数、救援数
                // 往下传递的思想
                if (dist[u] + g[u][v] < dist[v]) {
                    dist[v] = dist[u] + g[u][v];
                    cnt[v] = cnt[u];
                    max_rescue[v] = max_rescue[u] + team[v];
                    pre[v] = u;
                }
                // 情况2：找到同样长度的最短路径 → 更新条数，同时更新最大救援数
                else if (dist[u] + g[u][v] == dist[v]) {
                    cnt[v] += cnt[u];
                    if (max_rescue[u] + team[v] > max_rescue[v]) {
                        max_rescue[v] = max_rescue[u] + team[v];
                        pre[v] = u;
                    }
                }
            }
        }
    }

    // 输出第一行：最短路径数 + 最大救援队
    printf("%d %d\n", cnt[d], max_rescue[d]);
    // 逆序输出路径，递归或者栈都可以，这里用数组逆序更简单
    int path[MAXN], idx = 0;
    int cur = d;
    while (cur != -1) {
        path[idx++] = cur;
        cur = pre[cur];
    }
    // 逆序输出
    for (int i = idx - 1; i >= 0; i--) {
        if (i != idx - 1) printf(" ");
        printf("%d", path[i]);
    }
    printf("\n");
    return 0;
}
