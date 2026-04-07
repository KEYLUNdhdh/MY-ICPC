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
    if (u < graph->n_verts && v < graph->n_verts) {
        if (u != v && graph->edge_matrix[u][v] != no_edge_value) {
            return 1;
        }
    }
    return 0;
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

// Floyd-Warshall算法 本题要求实现
void FloydWarshall(MGraph* graph, int dist[MAX_VERTEX][MAX_VERTEX], int path[MAX_VERTEX][MAX_VERTEX])
{
    int n = graph->n_verts;
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            dist[i][j] = graph->edge_matrix[i][j];
            path[i][j] = -1;
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int len = dist[i][k] + dist[k][j];
                if (len < dist[i][j])
                {
                    path[i][j] = k;
                    dist[i][j] = len;
                }
            }
        }
    }
    return;
}

// 构建图
MGraph* BuildGraph() {
    int n, m;
    scanf("%d %d", &n, &m);
    MGraph* graph = InitGraph(n, INF, 1);
    graph->n_verts = n;
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        InsertEdge(graph, u, v, weight, INF);
    }
    return graph;
}

int main() {
    MGraph* graph = BuildGraph();
    static int dist[MAX_VERTEX][MAX_VERTEX];
    static int path[MAX_VERTEX][MAX_VERTEX];

    FloydWarshall(graph, dist, path);

    printf("dist:\n");
    for (int u = 0; u < graph->n_verts; u++) {
        for (int v = 0; v < graph->n_verts; v++) {
            if (dist[u][v] >= INF) printf("inf ");
            else printf("%d ", dist[u][v]);
        }
        printf("\n");
    }

    printf("path:\n");
    for (int u = 0; u < graph->n_verts; u++) {
        for (int v = 0; v < graph->n_verts; v++) {
            if (path[u][v] != -1)
                printf("%d ", path[u][v]);
            else printf("None ");
        }
        printf("\n");
    }

    return 0;
}