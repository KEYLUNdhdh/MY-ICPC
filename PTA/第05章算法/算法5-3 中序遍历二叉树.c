#include <stdio.h>
#include <stdlib.h>

typedef int TElemSet;

typedef struct BinaryTreeNode *BinaryTree;
struct BinaryTreeNode {
    TElemSet data;      /* 数据元素 */
    BinaryTree left;    /* 左孩子指针 */
    BinaryTree right;   /* 右孩子指针 */
};

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


/* 算法5-3：中序遍历二叉树 InOrder(tree) */ 
void InOrder(BinaryTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法5-3 结束 */ 

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

