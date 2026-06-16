#include <stdio.h>
#include <stdlib.h>

typedef enum{false, true} bool;
typedef int ElemSet; /* 默认元素为整数*/

int CntSwaps(ElemSet *a, int *idx, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}
 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int *idx;   /* 元素索引 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	idx = (int *)malloc(sizeof(int) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
		idx[a[i]] = i; /* 初始化索引 */
	}
	printf("%d\n", CntSwaps(a, idx, n));

	return 0;
}

