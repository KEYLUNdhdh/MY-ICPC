#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum { false, true } bool;
typedef int Vertex;    /* 顶点编号类型 */
#define kMaxVertex 10  /* 最大顶点数   */ 
typedef struct VertSetNode *VertexSet;
struct VertSetNode {
	bool *in;    /* 顶点状态数组，true表示该顶点在解集里 */
	int n_verts; /* 顶点总个数 */
	int in_v;    /* 当前解集中的顶点数 */
	int in_e;    /* 当前解集覆盖的边数 */
	int E;       /* 当前解的E值 */
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


double Random (double a, double b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int E(Vertex v, VertexSet s, EdgeSet Edge)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Accept(VertexSet current_solution, Vertex next_solution, int dE)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法16-6：模拟退火算法 SimulatedAnnealing(init_solution, E, T, alpha, k, iter_num, eps) */
void SimulatedAnnealing(VertexSet init_solution, 
						int (*E)(Vertex v, VertexSet s, EdgeSet Edge),
						double T, double alpha, double k, int iter_num, double eps,
						EdgeSet Edge)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法16-6 结束 */ 

int main(void)
{
	VertexSet solution;
	EdgeSet Edge;
	Vertex u, v;
	double T, alpha, k, eps;
	int n, m, iter_num, i;
		
	scanf("%d %d", &n, &m);
	Edge = InitEdgeSet(m);
	for (i=0; i<m; i++) {
		scanf("%d %d", &u, &v);
		Edge->e[Edge->size].u = u;
		Edge->e[Edge->size].v = v;
		Edge->size++;
	}
	solution = InitSet(n);
	scanf("%lf %lf %lf %d %lf", &T, &alpha, &k, &iter_num, &eps);
	SimulatedAnnealing(solution, E, T, alpha, k, iter_num, eps, Edge);
	for (v=0; v<n; v++) {
		if (solution->in[v]==true) {
			printf("%d ", v);
		}
	}

	return 0;
}

