#include <stdio.h>

#define kMaxN 100000
typedef int ElemSet; /* 默认元素为整数*/
#define Swap(x, y) { ElemSet t = x; x = y; y = t; }

void RightShift( ElemSet array[], int n, int m );

int main(void)
{
	ElemSet array[kMaxN];
	int n, m, i;

	scanf("%d %d", &n, &m);
	for( i=0; i<n; i++ )		    
		scanf("%d", &array[i] );
	m %= n;	/* 当m大于等于n时转化成等价的小于n的数 */
	RightShift(array, n, m); /* 循环右移m位　*/
	for( i=0; i<n-1; i++ )   /* 打印输出 */
		printf("%d ", array[i]);
	printf("%d\n", array[n-1]);
    return 0;
}

void RightShift( ElemSet array[], int n, int m )
{
	int tmp[kMaxN];
	for (int i = 0; i < n;i++)
	{
		int idx = (i + m) % n;
		tmp[idx] = array[i];
	}

	for (int i = 0; i < n;i++)
		array[i] = tmp[i];
}


