#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 10
#define NIL -1 /* 假设数据为非负整数，NIL定义为非法数据，表示空 */
typedef int TElemSet;

typedef struct BinaryTreeNode *BinaryTree;
struct BinaryTreeNode {
    TElemSet data;      /* 数据元素 */
    BinaryTree left;    /* 左孩子指针 */
    BinaryTree right;   /* 右孩子指针 */
};

void Visit(BinaryTree tree)
{
	printf("%d\n", tree->data);
}


void PreOrder(BinaryTree tree)
{
    if(tree == NULL)
		return;

	Visit(tree);
	PreOrder(tree->left);
	PreOrder(tree->right);
}


/* 算法5-12：根据前序序列重构二叉树 PreOrderDeSerialize(preorder, n) */ 
int k; /* 当前待处理的元素在preorder中的下标，初始化为-1 */
BinaryTree PreOrderDeSerialize(TElemSet preorder[], int n)
{
	k++;

	if(k >= n || preorder[k] == -1)
	{
		return NULL;
	}

	BinaryTree node = (BinaryTree)malloc(sizeof(struct BinaryTreeNode));
	node->data = preorder[k];
	node->left = PreOrderDeSerialize(preorder, n);
	node->right = PreOrderDeSerialize(preorder, n);
	
	return node;
}

/* 算法5-12 结束 */ 
 
int main(void)
{
	BinaryTree tree;
	TElemSet *preorder;
	char s[kMaxSize];
	int n, i;
	
	scanf("%d\n", &n);
	preorder = (TElemSet *)malloc(sizeof(TElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%s ", s);
		if (s[0] == '#') {
			preorder[i] = NIL;
		}
		else {
			preorder[i] = atoi(s);
		}
	}
	k = -1;
	tree = PreOrderDeSerialize(preorder, n);
	PreOrder(tree);
	 
	return 0;
}

