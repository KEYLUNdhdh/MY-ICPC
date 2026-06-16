#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 默认元素为整数*/

void XSort(ElemSet *a, int l, int r);

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n); /* 声明空间 */
	for (i=0; i<n; i++) { /* 读入待排序列 */
		scanf("%d", &a[i]);
	}
	XSort(a, 0, n-1); /* 排序 */
	/* 输出有序序列 */
	printf("%d", a[0]);
	for (i=1; i<n; i++) {
		printf(" %d", a[i]);
	} 

	return 0;
}

void XSort(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 

