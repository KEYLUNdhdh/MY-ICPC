#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* 邻接矩阵表示的图 */
typedef int Vertex;    /* 顶点编号类型 */
typedef int GElemSet;  /* 边权重类型 */
typedef struct MGraphNode *MGraph; /* 邻接矩阵表示的图 */
struct MGraphNode {
    int n_verts; /* 顶点数 */
    int m_edges; /* 边数 */
    GElemSet **dist_matrix;/* 距离矩阵 */
    GElemSet **cost_matrix;/* 费用矩阵 */
    Vertex s, d; /* s是出发地的城市编号；d是目的地的城市编号 */
    GElemSet no_edge_value; /* 表述没有边时的权重值 */
    bool directed; /* true为有向图，false为无向图 */
};
#define kMaxV 500   /* 最多顶点数为500 */
#define kMaxNum 1000000000 /* 大于最大距离值的数字 */

void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed);
bool ExistEdge(MGraph graph, Vertex u, Vertex v);
void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet dist, GElemSet cost);
MGraph BuildGraph();
void Dijkstra (MGraph graph, GElemSet dist[], GElemSet cost[]);
/* 邻接矩阵表示的图 结束 */

// O(n ^ 2) 的 dijkstra
void Dijkstra (MGraph graph, GElemSet dist[], GElemSet cost[])
{
    bool *visited = (bool*)malloc(sizeof(bool) * graph->n_verts);
    // 初始化距离和费用
    for (int i = 0; i < graph->n_verts; i++) {
        dist[i] = graph->dist_matrix[graph->s][i];
        cost[i] = graph->cost_matrix[graph->s][i];
        visited[i] = false;
    }

    dist[graph->s] = 0;
    cost[graph->s] = 0;
    visited[graph->s] = true;

    // Dijkstra主循环
    for (int i = 1; i < graph->n_verts; i++) {
        // 找未访问的距离最小的顶点
        Vertex u = -1;
        int min_dist = kMaxNum;
        for (Vertex v = 0; v < graph->n_verts; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        if (u == -1) break; // 所有可达点已经处理完
        visited[u] = true;

        // 松弛所有邻接点
        for (Vertex v = 0; v < graph->n_verts; v++) {
            if (!ExistEdge(graph, u, v)) continue;
            int new_dist = dist[u] + graph->dist_matrix[u][v];
            int new_cost = cost[u] + graph->cost_matrix[u][v];

            if (new_dist < dist[v]) {
                // 找到更短距离，直接更新
                dist[v] = new_dist;
                cost[v] = new_cost;
            } else if (new_dist == dist[v] && new_cost < cost[v]) {
                // 距离相同，费用更低，只更新费用
                cost[v] = new_cost;
            }
        }
    }
    free(visited);
}


int main(void)
{
	MGraph graph;
	GElemSet *dist, *cost;
	
	graph = BuildGraph(); /* 根据输入创建图 */
	dist = (GElemSet *)malloc(sizeof(GElemSet) * graph->n_verts);
	cost = (GElemSet *)malloc(sizeof(GElemSet) * graph->n_verts);
	Dijkstra (graph, dist, cost); /* 用Dijkstra求解 */
	printf("%d %d\n", dist[graph->d], cost[graph->d]);
	
	return 0;
}


void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed)
{
    // 分配二维数组空间
    graph->dist_matrix = (GElemSet**)malloc(sizeof(GElemSet*) * kMaxVertex);
    graph->cost_matrix = (GElemSet**)malloc(sizeof(GElemSet*) * kMaxVertex);
    for (int i = 0; i < kMaxVertex; i++) {
        graph->dist_matrix[i] = (GElemSet*)malloc(sizeof(GElemSet) * kMaxVertex);
        graph->cost_matrix[i] = (GElemSet*)malloc(sizeof(GElemSet) * kMaxVertex);
        // 初始化为无边值
        for (int j = 0; j < kMaxVertex; j++) {
            graph->dist_matrix[i][j] = no_edge_value;
            graph->cost_matrix[i][j] = no_edge_value;
        }
    }
    graph->no_edge_value = no_edge_value;
    graph->directed = directed;
}


bool ExistEdge(MGraph graph, Vertex u, Vertex v)
{
    // 判断矩阵中对应位置是不是无边值
    if (graph->dist_matrix[u][v] != graph->no_edge_value)
        return true;
    else
        return false;
}


void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet dist, GElemSet cost)
{
    // 插入边权重
    graph->dist_matrix[u][v] = dist;
    graph->cost_matrix[u][v] = cost;
    // 如果是无向图，反向也要插入
    if (!graph->directed) {
        graph->dist_matrix[v][u] = dist;
        graph->cost_matrix[v][u] = cost;
    }
}


MGraph BuildGraph()
{
    int n, m, s, d;
    scanf("%d %d %d %d", &n, &m, &s, &d);
    MGraph graph = (MGraph)malloc(sizeof(struct MGraphNode));
    // 初始化图，高速是双向的，所以directed设为false
    InitGraph(graph, kMaxV, kMaxNum, false);
    graph->n_verts = n;
    graph->m_edges = m;
    graph->s = s;
    graph->d = d;

    // 读入所有边并插入
    for (int i = 0; i < m; i++) {
        Vertex u, v;
        GElemSet dist, cost;
        scanf("%d %d %d %d", &u, &v, &dist, &cost);
        InsertEdge(graph, u, v, dist, cost);
    }
    return graph;
}
