#include <stdio.h>
#include <stdlib.h>


typedef int ElemSet; /* 默认元素为整数*/

/* 算法10-8 二路归并 TwoWayMerge(a,l_x,r_x,l_y,r_y) */
ElemSet *TwoWayMerge(ElemSet *a, int l_x, int r_x, int l_y, int r_y)
{
	int i, j, k, n;
	ElemSet *t;
	
	n = (r_x-l_x+1) + (r_y-l_y+1); /* 两个序列元素的总个数 */
	t = (ElemSet *)malloc(sizeof(ElemSet) * n); /* 创建临时数组 */
	i = l_x;
	j = l_y;
	k = 0;
	while (i<=r_x || j<=r_y) {
		if (j>r_y || (i<=r_x && a[i]<=a[j])) {
			t[k] = a[i]; /* 将a[i]添加至t末尾 */
			i++;
		}
		else {
			t[k] = a[j]; /* 将a[j]添加至t末尾 */
			j++;
		}
		k++;
	}
	return t;
}
/* 算法10-8 结束 */ 

/* 算法10-9 归并排序 MergeSort(a,l,r) */
void MergeSort(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-9 结束 */ 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	MergeSort(a, 0, n-1);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

