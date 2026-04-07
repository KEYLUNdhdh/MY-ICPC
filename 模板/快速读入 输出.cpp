#include <iostream>
#include <stdio.h>
#define int long long
using namespace std;
//快读//getchar_unlocked更快，但可能出现读入错误，慎用吧
///getchar_unlocked适用于基于lunix的机器,交到洛谷上可以，windows跑不行
inline int read()
{
	char ch;
	ch = getchar();
	//ch = getchar_unlocked();
	int f = 1;
	while (ch > '9' || ch < '0')
	{
		if (ch == '-') f = -1;
		ch = getchar();
		//ch = getchar_unlocked();
	}
	int k = 0;
	while (ch >= '0' && ch <= '9')
	{
		k = k * 10 + (ch - '0');
		ch = getchar();
		//ch = getchar_unlocked();
	}
	return k * f;
}
//快输//递归写法
inline void out(int x)
{
	char ch;
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else out(x / 10), putchar(x % 10 + '0');
}
signed main()
{
	int n; cin >> n;
	int sum = 0;
	int temp;
	while (n--)
	{
		temp = read();
		sum += temp;
	}
	out(sum);
}