#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX 1010
#define INF 1000000000

typedef struct {
    int n_verts;                 // 顶点数
    int m_edges;                 // 边数
    int edge_matrix[MAX_VERTEX][MAX_VERTEX]; // 邻接矩阵
    int directed;                // 1有向图，0无向图
} MGraph;

// 初始化图
MGraph* InitGraph(int kMaxVertex, int no_edge_value, int directed) {
    MGraph* graph = (MGraph*)malloc(sizeof(MGraph));
    graph->n_verts = 0;
    graph->m_edges = 0;
    graph->directed = directed;
    for (int i = 0; i < kMaxVertex; i++) {
        for (int j = 0; j < kMaxVertex; j++) {
            if (i == j) graph->edge_matrix[i][j] = 0;
            else graph->edge_matrix[i][j] = no_edge_value;
        }
    }
    return graph;
}

// 判断边是否存在
int ExistEdge(MGraph* graph, int u, int v, int no_edge_value) {
    int ret = 0;
    if (u < graph->n_verts && v < graph->n_verts) {
        if (u != v && graph->edge_matrix[u][v] != no_edge_value) {
            ret = 1;
        }
    }
    return ret;
}

// 插入边
void InsertEdge(MGraph* graph, int u, int v, int weight, int no_edge_value) {
    if (!ExistEdge(graph, u, v, no_edge_value)) {
        graph->edge_matrix[u][v] = weight;
        graph->m_edges += 1;
        if (!graph->directed) {
            graph->edge_matrix[v][u] = weight;
        }
    }
}

// 构建图
MGraph* BuildGraph() {
    int n_verts, m_edges;
    scanf("%d %d", &n_verts, &m_edges);
    MGraph* graph = InitGraph(n_verts, INF, 1);
    graph->n_verts = n_verts;

    for (int i = 0; i < m_edges; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        InsertEdge(graph, u, v, weight, INF);
    }
    return graph;
}

// Dijkstra 最短路径 本题要求实现
void Dijkstra(MGraph* graph, int s, int path[], int dist[])
{
    int n = graph->n_verts;
    int visited[MAX_VERTEX] = {0};
    dist[s] = 0;
    path[s] = s;
    for (int count = 0; count < n;count++)//最多跑n遍，但实际上处理好了可以通过break直接出去
    {
        int u = -1;
        int min_dist = INF;
        for (int i = 0; i < n;i++)
        {
            if(!visited[i] && dist[i] < min_dist)
            {
                min_dist = dist[i];
                u = i;
            }
        }
        if(u == -1)
            break;
        visited[u] = 1;
        for (int v = 0; v < n;v++)
        {
            if(!visited[v] && graph->edge_matrix[u][v] != INF && u != v)
            {
                int weight = graph->edge_matrix[u][v];
                int new_dist = dist[u] + weight;
                if(new_dist < dist[v])
                {
                    dist[v] = new_dist;
                    path[v] = u;
                }
                else if(new_dist == dist[v])
                {
                    if(dist[u] < dist[path[v]])
                        path[v] = u;
                }
            }
        }
    }
}

int main() {
    MGraph* graph = BuildGraph();
    int path[MAX_VERTEX], dist[MAX_VERTEX];
    for (int i = 0; i < graph->n_verts; i++) {
        path[i] = -1;
        dist[i] = INF;
    }

    Dijkstra(graph, 0, path, dist);

    for (int v = 0; v < graph->n_verts; v++) {
        if (dist[v] == INF)
            printf("v[%d]: dist=inf, path=%d\n", v, path[v]);
        else
            printf("v[%d]: dist=%d, path=%d\n", v, dist[v], path[v]);
    }

    return 0;
}