#include <stdio.h>
#include <stdlib.h>

typedef int OpType;
typedef union ExprData{
    OpType operand;   /* 运算数 */
    char operator;    /* 运算符 */
} TElemSet;

typedef struct ExprTreeNode *ExprTree;
struct ExprTreeNode {
    TElemSet data;   /* 数据元素 */
    ExprTree left;   /* 左孩子指针 */
    ExprTree right;  /* 右孩子指针 */
};

ExprTree CreateBinaryTree(TElemSet value, ExprTree left_tree, ExprTree right_tree )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void PrintData(ExprTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

 
/* 算法5-6：将表达式树转换成中缀表达式 PrintInfixExpression(tree) */ 
void PrintInfixExpression(ExprTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法5-6 结束 */ 

int main(void)
{
	ExprTree tree, left_tree, right_tree;
	TElemSet value;
	
	scanf("%d ", &value);
	left_tree = CreateBinaryTree(value, NULL, NULL);
	scanf("%d ", &value);
	right_tree = CreateBinaryTree(value, NULL, NULL);
	scanf("%c", &value);
	tree = CreateBinaryTree(value, left_tree, right_tree);
	PrintInfixExpression(tree);
	 
	return 0;
}

