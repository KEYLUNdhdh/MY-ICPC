#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

typedef int ElemSet; /* 默认元素为整数*/
#define kMaxDigit 4

typedef int DigitSet; /* 默认元素的每一位为整数*/

DigitSet GetDigit(ElemSet ai, int radix, int k, int d)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法10-16：基数排序中使用的计数排序 CountingSort2(a,l,r,radix,k,d) */
int *CountingSort2(ElemSet *a, int l, int r, int radix, int k, int d)
{
	ElemSet *b;
	DigitSet *c; 
	int *cnt, i, p;
	
	b = (ElemSet *)malloc(sizeof(ElemSet) * (r-l+1)); /* 临时存放有序序列的数组 */
	c = (DigitSet *)malloc(sizeof(DigitSet) * (r-l+1)); /* 存储元素第k位的数组 */
	cnt = (int *)malloc(sizeof(int) * radix); /* 计数数组 */
	memset(cnt, 0, sizeof(int)*radix); /* 初始全零 */
	for (i=l; i<=r; i++) {
		c[i-l] = GetDigit(a[i], radix, k, d); /* 得到a[i]在基数radix下元组表示的第k位 */
		cnt[c[i-l]]++;
	}
	for (i=1; i<radix; i++) {
		cnt[i] += cnt[i-1];
	}
	for (i=r; i>=l; i--) {
		p = cnt[c[i-l]]-1; /* a[i]应该在b中的位置。注意b数组下标从0开始 */
		b[p] = a[i];   /* 将a[i]放入 */
		cnt[c[i-l]]--;
	}
	for (i=l; i<=r; i++) {
		a[i] = b[i-l]; /* 将有序的b放回a中。注意b数组下标从0开始 */
	}
	free(b);
	free(c);
	return cnt;
}
/* 算法10-16 结束 */ 

/* 算法10-17：MSD基数排序 MSDRadixSort(a,l,r,radix,k,d) */
void MSDRadixSort(ElemSet *a, int l, int r, int radix, int k, int d)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法10-17 结束 */ 

/* 算法10-18：LSD基数排序 LSDRadixSort(a,l,r,radix,d) */
void LSDRadixSort(ElemSet *a, int l, int r, int radix, int d)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法10-18 结束 */ 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	MSDRadixSort(a, 0, n-1, 10, 1, kMaxDigit); /* 测试算法10-17 */
//	LSDRadixSort(a, 0, n-1, 10, kMaxDigit);    /* 测试算法10-18 */
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

