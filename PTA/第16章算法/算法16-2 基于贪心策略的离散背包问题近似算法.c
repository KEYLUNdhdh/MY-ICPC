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

int CmpValue(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int CmpUnitValue(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


ElemSet Greedy( ElemSet W, Objects s, int *x, int n, int (*Cmp)(const void *a, const void *b) )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法16-2：基于贪心策略的离散背包问题近似算法 KnapsackGreedyApproximation(W,s,x,n) */
ElemSet KnapsackGreedyApproximation(ElemSet W, Objects s, int *x, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法16-2 结束 */ 

int main(void)
{
	Objects s;
	int *x;
	ElemSet W;
	int n, i;
	
	scanf("%d %lf", &n, &W);
	s = (Objects)malloc(sizeof(struct ObjNode) * n);
	x = (int *)malloc(sizeof(int) * n);
	for (i=0; i<n; i++) {
		scanf("%lf", &s[i].w);
	}
	for (i=0; i<n; i++) {
		scanf("%lf", &s[i].v);
		s[i].idx = i;
	}
	printf("%.2f\n", KnapsackGreedyApproximation( W, s, x, n ));
	for (i=0; i<n; i++) {
		printf("%d ", x[i]);
	}
	return 0;
}

