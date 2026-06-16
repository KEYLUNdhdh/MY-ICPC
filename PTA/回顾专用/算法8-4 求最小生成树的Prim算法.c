#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Vertex;    /* 顶点编号类型 */
typedef int GElemSet;  /* 边权重类型 */
typedef char VertInfo; /* 顶点信息类型 */
typedef struct MGraphNode *MGraph; /* 邻接矩阵表示的图 */
struct MGraphNode {
    int n_verts; /* 顶点数 */
    int m_edges; /* 边数 */
    GElemSet **edge_matrix;/* 邻接矩阵 */
    VertInfo *ver_list; /* 存储顶点信息 */
    GElemSet no_edge_value; /* 表述没有边时的权重值 */
    bool directed; /* true为有向图，false为无向图 */
};
#define NIL -1      /* 顶点不存在时的返回值 */
#define kMaxV 100   /* 最多顶点数 */
#define kMaxNum 1e9 /* 大于最大距离值的数字 */

void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed);
bool ExistEdge(MGraph graph, Vertex u, Vertex v);
void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet weight);
MGraph BuildGraph();

#define ErrorCode -1
Vertex parent[kMaxV];
/* 算法8-4：求最小生成树的Prim算法 Prim(graph) */
GElemSet Prim(MGraph graph)
{
    int n = graph->n_verts;
    int dist[kMaxV];
    bool visited[kMaxV];
    int total = 0, cnt = 0;

    // 初始化
    for (int i = 0; i < n; i++) {
        dist[i] = graph->edge_matrix[0][i];
        visited[i] = false;
        parent[i] = 0;
    }
    visited[0] = true;
    parent[0] = -1;
    cnt = 1;

    //跑 n - 1 轮
    for (int i = 1; i < n; i++) {
        // 找距离当前点集最近且未被访问的顶点，等长选编号小的
        int min_dist = kMaxNum;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        // 找不到说明图不连通，没有最小生成树
        if (u == -1) break;

        visited[u] = true;
        total += dist[u];
        cnt++;

        // 更新距离和父节点
        // 这里好好感受一下
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph->edge_matrix[u][v] < dist[v]) {
                dist[v] = graph->edge_matrix[u][v];
                parent[v] = u;
            }
        }
    }

    // 若不能收录所有顶点，不存在最小生成树
    if (cnt != n) {
        return -1;
    }
    return total;
}

/* 算法8-4 结束 */

int main(void)
{
    MGraph graph;
    Vertex u;

    graph = BuildGraph();
    printf("total weight = %d\n", Prim(graph));
    for (u = 0; u < graph->n_verts; u++) {
        printf("%d ", parent[u]);
    }
    printf("\n");
    return 0;
}

void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed)
{
    graph->n_verts = 0;
    graph->m_edges = 0;
    graph->directed = directed;
    graph->no_edge_value = no_edge_value;

    // 分配邻接矩阵空间
    graph->edge_matrix = (GElemSet**)malloc(kMaxVertex * sizeof(GElemSet*));
    for (int i = 0; i < kMaxVertex; i++) {
        graph->edge_matrix[i] = (GElemSet*)malloc(kMaxVertex * sizeof(GElemSet));
        for (int j = 0; j < kMaxVertex; j++) {
            graph->edge_matrix[i][j] = no_edge_value;
        }
    }

    graph->ver_list = (VertInfo*)malloc(kMaxVertex * sizeof(VertInfo));
}


bool ExistEdge(MGraph graph, Vertex u, Vertex v)
{
    if (graph->edge_matrix[u][v] != graph->no_edge_value) {
        return true;
    }
    return false;
}


void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet weight)
{
    graph->edge_matrix[u][v] = weight;
    // 无向图，双向赋值
    if (!graph->directed) {
        graph->edge_matrix[v][u] = weight;
    }
    graph->m_edges++;
}


MGraph BuildGraph()
{
    int n, m;
    scanf("%d %d", &n, &m);
    // 分配图结构空间
    MGraph graph = (MGraph)malloc(sizeof(struct MGraphNode));
    InitGraph(graph, kMaxV, kMaxNum, false);
    graph->n_verts = n;

    for (int i = 0; i < m; i++) {
        Vertex u, v;
        GElemSet w;
        scanf("%d %d %d", &u, &v, &w);
        InsertEdge(graph, u, v, w);
    }
    return graph;
}
