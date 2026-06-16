#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef double ElemSet; /* 物品重量和价值均为实数 */
#define eps (1e-9)
typedef struct ObjNode *Objects;
struct ObjNode {
	ElemSet w;  /* 重量 */
	ElemSet v;  /* 价值 */
};
ElemSet opt_value;
int *opt;
 
ElemSet Max( ElemSet x, ElemSet y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法15-13：离散背包问题的递归分治解法 Knapsack01( W, s, x, f, n, i ) */
ElemSet Knapsack01( ElemSet W, Objects s, int *x, ElemSet f, int n, int i )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法15-13 结束 */

int main(void)
{
	Objects s;
	ElemSet W;
	int *x;
	int n, i;
	
	scanf("%d %lf", &n, &W);
	s = (Objects)malloc(sizeof(struct ObjNode) * n);
	x = (int *)malloc(sizeof(int) * n);
	memset(x, 0, sizeof(int) * n);
	opt = (int *)malloc(sizeof(int) * n);
	memset(opt, 0, sizeof(int) * n);
	for (i=0; i<n; i++) {
		scanf("%lf", &s[i].w);
	}
	for (i=0; i<n; i++) {
		scanf("%lf", &s[i].v);
	}
	opt_value = 0.0;
	printf("%.2f\n", Knapsack01( W, s, x, 0.0, n, 0 ));
	for (i=0; i<n; i++) {
		printf("%d ", opt[i]);
	}
	return 0;
}

