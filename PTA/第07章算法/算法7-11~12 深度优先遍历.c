#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef int Vertex;    /* 顶点编号类型 */
typedef int GElemSet;  /* 边权重类型 */
typedef char VertInfo; /* 顶点信息类型 */

typedef struct EdgeNode *Position; /* 指针即结点位置 */
struct EdgeNode {
    Vertex dest;     /* 边的另一端点编号 */
    GElemSet weight; /* 权重 */
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
#define NIL -1 /* 顶点不存在时的返回值 */

void InitGraph(LGraph graph, int kMaxVertex, bool directed)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool ExistEdge(LGraph graph, Vertex u, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void InsertEdge(LGraph graph, Vertex u, Vertex v, GElemSet weight)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void Visit(LGraph graph, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法7-12: 从指定顶点开始深度优先遍历 DFSv(graph,v,visited) */
void DFSv(LGraph graph, Vertex v, bool visited[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-12 结束 */

/* 算法7-11: 按深度优先遍历图中结点 DFS(graph) */
void DFS(LGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-11 结束 */

LGraph BuildGraph()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

int main(void)
{
	LGraph graph;
	
	graph = BuildGraph();
	DFS(graph);
	
	return 0;
}

