#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
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

/* 算法8-3: 求所有点对间最短路的Floyd-Warshall算法 FloydWarshall (graph, path, dist) */
void FloydWarshall(MGraph graph, Vertex path[][kMaxV], GElemSet dist[][kMaxV])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法8-3 结束 */ 

int main(void)
{
	MGraph graph;
	Vertex u, v;
	GElemSet dist[kMaxV][kMaxV];
	Vertex path[kMaxV][kMaxV];
	
	graph = BuildGraph();
	FloydWarshall(graph, path, dist);
	printf("dist:\n");
	for (u=0; u<graph->n_verts; u++) {
		for (v=0; v<graph->n_verts; v++) {
			printf("%d ", dist[u][v]);
		}
		printf("\n");
	}
	printf("path:\n");
	for (u=0; u<graph->n_verts; u++) {
		for (v=0; v<graph->n_verts; v++) {
			printf("%d ", path[u][v]);
		}
		printf("\n");
	}
	return 0;
}


void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool ExistEdge(MGraph graph, Vertex u, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet weight)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


MGraph BuildGraph()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


