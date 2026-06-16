#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef double ElemSet; /* 物品重量和价值均为实数 */
#define eps (1e-9)
typedef struct ObjNode *Objects;
struct ObjNode {
	int idx;    /* 序号 */
	ElemSet w;  /* 重量 */
	ElemSet v;  /* 价值 */
};

int CmpUnitValue(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法15-12：连续背包问题的贪心算法 Knapsack( W, s, x, n ) */
ElemSet Knapsack( ElemSet W, Objects s, double *x, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法15-12 结束 */ 

int main(void)
{
	Objects s;
	double *x;
	ElemSet W;
	int n, i;
	
	scanf("%d %lf", &n, &W);
	s = (Objects)malloc(sizeof(struct ObjNode) * n);
	x = (double *)malloc(sizeof(double) * n);
	memset(x, 0, sizeof(double) * n);
	for (i=0; i<n; i++) {
		scanf("%lf", &s[i].w);
	}
	for (i=0; i<n; i++) {
		scanf("%lf", &s[i].v);
		s[i].idx = i;
	}
	printf("%.2f\n", Knapsack( W, s, x, n ));
	for (i=0; i<n; i++) {
		printf("%.2f ", x[i]);
	}
	return 0;
}

