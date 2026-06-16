#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 物品价值为整数 */
typedef struct ObjNode *Objects;
struct ObjNode {
	int w;     /* 重量 */
	ElemSet v; /* 价值 */
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


/* 算法15-14：整数重量限制下离散背包问题的动态规划解法 Knapsack01( W, s, opt, n ) */
ElemSet Knapsack01( int W, Objects s, int *opt, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法15-14 结束 */

int main(void)
{
	Objects s;
	int W;
	int *opt;
	int n, i;
	
	scanf("%d %d", &n, &W);
	s = (Objects)malloc(sizeof(struct ObjNode) * n);
	opt = (int *)malloc(sizeof(int) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &s[i].w);
	}
	for (i=0; i<n; i++) {
		scanf("%d", &s[i].v);
	}
	printf("%d\n", Knapsack01( W, s, opt, n ));
	for (i=0; i<n; i++) {
		printf("%d ", opt[i]);
	}
	return 0;
}

