#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int ElemSet; /* 默认元素为整数*/
#define Swap(x, y) { ElemSet t = x; x = y; y = t; }
 
/* 算法10-15：计数排序 CountingSort(a,l,r,k) */
void CountingSort(ElemSet *a, int l, int r, ElemSet k)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-15 结束 */ 

#define kMaxKey 1000

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	CountingSort(a, 0, n-1, kMaxKey);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

