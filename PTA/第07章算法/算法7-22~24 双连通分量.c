#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef int Vertex;    /* 顶点编号类型 */
typedef char VertInfo; /* 顶点信息类型 */

typedef struct EdgeNode *Position; /* 指针即结点位置 */
struct EdgeNode {
    Vertex dest;     /* 边的另一端点编号 */
    Position next;   /* 线性表中下一个元素的位置 */
};
typedef struct HeadNode *AdjList; /* 邻接表 */
struct HeadNode {
    Position adj;  /* 邻接表头指针 */
    VertInfo data; /* 存储顶点信息 */
};
typedef struct LGraphNode *LGraph; /* 邻接表表示的图 */
struct LGraphNode {
    int n_verts; /* 顶点数 */
    int m_edges; /* 边数 */
    AdjList *ver_list; /* 存储顶点邻接表 */
    bool directed; /* true为有向图，false为无向图 */
};

typedef struct EulerNode *ECList; /* 欧拉回路链表 */
struct EulerNode {
    Vertex ver;    /* 顶点编号 */
    ECList next;   /* 线性表中下一个元素的位置 */
};
typedef struct CircPtrNode *Circuit; /* 欧拉回路 */
struct CircPtrNode {
	ECList first;  /* 回路首结点指针 */
	ECList last;   /* 回路尾结点指针 */
};

void InitGraph(LGraph graph, int kMaxVertex, bool directed)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void InsertEdge(LGraph graph, Vertex u, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int *dfn, *low, count;
Vertex *parents;
bool *visited, *points;

int Min(int x, int y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法7-22：利用深度优先遍历计算dfn和low的值 DfnAndLow(graph,v,parent) */
void DfnAndLow(LGraph graph, Vertex v, Vertex parent)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-22 结束 */

/* 算法7-23：求割点的Tarjan算法 ArticulationPoint (graph, start) */
void ArticulationPoint(LGraph graph, Vertex start)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-23 结束 */

/* 算法7-24：求割边的Tarjan算法 ArticulationEdge(graph, start) */
void ArticulationEdge(LGraph graph, Vertex start)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-24 结束 */

LGraph BuildGraph()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

int main(void)
{
	LGraph graph;
	Vertex v;
	
	graph = BuildGraph();
	dfn = (int *)malloc(sizeof(int) * graph->n_verts);
	low = (int *)malloc(sizeof(int) * graph->n_verts);
	parents = (Vertex *)malloc(sizeof(Vertex) * graph->n_verts);
	visited = (bool *)malloc(sizeof(bool) * graph->n_verts);
	count = 0;
	points = (bool *)malloc(sizeof(bool) * graph->n_verts);
	ArticulationPoint (graph, 0);
	for (v=0; v<graph->n_verts; v++) {
		if (points[v]==true) {
			printf("%c", graph->ver_list[v]->data);
		}
	}
	printf("\n");
	ArticulationEdge(graph, 0);
	
	return 0;
}

