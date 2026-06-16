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
#define NIL -1 /* 生成树不存在时的返回值 */
#define kMaxV 1000 /* 最大顶点数量 */
void InitGraph(LGraph graph, int kMaxVertex, bool directed);
bool ExistEdge(LGraph graph, Vertex u, Vertex v);
void InsertEdge(LGraph graph, Vertex u, Vertex v, GElemSet weight);
LGraph BuildGraph();

typedef struct Edge *EdgeSet;
struct Edge {
	Vertex u, v; /* 边的两个端点 */
	GElemSet weight; /* 权重 */
};
typedef Vertex *VertexSet;

int Cmp_Weight(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


EdgeSet InitEdgeSet (LGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


VertexSet InitVertexSet (LGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


Vertex Find (VertexSet v, Vertex u)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


bool IsCycle (VertexSet v, Vertex v1, Vertex v2)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


GElemSet Kruskal(LGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	printf("%d\n", Kruskal(BuildGraph()));
	return 0;
}

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


LGraph BuildGraph()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

