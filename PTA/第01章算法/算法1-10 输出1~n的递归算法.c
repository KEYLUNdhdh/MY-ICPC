#include <stdio.h>

/* 算法1-10：输出1~n的递归算法 RecursivePrint(n) */
void RecursivePrint( int n )
{
	if (n == 0)
		return;
	RecursivePrint(n - 1);
	printf("%d\n", n);
}

/* 算法1-10 结束 */

int main(void)
{
	int n;

	scanf("%d", &n);
	RecursivePrint(n);

	return 0;
}
