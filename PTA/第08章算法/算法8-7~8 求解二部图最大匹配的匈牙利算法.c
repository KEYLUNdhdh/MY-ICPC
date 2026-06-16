#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef int Vertex;    /* 顶点编号类型 */
typedef struct BiGraphNode *BiGraph; /* 邻接矩阵表示的图 */
struct BiGraphNode {
    int n_u_verts; /* U点集顶点数 */
    int n_v_verts; /* V点集顶点数 */
    int m_edges; /* 边数 */
    bool **edge_matrix;/* 邻接矩阵 */
};
#define NIL -1 /* 顶点不存在时的返回值 */

void InitGraph(BiGraph bigraph, int u_size, int v_size); 
void InsertEdge(BiGraph graph, Vertex u, Vertex v);
BiGraph BuildGraph();

/* 算法8-8：找二部图匹配的增广路径 FindAugmentingPath(bigraph, match, u, visited) */
bool FindAugmentingPath(BiGraph bigraph, Vertex match[], Vertex u, bool visited[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法8-8 结束 */

/* 算法8-7：求解二部图最大匹配的匈牙利算法 MaximumMatch(bigraph, match) */
int MaximumMatch(BiGraph bigraph, Vertex match[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法8-7 结束 */

int main(void)
{
	BiGraph bigraph;
	Vertex *match;
	
	bigraph = BuildGraph();
	match = (Vertex *)malloc(sizeof(Vertex) * bigraph->n_u_verts);
	printf("最大匹配值 = %d\n", MaximumMatch(bigraph, match));
	
	return 0;
}

void InitGraph(BiGraph bigraph, int u_size, int v_size)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void InsertEdge(BiGraph graph, Vertex u, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


BiGraph BuildGraph()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


