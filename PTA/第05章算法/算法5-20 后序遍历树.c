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

void Visit(Tree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法5-20：后序遍历树 PostOrder(tree) */
void PostOrder(Tree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法5-20 结束 */ 

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
	PostOrder(tree);
		
	return 0;
}

