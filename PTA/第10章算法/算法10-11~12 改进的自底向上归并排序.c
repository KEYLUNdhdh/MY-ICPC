#include <stdio.h>
#include <stdlib.h>


typedef int ElemSet; /* 默认元素为整数*/

int Min( int x, int y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法10-11：改进二路归并 TwoWayMergeImproved(a,t,l,m,r) */
void TwoWayMergeImproved(ElemSet *a, ElemSet *t, int l, int m, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法10-11 结束 */ 

/* 算法10-12：改进的自底向上归并排序 MergeSortBottomUpImproved(a,l,r) */
void MergeSortBottomUpImproved(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-12 结束 */ 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	MergeSortBottomUpImproved(a, 0, n-1);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

