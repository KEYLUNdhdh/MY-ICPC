#include <stdio.h>
#include <stdlib.h>

#define infinity 10000  /* 表示没有关系的常数 */
#define kMaxM 100000    /* 关系条数最大值 */
typedef enum { false, true } bool;

/* 集合相关定义与操作 */
#define kMaxSize 100000   /* 集合最大元素个数 */
typedef int SElemSet;     /* 默认元素用非负整数表示 */
typedef SElemSet SetName; /* 默认用根结点的下标作为集合名称 */
typedef struct SetNode {
	SElemSet parent;  /* 父结点 */
	int size;         /* 群规模 */
	int rank;         /* 秩，用于最小生成树 */ 
	SetName name;     /* 集合名称，即朋友群的编号 */
	int strength;     /* 凝聚力 */
	bool root;        /* 是否原始集合的根结点 */
} Set[kMaxSize+1];    /* 假设集合元素下标从1开始 */

void InitSet(Set set, int n); /* 初始化集合 */
SetName Find(Set set, SElemSet x); /* 找到x所在集合的根结点 */
void UnionPersons(Set set, SElemSet x, SElemSet y, int strength); /* 合并两个人进同一个群 */
/* 集合相关定义与操作 结束 */

/* 边集相关定义与操作 */
typedef int Vertex; /* 顶点 */
typedef struct EdgeNode { /* 边 */
	Vertex u, v;  /* 边(u,v)的两个端点 */
	int weight;  /* 权重 */ 
} Edge[kMaxM];

int CmpWeight(const void *a, const void *b); /* qsort比较函数 */
/* 边集相关定义与操作 结束*/

/* 最小生成树相关函数 */
bool IsCycle (Set v, Vertex v1, Vertex v2); /* 判断边(v1, v2)的加入是否构成回路 */
int Kruskal(Set v, Edge e, int n_verts, int m_edges); /* Kruskal 求最小生成树算法 */
/* 最小生成树相关函数 结束*/

int ReadRelations(Set v, Edge e, int m); /* 读取输入，建群和边集 */
int GetGroups(Set v, int n); /* 统计有多少个群，并修正单人群的凝聚力 */
int CmpSet(const void *a, const void *b); /* qsort比较函数 */
void OutputGroups(Set v, int n); /* 输出群信息 */

int main(void)
{
	int n, m, n_verts, m_edges, mst_weight;
	Set v;  /* 顶点集合 */
	Edge e; /* 边集合 */

	scanf("%d %d", &n, &m);
	InitSet(v, n); /* 顶点集合初始化 */
	m_edges = ReadRelations(v, e, m); /* 根据输入建群，并获得边 */
	n_verts = GetGroups(v, n); /* 将一个群缩成一个顶点 */
	mst_weight = Kruskal(v, e, n_verts, m_edges); /* 求最小生成树 */
	OutputGroups(v, n); /* 输出群信息 */
	printf("%d\n", mst_weight); /* 输出最小生成树权重 */
	
	return 0;
}

void InitSet(Set set, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 

SetName Find(Set set, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void UnionPersons(Set set, SElemSet x, SElemSet y, int strength)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int CmpWeight(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsCycle (Set set, Vertex v1, Vertex v2)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int Kruskal(Set v, Edge e, int n_verts, int m_edges)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int ReadRelations(Set v, Edge e, int m)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int GetGroups(Set v, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int CmpSet(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void OutputGroups(Set v, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


