#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef enum { false, true } bool;

typedef int Vertex;    /* 顶点编号类型 */
typedef int GElemSet;  /* 边权重类型 */
typedef char VertInfo[4]; /* 顶点信息类型 */

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
#define kMaxV 100

void InitGraph(LGraph graph, int kMaxVertex, bool directed);
bool ExistEdge(LGraph graph, Vertex u, Vertex v);
void InsertEdge(LGraph graph, Vertex u, Vertex v);
LGraph BuildGraph();

/* 链式队列定义 */
typedef Vertex QElemSet;
typedef struct QueueNode *QPosition; /* 指针即结点位置 */
struct QueueNode {
    QElemSet data;    /* 存储数据 */
    QPosition next;   /* 链接队列中下一个元素的位置 */
};
typedef struct QueueHeadNode *Queue;
struct QueueHeadNode {
    int size;        /* 链接队列中当前元素个数 */
    QPosition front;  /* 链接队列的队首指针，初始化为NULL */
    QPosition rear;   /* 链接队列的队尾指针，初始化为NULL */
};
void InitQueue(Queue queue);
bool IsEmpty(Queue queue);
void EnQueue(Queue queue, QElemSet x);
QElemSet GetFront(Queue queue);
void DeQueue(Queue queue);
void DestroyQueue(Queue queue);
/* 链式队列定义结束 */

void GetInDegree(LGraph graph, Vertex in_degree[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法8-5：拓扑排序 TopSort(graph, top_s) */
bool TopSort(LGraph graph, Vertex top_s[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法8-5 结束 */

int main(void)
{
	LGraph graph;
	int i;
	Vertex *top_s; 
	
	graph = BuildGraph();
	top_s = (Vertex *)malloc(sizeof(Vertex) * graph->n_verts);
	memset(top_s, 0, sizeof(Vertex) * graph->n_verts);
	printf("该图拓扑序存在性为 %d\n", TopSort(graph, top_s));
	for (i=0; i<graph->n_verts; i++) {
		printf("%s ", graph->ver_list[top_s[i]]->data);
	}
	
	return 0;
}

/* 建图的相关操作 */
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


void InsertEdge(LGraph graph, Vertex u, Vertex v)
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

/* 建图的相关操作结束 */

/* 链式队列相关操作 */
void InitQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsEmpty(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void EnQueue(Queue queue, QElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


QElemSet GetFront(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void DeQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void DestroyQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 链式队列相关操作结束 */

