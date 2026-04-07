#include <bits/stdc++.h>
using namespace std;

int res[1010], a[1010], n, cnt = 0;

void highmultiple()
{
	int c[1010] = { 0 };
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			c[i + j] += res[i] * a[j];
		}
	}
	int g = 0;
	for (int i = 0; i < 500; i++)
	{
		c[i] += g;
		res[i] = c[i] % 10;
		g = c[i] / 10;
	}
}

void highmultiple2()
{
	int c[1010] = { 0 };
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			c[i + j] += a[i] * a[j];
		}
	}
	int g = 0;
	for (int i = 0; i < 500; i++)
	{
		c[i] += g;
		a[i] = c[i] % 10;
		g = c[i] / 10;
	}
}

void quick_pow(int p)
{
	res[0] = 1; a[0] = 2;
	while (p)
	{
		if (p & 1) highmultiple();
		highmultiple2();
		p >>= 1;
	}
}

int main()
{
	cin >> n;
	int lengh = n*log10(2) + 1;
	cout << lengh << "\n";
	quick_pow(n);
	res[0] -= 1;
	for (int i = 499; i >= 0; i--)
	{
		cout << res[i];
		cnt++;
		if (cnt % 50 == 0)cout << "\n";
	}
	return 0;
}