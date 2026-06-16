#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef enum { false, true } bool;
#define kInfinity (1e9)
typedef int ElemSet; /* 默认矩阵元素为整型 */
typedef struct MatrixNode *Matrix;
struct MatrixNode {
	ElemSet **m;
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


void PrintOrder(Matrix p, int i, int j)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法15-10 计算m_(1,n)的动态规划算法 OptimalMatrixOrdering (m, p, r, n) */
void OptimalMatrixOrdering (Matrix m, Matrix p, int *r, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法15-10 结束 */ 

int main(void)
{
	Matrix m, p;
	int *r;
	int n, i;
	
	scanf("%d", &n);
	m = (Matrix)malloc(sizeof(struct MatrixNode));
	m->row = n;
	m->col = n;
	m->m = Create2DArray(m->row, m->col);
	p = (Matrix)malloc(sizeof(struct MatrixNode));
	p->row = n;
	p->col = n;
	p->m = Create2DArray(p->row, p->col);
	r = (int *)malloc(sizeof(int) * (n+1));
	for (i=0; i<=n; i++) {
		scanf("%d", &r[i]);
	}
	OptimalMatrixOrdering (m, p, r, n);
	PrintOrder(p, 0, n-1);
	printf("\n%d\n", m->m[0][n-1]);
	Free2DArray(m->m);
	free(m);
	Free2DArray(p->m);
	free(p);
	
	return 0;
}

