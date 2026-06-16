#include <stdio.h>
#include <stdlib.h>

/* 邻接矩阵表示的图定义 */
typedef enum { false, true } bool;
typedef int Vertex;    /* 顶点编号类型 */
typedef int GElemSet;  /* 边权重类型 */
typedef bool VertInfo; /* 顶点信息类型 */
typedef struct MGraphNode *MGraph; /* 邻接矩阵表示的图 */
struct MGraphNode {
    int n_verts; /* 顶点数 */
    int m_edges; /* 边数 */
    GElemSet **edge_matrix;/* 邻接矩阵 */
    VertInfo *visited;     /* 存储顶点访问标识 */
    GElemSet no_edge_value; /* 表述没有边时的权重值 */
    bool directed; /* true为有向图，false为无向图 */
};

void InitGraph(MGraph graph, int kMaxVertex, GElemSet no_edge_value, bool directed);
bool ExistEdge(MGraph graph, Vertex u, Vertex v);
void InsertEdge(MGraph graph, Vertex u, Vertex v, GElemSet weight);
/* 邻接矩阵表示的图定义 结束 */

#define kMaxN 1000
MGraph BuildGraph()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void DFSv(MGraph graph, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsConnected(MGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool CheckDegrees(MGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int main(void)
{
	MGraph graph;
	Vertex u, v;
	
	graph = BuildGraph();
	if (IsConnected(graph) == true) {
		if (CheckDegrees(graph) == true) {
			printf("1\n"); /* 全是偶数度的顶点 */
		}
		else { /* 发现奇数度的顶点 */
			printf("0\n");
		}
	}
	else { /* 图不连通，答案是0 */
		printf("0\n");
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


