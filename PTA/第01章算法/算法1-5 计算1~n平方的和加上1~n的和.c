#include <stdio.h>

/* 算法1-5：计算1~n^2的和加上1~n的和 SumUp(n) */
int SumUp( int n )
{
	int ans = 0;
	for (int i = 1; i <= n;i++)
		ans += + i;
	for (int i = 1; i <= n * n;i++)
		ans += i;
	return ans;
}

/* 算法1-5 结束 */

int main(void)
{
	int n;

	scanf("%d", &n);
	printf("%d\n", SumUp(n));

	return 0;
}
