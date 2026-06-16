#include <stdio.h>
#include <stdlib.h>


typedef int ElemSet; /* 默认元素为整数*/
#define Swap(x, y) { ElemSet t = x; x = y; y = t; }
 
/* 算法10-5：冒泡排序 BubbleSort(a,l,r) */
void BubbleSort(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-5 结束 */ 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	BubbleSort(a, 0, n-1);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

