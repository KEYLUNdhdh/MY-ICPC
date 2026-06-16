#include <stdio.h>
#include <stdlib.h>

typedef struct ActivityNode *Activities;
struct ActivityNode {
	int start;  /* 开始时间 */
	int finish; /* 结束时间 */
};

int CmpFinish(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法15-11：活动安排问题的贪心算法 ActivitySelection(a, k, n) */
int ActivitySelection(Activities a, int k, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}
 
/* 算法15-11 结束 */ 

int main(void)
{
	Activities a;
	int n, i;
	
	scanf("%d", &n);
	a = (Activities)malloc(sizeof(struct ActivityNode) * (n+1));
	a[0].finish = 0; /* a[0] 是一个虚设的活动，其结束时间为 0 */
	a[0].start = 0;
	for (i=1; i<=n; i++) {
		scanf("%d", &a[i].start);
	}
	for (i=1; i<=n; i++) {
		scanf("%d", &a[i].finish);
	}
	qsort(a, n+1, sizeof(struct ActivityNode), CmpFinish);
	printf("%d", ActivitySelection(a, 0, n));
	
	return 0;
}

