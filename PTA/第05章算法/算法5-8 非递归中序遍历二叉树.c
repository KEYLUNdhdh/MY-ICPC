#include <stdio.h>
#include <stdlib.h>

typedef int TElemSet;

typedef struct BinaryTreeNode *BinaryTree;
struct BinaryTreeNode {
    TElemSet data;      /* 数据元素 */
    BinaryTree left;    /* 左孩子指针 */
    BinaryTree right;   /* 右孩子指针 */
};

/* 链式堆栈定义 */
typedef enum {false, true} bool;
#define NIL NULL
typedef BinaryTree SElemSet;

typedef struct StackNode *Position; /* 指针即结点位置 */
struct StackNode {
    SElemSet data;  /* 存储数据 */
    Position next;  /* 链接栈中下一个元素的位置 */
};
typedef struct StackHeadNode *Stack;
struct StackHeadNode {
    int size;       /* 链接栈中当前元素个数 */
    Position top;   /* 链接栈的栈顶指针，初始化为NULL */
};

void InitStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsEmpty(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Push (Stack stack, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


SElemSet Top (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Pop (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void DestroyStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 堆栈定义结束*/ 

BinaryTree CreateBinaryTree(TElemSet value, BinaryTree left_tree, BinaryTree right_tree )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Visit(BinaryTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法5-8：非递归中序遍历二叉树 InOrder(tree) */ 
void InOrder(BinaryTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法5-8 结束 */ 

int main(void)
{
	BinaryTree tree, left_tree, right_tree;
	TElemSet value;
	
	scanf("%d", &value);
	left_tree = CreateBinaryTree(value, NULL, NULL);
	scanf("%d", &value);
	right_tree = CreateBinaryTree(value, NULL, NULL);
	scanf("%d", &value);
	tree = CreateBinaryTree(value, left_tree, right_tree);
	InOrder(tree);
	 
	return 0;
}

