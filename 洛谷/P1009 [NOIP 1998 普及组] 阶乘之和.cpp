#include <iostream>
using namespace std;

int a[100000000] = { 0 };
int b[100000000] = { 0 };
int cnt = 1;

void highadd(int a[], int b[])
{
	int g = 0;
	for (int i = 0; i <= cnt; i++)
	{
		b[i] += a[i] + g;
		g = b[i] / 10;
		b[i] %= 10;
	}
}
void highmultiple(int a[], int key)
{
	for (int i = 0; i <= cnt; i++)
	{
		a[i] *= key;
	}
	for (int i = 0; i <= cnt; i++)
	{
		if (a[i] > 9)
		{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}
	for (int i = cnt + 4; i >= 0; i--)
	{
		if (a[i] != 0)
		{
			cnt = i + 1;
			break;
		}
	}
}
int main()
{
	a[0] = 1;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		highmultiple(a, i + 1);
		highadd(a, b);
	}

	for (int i = cnt; i >= 0; i--)
	{
		if (i == cnt && b[i] == 0) continue;
		cout << b[i];
	}
}