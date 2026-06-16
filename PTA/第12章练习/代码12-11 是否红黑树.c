#include <stdio.h>
#include <stdlib.h>

#define kMaxN 30
typedef enum { false, true } bool;
typedef int TElemSet;  /* 默认元素为整型 */
typedef enum { Red, Black } Color;
typedef struct RBTreeNode *Position; /* 树结点指针是元素的位置 */
typedef struct RBTreeNode *RBTree;
struct RBTreeNode {
    TElemSet data;    /* 数据元素 */
    RBTree left;      /* 左孩子指针 */
    RBTree right;     /* 右孩子指针 */
    Color color;      /* 颜色 */
    int black_height; /* 结点黑高 */
};

int CmpNum(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


RBTree BuildTree(TElemSet *preorder, TElemSet *inorder, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


bool Check( RBTree tree )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void DestroyTree( RBTree tree )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	int k, n, i;
	TElemSet preorder[kMaxN], inorder[kMaxN];
	RBTree tree;
	
	scanf("%d", &k);
	while (k--) {
		scanf("%d", &n);
		for (i=0; i<n; i++) {
			scanf("%d", &preorder[i]);
		}
        if (preorder[0]<0) printf("No\n"); /* 根结点是红色 */
        else {
            for (i=0; i<n; i++) {
            	inorder[i] = (preorder[i]>0)? preorder[i]:(-preorder[i]);
			}
            qsort(inorder, n, sizeof(int), CmpNum);
            tree = BuildTree(preorder, inorder, n);
            if (Check(tree)==true) {
                printf("Yes\n");
			}
            else {
                printf("No\n");
			}
			DestroyTree(tree);
        }
	}
    return 0;
}

