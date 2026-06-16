#include <bits/stdc++.h>
using namespace std;

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

inline void out(int x)
{
	char ch;
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else out(x / 10), putchar(x % 10 + '0');
}
