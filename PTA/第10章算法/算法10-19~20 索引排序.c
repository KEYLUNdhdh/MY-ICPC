#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 默认元素为整数*/

/* 算法10-19：基于插入排序的索引排序 IndexedInsertionSort(a,idx,l,r) */
void IndexedInsertionSort(ElemSet *a, int *idx, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-19 结束 */ 

/* 算法10-20：元素顺序调整 ElementAdjust(a,idx,l,r) */
void ElementAdjust(ElemSet *a, int *idx, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-20 结束 */ 

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
		idx[i] = i;
	}
	IndexedInsertionSort(a, idx, 0, n-1);
	ElementAdjust(a, idx, 0, n-1);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

