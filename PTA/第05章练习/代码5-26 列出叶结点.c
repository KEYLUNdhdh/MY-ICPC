#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 10
typedef int NodePosition; /* 数组下标即结点位置 */
typedef struct BinaryTreeNode *BinaryTree;
struct BinaryTreeNode {
    NodePosition left;    /* 左孩子指针 */
    NodePosition right;   /* 右孩子指针 */
};

/* 链式队列定义 */
typedef enum {false, true} bool;
#define NIL -1
typedef NodePosition QElemSet;

typedef struct QueueNode *Position; /* 指针即结点位置 */
struct QueueNode {
    QElemSet data;   /* 存储数据 */
    Position next;   /* 链接队列中下一个元素的位置 */
};
typedef struct QueueHeadNode *Queue;
struct QueueHeadNode {
    int size;        /* 链接队列中当前元素个数 */
    Position front;  /* 链接队列的队首指针，初始化为NULL */
    Position rear;   /* 链接队列的队尾指针，初始化为NULL */
};

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

/* 队列定义结束*/ 

bool Visit(BinaryTree tree, NodePosition idx, bool first)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void LevelOrder(BinaryTree tree, NodePosition root)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


NodePosition BuildTree(BinaryTree tree, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	int n;
	BinaryTree tree;
	NodePosition root;
	
	scanf("%d\n", &n);
	tree = (BinaryTree)malloc(sizeof(struct BinaryTreeNode) * n);
	root = BuildTree(tree, n);
	LevelOrder(tree, root);
		 
	return 0;
}

