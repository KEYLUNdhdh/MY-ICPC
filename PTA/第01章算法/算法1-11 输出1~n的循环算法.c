#include <stdio.h>

/* 算法1-11 ：输出1~n的循环算法 IterativePrint (n) */
void IterativePrint( int n )
{
	for (int i = 1; i <= n;i++)
		printf("%d\n", i);

	return;
}

/* 算法1-11 结束 */

int main(void)
{
	int n;

	scanf("%d", &n);
	IterativePrint(n);

	return 0;
}
