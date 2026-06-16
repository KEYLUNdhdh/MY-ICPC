#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef int ElemSet; /* 默认矩阵元素为整型 */
#define kMaxPeople 3
#define kMaxBook 4
typedef struct MatrixNode *Matrix;
struct MatrixNode {
	ElemSet t[kMaxPeople][kMaxBook];
	int row;
	int col;
};

bool Check( int s1, int s2, int s3, Matrix T )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法15-1：小规模分书问题的嵌套循环算法 BookAssignment(T) */
void BookAssignment( Matrix T )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法15-1 结束 */ 

int main(void)
{
	Matrix T;
	int n_people, n_book, i, j;
	
	scanf("%d %d", &n_people, &n_book);
	T = (Matrix)malloc(sizeof(struct MatrixNode));
	T->row = n_people;
	T->col = n_book;
	for (i=0; i<n_people; i++) {
		for (j=0; j<n_book; j++) {
			scanf("%d", &T->t[i][j]);
		}
	}
	BookAssignment(T);
	free(T);
	
	return 0;
}

