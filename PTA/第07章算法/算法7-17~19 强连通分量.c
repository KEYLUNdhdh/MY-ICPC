#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef int Vertex;    /* 顶点编号类型 */

typedef struct EdgeNode *Position; /* 指针即结点位置 */
struct EdgeNode {
    Vertex dest;     /* 边的另一端点编号 */
    Position next;   /* 线性表中下一个元素的位置 */
};
typedef struct HeadNode *AdjList; /* 邻接表 */
struct HeadNode {
    Position adj;  /* 邻接表头指针 */
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
bool ExistEdge(LGraph graph, Vertex u, Vertex v);
void InsertEdge(LGraph graph, Vertex u, Vertex v);
LGraph BuildGraph();
LGraph ReverseGraph(LGraph graph);
int PostOrderDFS(LGraph graph, Vertex v, bool visited[], Vertex dfs_seq[], int dfs_num);
void PrintV(LGraph graph, Vertex v, bool visited[]);
int StronglyConnectedComponents(LGraph graph);

int main(void)
{
	LGraph graph;
	
	graph = BuildGraph();
	printf("%d\n", StronglyConnectedComponents(graph));
	
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
 

LGraph ReverseGraph(LGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

/* 算法7-18：后序DFS遍历记录顶点 PostOrderDFS(graph, v, visited, dfs_seq, dfs_num) */
int PostOrderDFS(LGraph graph, Vertex v, bool visited[], Vertex dfs_seq[], int dfs_num)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法7-18 结束 */

/* 算法7-19：后序DFS遍历输出顶点 PrintV(graph, v, visited) */
void PrintV(LGraph graph, Vertex v, bool visited[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法7-19 结束 */

/* 算法7-17：获取图的强连通分量 StronglyConnectedComponents (graph) */
int StronglyConnectedComponents(LGraph graph)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法7-17 结束 */

