#include <stdio.h>
#include <stdlib.h>

typedef int TElemSet;   /* 树中数据元素类型为整型 */
typedef struct AVLTreeNode *Position; /* 树结点指针是元素的位置 */
typedef struct AVLTreeNode *AVLTree;
struct AVLTreeNode {
    TElemSet data;   /* 数据元素 */
    int height;      /* 结点高度 */
    AVLTree left;    /* 左孩子指针 */
    AVLTree right;   /* 右孩子指针 */
};
#define NIL NULL

int GetHeight(AVLTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int Max( int x, int y )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法11-8：AVL树的左单旋转（RR型） RRSingleRotation(root) */
AVLTree RRSingleRotation(AVLTree root)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法11-8 结束 */ 

AVLTree LLSingleRotation(AVLTree root)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法11-9：AVL树的先左后右双向旋转 (LR型） LRDoubleRotation(root) */
AVLTree LRDoubleRotation(AVLTree root)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法11-9 结束 */ 

AVLTree RLDoubleRotation(AVLTree root)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法11-7 AVL树的插入 InsertAVL(tree, x) */
AVLTree InsertAVL(AVLTree tree, TElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法11-7 结束 */ 

int main(void)
{
	TElemSet x;
	AVLTree tree;
	int n, i;
	
	tree = NIL;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		scanf("%d", &x);
		tree = InsertAVL(tree, x);
	}
	printf("%d\n", tree->data);

	return 0;
}

