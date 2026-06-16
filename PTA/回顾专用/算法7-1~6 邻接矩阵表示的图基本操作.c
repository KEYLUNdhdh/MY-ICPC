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
#define NIL -1 /* 顶点不存在时的返回值 */

void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed);
int NumberOfVerts(MGraph graph);
bool ExistEdge(MGraph graph, Vertex u, Vertex v);
Vertex FirstAdjVert (MGraph graph, Vertex v);
void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet weight);
void RemoveEdge(MGraph graph, Vertex u, Vertex v);
void RemoveVert(MGraph graph, Vertex v);

MGraph BuildGraph()
{
	MGraph g = (MGraph)malloc(sizeof(struct MGraphNode));
	int MAXN, noedgeval;
	scanf("%d %d", &MAXN, &noedgeval);
	InitGraph(g, MAXN, noedgeval, 1);
	return g;
}


int main(void)
{
	MGraph graph;
	Vertex u, v;
	
	graph = BuildGraph();
	printf("邻接矩阵为：\n");
	for (u=0; u<graph->n_verts; u++) {
		for (v=0; v<graph->n_verts; v++) {
			printf("%d ", graph->edge_matrix[u][v]);
		}
		printf("\n");
	}
	printf("顶点数 = %d\n", NumberOfVerts(graph));
	scanf("%d %d\n", &u, &v);
	printf("<%d, %d> 的存在性 = %d\n", u, v, ExistEdge(graph, u, v));
	scanf("%d %d\n", &u, &v);
	printf("<%d, %d> 的存在性 = %d\n", u, v, ExistEdge(graph, u, v));
	scanf("%d\n", &v);
	printf("顶点%d的第一个邻接点 = %d\n", v, FirstAdjVert (graph,v));
	scanf("%d %d\n", &u, &v);
	RemoveEdge(graph, u, v);
	printf("<%d, %d> 的存在性 = %d\n", u, v, ExistEdge(graph, u, v));
	scanf("%d\n", &v);
	printf("待删除的顶点信息为 %c\n", graph->ver_list[v]);
	RemoveVert(graph, v);
	printf("当前顶点数 = %d\n", graph->n_verts);
	printf("当前边数 = %d\n", graph->m_edges);
	for (v=0; v<graph->n_verts; v++) {
		printf("%c", graph->ver_list[v]);
	}
	printf("\n");
	printf("邻接矩阵为：\n");
	for (u=0; u<graph->n_verts; u++) {
		for (v=0; v<graph->n_verts; v++) {
			printf("%d ", graph->edge_matrix[u][v]);
		}
		printf("\n");
	}
	return 0;
}

void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed)
{
	int m;
	scanf("%d %d", &graph->n_verts, &m);
	graph->edge_matrix = (int **)malloc(kMaxVertex * sizeof(int *));
	for (int i = 0; i < kMaxVertex;i++)
		graph->edge_matrix[i] = (int *)malloc(kMaxVertex * sizeof(int));

	for (int i = 0; i < graph->n_verts;i++)
		for (int j = 0; j < graph->n_verts;j++)
			graph->edge_matrix[i][j] = no_edge_value;
	
	graph->no_edge_value = no_edge_value;
	graph->directed = directed;
	graph->ver_list = (char *)malloc(kMaxVertex * sizeof(char));
	for (int i = 0; i < graph->n_verts;i++)
		scanf(" %c", &graph->ver_list[i]);

	for (int i = 0; i < m;i++)
	{
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		InsertEdge(graph, u, v, w);
	}
}


/* 算法7-1: 获取图的顶点个数 NumberOfVerts(graph) */
int NumberOfVerts(MGraph graph)
{
	return graph->n_verts;
}

/* 算法7-1 结束 */ 

/* 算法7-2: 判断边是否存在  ExistEdge(graph, u, v) */
bool ExistEdge(MGraph graph, Vertex u, Vertex v)
{
    if(graph->edge_matrix[u][v] != graph->no_edge_value)
		return true;

	return false;
}

/* 算法7-2 结束 */ 

/* 算法7-3: 找顶点的第一个邻接点  FirstAdjVert (graph,v) */
Vertex FirstAdjVert (MGraph graph, Vertex v)
{
	for (int i = 0; i < graph->n_verts;i++)
		if(ExistEdge(graph, v, i))
			return i;
	return -1;
}

/* 算法7-3 结束 */ 

/* 算法7-4: 向图中插入边 InsertEdge(graph, u,v,weight) */
void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet weight)
{
	if(graph->edge_matrix[u][v] == graph->no_edge_value)
		graph->m_edges++;

	graph->edge_matrix[u][v] = weight;
	if(!graph->directed)
		graph->edge_matrix[v][u] = weight;

	return;
}

/* 算法7-4 结束 */ 

/* 算法7-5: 从图中删除边 RemoveEdge(graph, u,v) */
void RemoveEdge(MGraph graph, Vertex u, Vertex v)
{
	if(graph->edge_matrix[u][v] != graph->no_edge_value)
		graph->m_edges--;

	graph->edge_matrix[u][v] = graph->no_edge_value;
	if(!graph->directed)
		graph->edge_matrix[v][u] = graph->no_edge_value;

	return;
}

/* 算法7-5 结束 */ 

/* 算法7-6: 从图中删除顶点及所有邻接于该顶点的边 RemoveVert(graph,v) */
void RemoveVert(MGraph graph, Vertex v) {
    Vertex last = graph->n_verts - 1; // 最后一个顶点的编号
    if (v == last) { // 如果删除的就是最后一个顶点，直接减少顶点数即可
        graph->n_verts--;
        goto recount_edges;
    }

    // 1. 用最后一个顶点覆盖待删除顶点的信息
    graph->ver_list[v] = graph->ver_list[last];
    // 2. 复制最后一行边到待删除顶点行
    for (int j = 0; j < graph->n_verts; j++) {
        graph->edge_matrix[v][j] = graph->edge_matrix[last][j];
    }
    // 3. 复制最后一列边到待删除顶点列
    for (int i = 0; i < graph->n_verts; i++) {
        graph->edge_matrix[i][v] = graph->edge_matrix[i][last];
    }

    // 4. 顶点数减1
    graph->n_verts--;

    // 重新统计总边数（删除顶点会删除所有和它相连的边）
recount_edges:
    int cnt = 0;
    for (int i = 0; i < graph->n_verts; i++) {
        for (int j = 0; j < graph->n_verts; j++) {
            if (graph->edge_matrix[i][j] != graph->no_edge_value) {
                cnt++;
            }
        }
    }
    graph->m_edges = cnt;
}

/* 算法7-6 结束 */ 

