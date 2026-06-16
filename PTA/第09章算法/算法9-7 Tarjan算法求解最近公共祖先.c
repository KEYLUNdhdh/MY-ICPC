#include <stdio.h>
#include <stdlib.h>

#define NIL -1 /* 假设数据为非负整数，NIL定义为非法数据，表示空 */
#define kMaxSize 1000 /* 树结点最大个数 */
#define kMaxStringSize 4 /* 键值最大位数 */
typedef enum {false, true} bool;

/* 树的定义与操作 */ 
typedef int TElemSet;
typedef struct BinaryTreeNode *BinaryTree;
typedef struct BinaryTreeNode *Position;
struct BinaryTreeNode {
    TElemSet data;       /* 数据元素 */
    BinaryTree left;    /* 左孩子指针 */
    BinaryTree right;   /* 右孩子指针 */
};

int k; /* 当前待处理的元素在preorder中的下标，初始化为-1 */
BinaryTree PreOrderDeSerialize(TElemSet preorder[], int n);
BinaryTree BuildTree();
/* 树的定义与操作结束 */ 

/* 不相交集的定义与操作 */
typedef int SElemSet;             /* 默认元素用非负整数表示 */
typedef SElemSet SetName;         /* 默认用根结点的下标作为集合名称 */
typedef struct SetNode {
	SElemSet parent;  /* 父结点 */
	int rank;         /* 秩 */ 
} Set[kMaxSize+1];    /* 假设集合元素下标从1开始 */

void InitSet(Set set, int n);
SetName Find(Set set, SElemSet x);
void Union(Set set, SElemSet x, SElemSet y);
/* 不相交集的定义与操作结束 */

/* 查询结点对的存储结构 */
typedef int Node; /* 结点为从1开始的正整数 */
typedef struct PairNode *Pair;
struct PairNode {
	Node u, v;  /* 待查询的一对结点(u,v) */
	Node lca;   /* 记录LCA(u,v) */
};
typedef struct QueryNode *Query;
struct QueryNode {
	Pair nodes; /* 待查询的结点对数组 */
	int size;   /* 查询数量，即数组长度 */
};

/* 算法9-7：Tarjan算法求解最近公共祖先 LCA(P, u, set, ancestor, visited) */
void LCA(Query P, Position u, Set set, Node ancestor[], bool visited[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法9-7 结束 */ 

void LeastCommonAncestor(BinaryTree tree, Query P)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	BinaryTree tree;
	Query P;
	int m, i;
	
	tree = BuildTree(); /* 创建二叉树 */ 
	scanf("%d", &m);
	/* 创建查询集 */
	P = (Query)malloc(sizeof(struct QueryNode));
	P->size = m;
	P->nodes = (Pair)malloc(sizeof(struct PairNode) * m);
	for (i=0; i<m; i++) { /* 读入待查询的结点对，并初始化其LCA为空 */
		scanf("%d %d", &P->nodes[i].u, &P->nodes[i].v);
		P->nodes[i].lca = NIL;
	}
	LeastCommonAncestor(tree, P); /* 求查询集P中所有结点对的LCA */
	for (i=0; i<m; i++) {
		printf("LCA(%d, %d) = %d\n", P->nodes[i].u, P->nodes[i].v, P->nodes[i].lca);
	}
	return 0;
}

/* 创建树的操作 */
BinaryTree PreOrderDeSerialize(TElemSet preorder[], int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


BinaryTree BuildTree()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 创建树的操作 结束 */

/* 不相交集的操作 */
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


void Union(Set set, SElemSet x, SElemSet y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 不相交集的操作 结束 */

