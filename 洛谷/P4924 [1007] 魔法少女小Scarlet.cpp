#include <iostream>
using namespace std;
int a[505][505] = { 0 };
int b[505][505] = { 0 };

void ni(int x, int y, int r)
{
	int m = y - r;
	int n = x + r;
	for (int i = x - r; i <= x + r; ++i)
	{
		for (int j = y - r; j <= y + r; ++j)
		{
			b[n][m] = a[i][j];
			n--;
		}
		m++;
		n = x + r;
	}
	for (int i = x - r; i <= x + r; ++i)
	{
		for (int j = y - r; j <= y + r; ++j)
		{
			a[i][j] = b[i][j];
		}
	}
}
void shun(int x, int y, int r)
{
	int n = x - r;
	int m = y + r;
	for (int i = x - r; i <= x + r; ++i)
	{
		for (int j = y - r; j <= y + r; ++j)
		{
			b[n][m] = a[i][j];
			n++;
		}
		m--;
		n = x - r;
	}
	for (int i = x - r; i <= x + r; ++i)
	{
		for (int j = y - r; j <= y + r; ++j)
		{
			a[i][j] = b[i][j];
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	int cot = 0;
	int n, m; cin >> n >> m;
	//初始化
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = ++cot;
		}
	}
	while (m--)
	{
		int x, y, r, z; cin >> x >> y >> r >> z;
		if (z == 0)//顺时针
		{
			shun(x-  1, y - 1, r);
		}
		else//逆时针
		{
			ni(x  - 1, y - 1, r);
		}

	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
}