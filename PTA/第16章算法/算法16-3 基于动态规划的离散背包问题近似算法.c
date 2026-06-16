#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 物品重量为整数 */
#define infinity (1e9)
typedef struct ObjNode *Objects;
struct ObjNode {
	ElemSet w; /* 重量 */
	int v;     /* 价值 */
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


ElemSet Knapsack01( int W, Objects s, int *opt, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int FindMaxValue(Objects s, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法16-3：基于动态规划的离散背包问题近似算法 KnapsackDPApproximation(W,s,x,n,eps) */
ElemSet KnapsackDPApproximation(ElemSet W, Objects s, int *x, int n, double eps)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法16-3 结束 */

int main(void)
{
	Objects s;
	int W;
	int *opt;
	double eps;
	int n, i;
	
	scanf("%d %d %lf", &n, &W, &eps);
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
	printf("\n%d\n", KnapsackDPApproximation(W,s,opt,n,eps));
	for (i=0; i<n; i++) {
		printf("%d ", opt[i]);
	}
	return 0;
}

