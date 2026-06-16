#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef enum { false, true } bool;
typedef int ElemSet; /* 默认矩阵元素为整型 */
typedef struct MatrixNode *Matrix;
struct MatrixNode {
	ElemSet **t;
	int row;
	int col;
};

ElemSet **Create2DArray(int row, int col)
{	/* 动态声明row行col列的二维数组 */
	ElemSet *a, **t;
	int i;

	a = (ElemSet *)malloc(sizeof(ElemSet) * row * col);
	t = (ElemSet **)malloc(sizeof(ElemSet *) * row);
	for (i=0; i<row; i++)
		t[i] = &a[col*i];
	return t;
}

void Free2DArray (ElemSet **t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void Print( int *s, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法15-4：分书问题的递归枚举算法 BookAssignmentBF (table, s, i, n, m) */
void BookAssignmentBF( Matrix table, int *s, int i, int n, int m )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法15-4 结束 */ 

int main(void)
{
	Matrix table;
	int *s;  /* 解的状态分量 */
	int n, m, i, j;
	
	scanf("%d %d", &n, &m);
	table = (Matrix)malloc(sizeof(struct MatrixNode));
	table->row = n;
	table->col = m;
	table->t = Create2DArray(table->row, table->col);
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			scanf("%d", &table->t[i][j]);
		}
	}
	s = (int *)malloc(sizeof(int) * n);
	BookAssignmentBF(table, s, 0, n, m);
	Free2DArray(table->t);
	free(table);
	
	return 0;
}

