#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef int Vertex;    /* 顶点编号类型 */
#define kMaxVertex 10  /* 最大顶点数   */ 
#define infinity (1e9)
typedef struct VertSetNode *VertexSet;
struct VertSetNode {
	bool *in;    /* 顶点状态数组，true表示该顶点在解集里 */
	int n_verts; /* 顶点总个数 */
	int in_v;    /* 当前解集中的顶点数 */
	int in_e;    /* 当前解集覆盖的边数 */
	int f;       /* 当前解的f值 */
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


VertexSet InitSet( int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int f(Vertex v, VertexSet s, EdgeSet E)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法16-5：爬山算法 HillClimbing(f, init_solution, E) */
void HillClimbing(int (*f)(Vertex v, VertexSet s, EdgeSet E), VertexSet init_solution, EdgeSet E)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法16-5 结束 */ 

int main(void)
{
	VertexSet solution;
	EdgeSet E;
	Vertex u, v;
	int n, m, i;
		
	scanf("%d %d", &n, &m);
	E = InitEdgeSet(m);
	for (i=0; i<m; i++) {
		scanf("%d %d", &u, &v);
		E->e[E->size].u = u;
		E->e[E->size].v = v;
		E->size++;
	}
	solution = InitSet(n);
	HillClimbing(f, solution, E);
	for (v=0; v<n; v++) {
		if (solution->in[v]==true) {
			printf("%d ", v);
		}
	}

	return 0;
}

