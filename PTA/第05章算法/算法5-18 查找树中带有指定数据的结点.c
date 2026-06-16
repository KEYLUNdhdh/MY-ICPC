#include <stdio.h>
#include <stdlib.h>

typedef int TElemSet;
typedef struct TreeNode *Position;
typedef struct TreeNode *Tree;
struct TreeNode {
	TElemSet data;       /* 数据元素 */
	Tree first_child;    /* 第一个子结点 */
	Tree next_sibling;   /* 下一个兄弟结点 */
};

/* 算法5-18：查找树中带有指定数据的结点 Search(tree, x) */
Position Search(Tree tree, TElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法5-18 结束 */ 

Tree NewTreeNode ()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	Tree tree, child, sibling, p;
	TElemSet x;
	
	tree = NewTreeNode();
	child = NewTreeNode();
	sibling = NewTreeNode();
	tree->first_child = child;
	child->next_sibling = sibling;
	sibling->next_sibling = NewTreeNode();
	scanf("%d", &x);
	p = Search(tree, x);
	if (p != NULL) {
		printf("%d is found.\n", p->data);
	}
	else {
		printf("%d is NOT found.\n", x);
	}
		
	return 0;
}

