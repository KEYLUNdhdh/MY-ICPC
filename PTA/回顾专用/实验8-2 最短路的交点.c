#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define INF 0x3f3f3f3f
#define MAXN 1005
#define MAXM 3005

// 邻接表节点
typedef struct Edge {
    int to, w;
    struct Edge *next;
} Edge;

Edge *g1[MAXN], *g2[MAXN]; // g1原图 g2反图
int d1[MAXN], d2[MAXN], d3[MAXN], d4[MAXN]; // 存四次最短路结果
bool vis[MAXN];
int heap[MAXM * 2], sz; // 手写堆，满足代码长度限制

// 堆操作
void push(int dist_v, int v) {
    heap[++sz] = dist_v * (MAXN + 1) + v;// 这个映射神了
    int cur = sz;
    while (cur > 1 && heap[cur] < heap[cur / 2]) {
        int tmp = heap[cur]; heap[cur] = heap[cur / 2]; heap[cur / 2] = tmp;
        cur /= 2;
    }
}

void pop() {
    heap[1] = heap[sz--];
    int cur = 1;
    while (cur * 2 <= sz) {
        int child = cur * 2;
        if (child + 1 <= sz && heap[child + 1] < heap[child]) child++;
        if (heap[child] < heap[cur]) {
            int tmp = heap[cur]; heap[cur] = heap[child]; heap[child] = tmp;
            cur = child;
        } else break;
    }
}

// Dijkstra模板
void dijkstra(Edge *g[], int n, int start, int dist[]) {
    sz = 0;
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = false;
    }
    dist[start] = 0;
    push(0, start);
    while (sz > 0) {
        int val = heap[1]; pop();
        int u = val % (MAXN + 1);
        int d_u = val / (MAXN + 1);
        if (vis[u]) continue;
        vis[u] = true;
        for (Edge *e = g[u]; e; e = e->next) {
            int v = e->to, w = e->w;
            if (dist[v] > d_u + w) {
                dist[v] = d_u + w;
                push(dist[v], v);
            }
        }
    }
}

// 加边，同时加原图和反图
void add_edge(int u, int v, int w) {
    Edge *e1 = (Edge*)malloc(sizeof(Edge));
    e1->to = v; e1->w = w; e1->next = g1[u]; g1[u] = e1;
    Edge *e2 = (Edge*)malloc(sizeof(Edge));
    e2->to = u; e2->w = w; e2->next = g2[v]; g2[v] = e2;
}

int main() {
    int n, m, u, v, s, t;
    scanf("%d%d%d%d%d%d", &n, &m, &u, &v, &s, &t);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        add_edge(a, b, w);
    }

    // 跑四次最短路
    dijkstra(g1, n, u, d1);   // d1: u到所有点距离
    dijkstra(g1, n, s, d2);   // d2: s到所有点距离
    dijkstra(g2, n, v, d3);   // d3: 所有点到v距离 = 反图v到所有点距离
    dijkstra(g2, n, t, d4);   // d4: 所有点到t距离 = 反图t到所有点距离

    int ans[MAXN], cnt = 0;
    for (int w = 1; w <= n; w++) {
        bool is_uv = (d1[w] + d3[w] == d1[v]);
        bool is_st = (d2[w] + d4[w] == d2[t]);
        if (is_uv && is_st) ans[cnt++] = w;
    }

    if (d1[v] == INF || d2[t] == INF) {
        printf("No Intersection\n");
        return 0;
    }
    if (cnt == 0) {
        printf("No Intersection\n");
    } else {
        for (int i = 0; i < cnt; i++) {
            if (i > 0) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
