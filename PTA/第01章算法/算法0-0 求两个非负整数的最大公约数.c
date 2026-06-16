#include <stdio.h>

/* 算法0-0：求两个非负整数的最大公约数GCD(x, y) */ 
int GCD(int x, int y)
{
    if(x < y)
	{
		int tmp = x;
		x = y;
		y = tmp;
	}
	return (y == 0 ? x : GCD(y, x % y));
}

/* 算法0-0 结束 */ 

int main()
{
	int x, y;
	
	scanf("%d %d", &x, &y);
	printf("%d\n", GCD(x,y));
	
	return 0;
}
