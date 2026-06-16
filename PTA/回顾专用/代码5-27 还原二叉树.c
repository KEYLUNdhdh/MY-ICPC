#include <stdio.h>
#include <stdlib.h>

typedef char TElemSet;
typedef struct BinaryTreeNode *BinaryTree;
struct BinaryTreeNode {
    TElemSet data;      /* 数据元素 */
    BinaryTree left;    /* 左孩子指针 */
    BinaryTree right;   /* 右孩子指针 */
};

BinaryTree BuildTree(TElemSet *preorder, TElemSet *inorder, int n)
{

	// 这个一定要加上，要不然爆栈
	if(n == 0)
		return NULL;
	int len = n;
	char root = preorder[0];
	BinaryTree node = (BinaryTree)malloc(sizeof(struct BinaryTreeNode));
	node->data = root;
	if(len == 1)
	{
		node->left = NULL;
		node->right = NULL;
		return node;
	}

	int posroot = -1;
	for (int i = 0; i < len;i++)
	{
		if(inorder[i] == root)
		{
			posroot = i;
			break;
		}
	}

	int llen = posroot;
	int rlen = len - llen - 1;

	char lpre[llen + 1], rpre[rlen + 1], lin[llen + 1], rin[rlen + 1];
	lpre[llen] = '\0';
	lin[llen] = '\0';
	rpre[rlen] = '\0';
	rin[rlen] = '\0';

	for (int i = 0; i < llen;i++)
		lpre[i] = preorder[i + 1];

	for (int i = 0; i < llen;i++)
		lin[i] = inorder[i];

	for (int i = 0; i < rlen;i++)
		rpre[i] = preorder[i + llen + 1];
	for (int i = 0; i < rlen;i++)
		rin[i] = inorder[i + posroot + 1];

	node->left = BuildTree(lpre, lin, llen);
	node->right = BuildTree(rpre, rin, rlen);
	return node;
}


int Height(BinaryTree tree)
{
    if(!tree)
		return 0;

	int lh = Height(tree->left);
	int rh = Height(tree->right);

	return 1 + (lh > rh ? lh : rh);
}


int main(void)
{
	int n;
	TElemSet *preorder, *inorder;
	BinaryTree tree;
	
	scanf("%d\n", &n);
	preorder = (TElemSet *)malloc(sizeof(TElemSet) * (n+1));
	scanf("%s\n", preorder);	 
	inorder = (TElemSet *)malloc(sizeof(TElemSet) * (n+1));
	scanf("%s\n", inorder);
	tree = BuildTree(preorder, inorder, n);
	printf("%d\n", Height(tree));

	return 0;
}

