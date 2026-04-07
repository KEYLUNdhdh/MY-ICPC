#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 1010

typedef struct {
    int n_verts;                 // 顶点数
    int m_edges;                 // 边数
    int edge_matrix[MAX_VERTEX][MAX_VERTEX]; // 邻接矩阵
    char* ver_list[MAX_VERTEX];  // 存储顶点信息
    int no_edge_value;           // 表示没有边时的权重值
    int directed;                // 1为有向图，0为无向图
} MGraph;

// 初始化图
MGraph* InitGraph(int kMaxVertex, int no_edge_value, int directed) {
    MGraph* graph = (MGraph*)malloc(sizeof(MGraph));
    graph->n_verts = 0;
    graph->m_edges = 0;
    graph->no_edge_value = no_edge_value;
    graph->directed = directed;
    for (int i = 0; i < kMaxVertex; i++) {
        graph->ver_list[i] = NULL;
        for (int j = 0; j < kMaxVertex; j++) {
            graph->edge_matrix[i][j] = no_edge_value;
        }
    }
    return graph;
}

// 本题要求实现
int NumberOfEdges(MGraph* graph)
{
    return graph->m_edges;
}

// 本题要求实现
int NumberOfVerts(MGraph* graph)
{
    return graph->n_verts;
}
// 判断边是否存在 本题要求实现
int ExistEdge(MGraph* graph, int u, int v)
{
    if(graph->edge_matrix[u][v] == graph->no_edge_value)
        return 0;
    else
        return 1;
}

// 找顶点的第一个邻接点  本题要求实现
int FirstAdjVert(MGraph* graph, int v)
{
    int f = 0;
    for (int i = 0; i < graph->n_verts;i++)
    {
        if(graph->edge_matrix[v][i] != graph->no_edge_value)
        {
            f = 1;
            return i;
        }
    }
    if(!f)
        return -1;
}
// 向图中插入边  本题要求实现
void InsertEdge(MGraph* graph, int u, int v, int weight)
{
    if(graph->edge_matrix[u][v] != graph->no_edge_value)
        return;
    else
    {
        graph->edge_matrix[u][v] = weight;
        graph->m_edges++;
    }
    if(graph->directed == 0)
    {
        if(graph->edge_matrix[v][u] != graph->no_edge_value)
            return;
        else
            graph->edge_matrix[v][u] = weight;
    }
    return;
}
// 从图中删除边  本题要求实现
void RemoveEdge(MGraph* graph, int u, int v)
{
    if(graph->edge_matrix[u][v] != graph->no_edge_value)
    {
        graph->edge_matrix[u][v] = graph->no_edge_value;
        graph->m_edges--;
    }
    if(graph->directed == 0)
    {
        if(graph->edge_matrix[v][u] != graph->no_edge_value)
        {
            graph->edge_matrix[v][u] = graph->no_edge_value;
        }
    }
    return;
}
// 从图中删除顶点及所有邻接边  本题要求实现
void RemoveVert(MGraph* graph, int v)
{
    if(v < 0 || v >= graph->n_verts)
    {
        printf("error: %d is not exist\n", v);
        return;
    }
    else
    {
        int removed_edges = 0;
        for (int i = 0; i < graph->n_verts;i++)
        {
            if(graph->edge_matrix[v][i] != graph->no_edge_value)
                removed_edges++;
            if(graph->directed == 1 && i != v)
            {
                if(graph->edge_matrix[i][v] != graph->no_edge_value)
                    removed_edges++;
            }
        }
        graph->m_edges -= removed_edges;
        int last_idx = graph->n_verts - 1;
        if(v != last_idx)
        {
            if(graph->ver_list[v])
                free(graph->ver_list[v]);
            graph->ver_list[v] = graph->ver_list[last_idx];
            graph->ver_list[last_idx] = NULL;
            for (int i = 0; i < graph->n_verts;i++)
            {
                graph->edge_matrix[v][i] = graph->edge_matrix[last_idx][i];
            }
            for (int i = 0; i < graph->n_verts;i++)
            {
                graph->edge_matrix[i][v] = graph->edge_matrix[i][last_idx];
            }
            graph->edge_matrix[v][v] = graph->edge_matrix[last_idx][last_idx];
        }
        else
        {
            free(graph->ver_list[last_idx]);
            graph->ver_list[last_idx] = NULL;
        }
    }
    graph->n_verts--;
}
// 构建图
MGraph* BuildGraph() {
    int kMaxVertex, no_edge_value, directed;
    scanf("%d %d %d", &kMaxVertex, &no_edge_value, &directed);
    MGraph* graph = InitGraph(kMaxVertex, no_edge_value, directed);

    int n, m;
    scanf("%d %d", &n, &m);

    char temp[50];
    for (int i = 0; i < n; i++) {
        scanf("%s", temp);
        graph->ver_list[i] = (char*)malloc(strlen(temp)+1);
        strcpy(graph->ver_list[i], temp);
    }
    graph->n_verts = n;

    for (int i = 0; i < m; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        InsertEdge(graph, u, v, weight);
    }
    return graph;
}

// 打印图
void PrintGraph(MGraph* g) {
    printf("adjacency matrix:\n");
    for (int u = 0; u < g->n_verts; u++) {
        for (int v = 0; v < g->n_verts; v++) {
            printf("%d ", g->edge_matrix[u][v]);
        }
        printf("\n");
    }
    printf("vex num = %d, edge num = %d\n", NumberOfVerts(g), NumberOfEdges(g));
}

int main() {
    MGraph* graph = BuildGraph();
    PrintGraph(graph);

    int u, v;
    scanf("%d %d", &u, &v);
    if (ExistEdge(graph, u, v))
        printf("Existence of <%d, %d> = True\n", u, v);
    else 
        printf("Existence of <%d, %d> = False\n", u, v);
    scanf("%d %d", &u, &v);
    if (ExistEdge(graph, u, v))
        printf("Existence of <%d, %d> = True\n", u, v);
    else 
        printf("Existence of <%d, %d> = False\n", u, v);

    scanf("%d", &v);
    
    int k = FirstAdjVert(graph, v);
    if (k != -1)
        printf("the first adjacent vertex of %d = %d\n", v, k);
    else 
        printf("the first adjacent vertex of %d = None\n", v);

    scanf("%d %d", &u, &v);
    RemoveEdge(graph, u, v);
    if (ExistEdge(graph, u, v))
        printf("Existence of <%d, %d> = True\n", u, v);
    else 
        printf("Existence of <%d, %d> = False\n", u, v);

    scanf("%d", &v);
    RemoveVert(graph, v);
    PrintGraph(graph);

    return 0;
}
