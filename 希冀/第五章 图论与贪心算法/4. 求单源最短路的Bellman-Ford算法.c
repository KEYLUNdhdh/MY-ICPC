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

// Bellman-Ford算法 本题要求实现
int BellmanFord(MGraph* graph, int s, int dist[])
{
    int n = graph->n_verts;
    for (int i = 0; i < n;i++)
        dist[i] = INF;//初始化
    dist[s] = 0;//起点到自己是0
    for (int k = 1; k < n;k++)
    {
        int relaxed = 0;//统计是否有松驰过
        //由于是邻接表，我们要完全遍历
        for (int u = 0; u < n;u++)
            for (int v = 0; v < n;v++)
            {
                if(u != v && graph->edge_matrix[u][v] != INF)
                {
                    int weight = graph->edge_matrix[u][v];
                    if(dist[u] != INF && dist[u] + weight < dist[v])
                    {
                        dist[v] = dist[u] + weight;
                        relaxed = 1;
                    }
                }
            }
        if(!relaxed)//松弛完全
            break;
    }
    for (int u = 0; u < n;u++)
    {
        for (int v = 0; v < n;v++)
        {
            if(u != v && graph->edge_matrix[u][v] != INF)
            {
                int weight = graph->edge_matrix[u][v];
                if(dist[u] != INF && dist[u] + weight < dist[v])
                    return 0;
            }
        }
    }
    return 1;
}

int main() {
    MGraph* graph = BuildGraph();
    int dist[MAX_VERTEX];
    int ret = BellmanFord(graph, 0, dist);
    if (ret) {
        printf("BF returns True\n");
        for (int v = 0; v < graph->n_verts; v++) {
            if (dist[v] == INF)
                printf("dist[%d] = inf\n", v);
            else
                printf("dist[%d] = %d\n", v, dist[v]);
        }
    } else {
        printf("BF returns False\n");
    }
    return 0;
}