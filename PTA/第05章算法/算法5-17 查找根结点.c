#include <stdio.h>
#include <stdlib.h>

typedef char TElemSet;
typedef int Position;
typedef struct TreeNode *Tree;
struct TreeNode {
    TElemSet data;    /* 数据元素 */
	Position parent;  /* 父结点位置 */
};


/* 算法5-17：查找根结点 FindRoot(tree, x) */
Position FindRoot(Tree tree, Position x)
{
	while(tree[x].parent != -1)
	{
		x = tree[x].parent;
	}
	return x;
}

/* 算法5-17 结束 */ 

int main(void)
{
	int n, i;
	Tree tree;
	Position x;
	
	scanf("%d\n", &n);
	tree = (Tree)malloc(sizeof(struct TreeNode) * n);
	for (i=0; i<n; i++) {
		scanf("%c %d\n", &tree[i].data, &tree[i].parent);
	}
	scanf("%d", &x);
	printf("root index = %d\n", FindRoot(tree, x));
	
	return 0;
}

