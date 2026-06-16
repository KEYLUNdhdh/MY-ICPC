#include <stdio.h>

/* 算法1-6：计算1~n与1~m每一项相互乘积的和 SumProducts(n,m) */
int SumProducts( int n, int m)
{
	int ans = 0;
	for (int i = 1; i <= n;i++)
		for (int j = 1; j <= m;j++)
			ans += i * j;
	return ans;
}

/* 算法1-6 结束 */

int main(void)
{
	int n, m;

	scanf("%d %d", &n, &m);
	printf("%d\n", SumProducts(n, m));

	return 0;
}
