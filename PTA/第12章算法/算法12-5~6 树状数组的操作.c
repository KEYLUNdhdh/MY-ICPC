#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int ElemSet;  /* 默认元素为整型 */

/* 算法12-5 树状数组区间求前缀和 GetPrefixSum(c, k) */
ElemSet GetPrefixSum(ElemSet c[], int k)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法12-5 结束 */ 

/* 算法12-6 树状数组单点修改的伪代码：Update(c, n, k, d) */
void Update(ElemSet c[], int n, int k, ElemSet d)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法12-6 结束 */ 

#define kMaxSize 1000

int main(void)
{
	ElemSet a[kMaxSize], c[kMaxSize], s[kMaxSize];
	int n, k;
	
	memset(c, 0, sizeof(c));
	scanf("%d", &n);
	for (k=1; k<=n; k++) {
		scanf("%d", &a[k]);
		Update(c, n, k, a[k]);
	}
	for (k=1; k<=n; k++) {
		printf("%d ", c[k]);
	}
	printf("\n");
	for (k=1; k<=n; k++) {
		s[k] = GetPrefixSum(c, k);
	}
	for (k=1; k<=n; k++) {
		printf("%d ", s[k]);
	}
	printf("\n");

	return 0;
}

