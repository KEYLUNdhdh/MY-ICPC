#include <stdio.h>
#include <stdlib.h>

#define KMAXN 1000
#define NO_EDGE 0  // 无边标记

typedef struct {
    int n_verts;
    int m_edges;
    int edge_matrix[KMAXN][KMAXN];
    int visited[KMAXN];
    int no_edge_value;
    int directed;
} MGraphNode;

// 初始化图
MGraphNode* InitGraph(int kMaxVertex, int no_edge_value, int directed) {
    MGraphNode* graph = (MGraphNode*)malloc(sizeof(MGraphNode));
    graph->n_verts = 0;
    graph->m_edges = 0;
    graph->no_edge_value = no_edge_value;
    graph->directed = directed;
    for(int i=0;i<kMaxVertex;i++){
        graph->visited[i] = 0;
        for(int j=0;j<kMaxVertex;j++)
            graph->edge_matrix[i][j] = no_edge_value;
    }
    return graph;
}

// 插入边
void InsertEdge(MGraphNode* graph, int u, int v, int weight) {
    graph->edge_matrix[u][v] = weight;
    graph->m_edges++;
    if(!graph->directed)
        graph->edge_matrix[v][u] = weight;
}


// 判断欧拉回路 本题要求实现
int HasEulerCircuit(MGraphNode* graph)
{
    int n = graph->n_verts;
    int d[KMAXN] = {0};
    // 1. 统计每个顶点的度数，并检查是否全为偶数
    //也就是连边数
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            if(graph->edge_matrix[i][j] != graph->no_edge_value)
                d[i]++;
        }
        // 如果存在奇数度的顶点，不可能存在欧拉回路，直接返回 0
        if(d[i] % 2)
            return 0;
    }
    // 2. 检查连通性 (找第一个有边的顶点作为起点)
    int s = -1;
    for (int i = 0; i < n;i++)
    {
        if(d[i] > 0)
        {
            s = i;
            break;
        }
    }
    // 如果全图一条边都没有（所有顶点度数都为0），算作存在欧拉回路
    if(s == -1)
        return 1;
    //跑bfs，判断图是否连通了
    int queue[KMAXN];
    int front = 0;
    int rear = 0;
    queue[rear++] = s;
    graph->visited[s] = 1;

    while(front < rear)
    {
        int u = queue[front++];
        for (int v = 0; v < n;v++)
        {
            if(graph->edge_matrix[u][v] != graph->no_edge_value && !graph->visited[v])
            {
                graph->visited[v]++;
                queue[rear++] = v;
            }
        }
    }
    for (int i = 0; i < n;i++)
    {
        if(d[i] > 0 && !graph->visited[i])
        {
            return 0;
        }
    }
    return 1;
}

// 构建图
MGraphNode* BuildGraph() {
    int n, m;
    MGraphNode* graph = InitGraph(KMAXN, NO_EDGE, 0); // 无向图
    scanf("%d %d", &n, &m);
    graph->n_verts = n;
    for(int i=0;i<m;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--; // 转为0-indexed
        InsertEdge(graph, u, v, 1);
    }
    return graph;
}

int main() {
    MGraphNode* graph = BuildGraph();
    printf("%d\n", HasEulerCircuit(graph));
    return 0;
}