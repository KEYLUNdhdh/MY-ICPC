#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 默认元素为整数*/

/* 算法10-1：插入排序  InsertionSort(a,l,r) */
void InsertionSort(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-1 结束 */ 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n); /* 声明空间 */
	for (i=0; i<n; i++) { /* 读入待排序列 */
		scanf("%d", &a[i]);
	}
	InsertionSort(a, 0, n-1); /* 排序 */
	for (i=0; i<n; i++) { /* 输出有序序列 */
		printf("%d ", a[i]);
	} 

	return 0;
}

