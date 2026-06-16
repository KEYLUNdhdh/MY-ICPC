#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef int Vertex;    /* 顶点编号类型 */
#define kMaxVertex 1000  /* 最大顶点数   */ 

typedef struct VCNode *VertexCover; /* 顶点覆盖集 */
struct VCNode {
	Vertex *ver; /* 存储顶点的数组 */ 
	int size;    /* 集合规模 */
};

typedef struct EdgeNode *Edges; /* 图中的边 */
struct EdgeNode {
	Vertex u, v;  /* 边的两个端点 */
};

typedef struct EdgeSetNode *EdgeSet; /* 边集合 */
struct EdgeSetNode {
	Edges e;  /* 存储边的数组 */
	int size; /* 集合规模 */
};

EdgeSet InitEdgeSet( int m )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


VertexCover InitSet()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Insert(VertexCover C, Vertex u, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void Delete(EdgeSet E, Vertex u, Vertex v)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法16-1：顶点覆盖问题的近似算法 VertexCoverApproximation(E) */
VertexCover VertexCoverApproximation(EdgeSet E)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法16-1 结束 */ 

int main(void)
{
	EdgeSet E;
	VertexCover C;
	Vertex u, v;
	int m, i;
	
	scanf("%d", &m);
	E = InitEdgeSet(m);
	for (i=0; i<m; i++) {
		scanf("%d %d", &u, &v);
		E->e[E->size].u = u;
		E->e[E->size].v = v;
		E->size++;
	}
	C = VertexCoverApproximation(E);
	for (i=0; i<C->size; i++) {
		printf("%d ", C->ver[i]);
	}
	
	return 0;
}

