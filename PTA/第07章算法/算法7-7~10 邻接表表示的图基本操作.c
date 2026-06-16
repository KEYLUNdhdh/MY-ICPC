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

void InitGraph(LGraph graph, int kMaxVertex, bool directed);
Vertex FirstAdjVert (LGraph graph, Vertex v);
bool ExistEdge(LGraph graph, Vertex u, Vertex v);
void InsertEdge(LGraph graph, Vertex u, Vertex v, GElemSet weight);
void RemoveVert(LGraph graph, Vertex v);

LGraph BuildGraph()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

int main(void)
{
	LGraph graph;
	Vertex u, v;
	Position p;
	
	graph = BuildGraph();
	printf("邻接表为：\n");
	for (v=0; v<graph->n_verts; v++) {
		printf("list[%d]->", v);
		p = graph->ver_list[v]->adj;
		while (p != NULL) {
			printf("%d:%d->", p->dest, p->weight);
			p = p->next;
		}
		printf("end\n");
	}
	printf("顶点数 = %d\n", graph->n_verts);
	scanf("%d %d\n", &u, &v);
	printf("<%d, %d> 的存在性 = %d\n", u, v, ExistEdge(graph, u, v));
	scanf("%d %d\n", &u, &v);
	printf("<%d, %d> 的存在性 = %d\n", u, v, ExistEdge(graph, u, v));
	scanf("%d\n", &v);
	printf("顶点%d的第一个邻接点 = %d\n", v, FirstAdjVert (graph,v));
	scanf("%d\n", &v);
	printf("待删除的顶点信息为 %c\n", graph->ver_list[v]->data);
	RemoveVert(graph, v);
	printf("当前顶点数 = %d\n", graph->n_verts);
	printf("当前边数 = %d\n", graph->m_edges);
	for (v=0; v<graph->n_verts; v++) {
		printf("%c", graph->ver_list[v]->data);
	}
	printf("\n");
	printf("邻接表为：\n");
	for (v=0; v<graph->n_verts; v++) {
		printf("list[%d]->", v);
		p = graph->ver_list[v]->adj;
		while (p != NULL) {
			printf("%d:%d->", p->dest, p->weight);
			p = p->next;
		}
		printf("end\n");
	}
	return 0;
}

void InitGraph(LGraph graph, int kMaxVertex, bool directed)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法7-7: 返回图中顶点的第一个邻接顶点 FirstAdjVert(graph,v) */
Vertex FirstAdjVert (LGraph graph, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法7-7 结束 */ 

/* 算法7-8: 判断边是否存在  ExistEdge(graph, u, v) */
bool ExistEdge(LGraph graph, Vertex u, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法7-8 结束 */ 

/* 算法7-9: 向图中插入边 InsertEdge(graph, u,v,weight) */
void InsertEdge(LGraph graph, Vertex u, Vertex v, GElemSet weight)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-9 结束 */ 

/* 算法7-10: 从图中删除顶点及所有邻接于该顶点的边 RemoveVert(graph,v) */
void RemoveVert(LGraph graph, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-10 结束 */ 

