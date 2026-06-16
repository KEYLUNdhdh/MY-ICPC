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
#define kMaxS 4 /* 解分量的值域规模|S|的上限 */

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


bool Check( int s[], Matrix T, int i )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Print( int *s, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法15-5：回溯法的通用伪代码 Backtracking (i, n) */
bool Backtracking( Matrix T, int *s, int i, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}
 
/* 算法15-5 结束 */ 

int main(void)
{
	Matrix T;
	int *s;  /* 解的状态分量 */
	int n_people, n_book, i, j;
	
	scanf("%d %d", &n_people, &n_book);
	T = (Matrix)malloc(sizeof(struct MatrixNode));
	T->row = n_people;
	T->col = n_book;
	T->t = Create2DArray(T->row, T->col);
	for (i=0; i<n_people; i++) {
		for (j=0; j<n_book; j++) {
			scanf("%d", &T->t[i][j]);
		}
	}
	s = (int *)malloc(sizeof(int) * T->row);
	Backtracking (T, s, 1, T->row);
	Free2DArray(T->t);
	free(T);
	
	return 0;
}

