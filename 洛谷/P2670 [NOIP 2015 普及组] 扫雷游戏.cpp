#include <iostream>
using namespace std;
int a[102][102] = { 0 };
int b[102][102] = { 0 };
int xing = '*';
int wen = '?';
int check(int i, int j)
{
	int cnt = 0;
	if (a[i - 1][j - 1] == xing) cnt++;
	if (a[i - 1][j] == xing) cnt++;
	if (a[i - 1][j + 1] == xing) cnt++;
	if(a[i][j - 1] == xing) cnt++;
	if (a[i][j + 1] == xing) cnt++;
	if (a[i + 1][j - 1] == xing) cnt++;
	if (a[i + 1][j] == xing) cnt++;
	if (a[i + 1][j + 1] == xing) cnt++;
	return cnt;
}
int main()
{
	ios::sync_with_stdio(0);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			char ch;
			cin >> ch;
			if (ch == '*')
			{
				a[i][j] = xing;
			}
			else
			{
				a[i][j] = wen;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (a[i][j] == xing)
			{
				continue;
			}
			else
			{
				int temp =  check(i, j);
				a[i][j] = temp;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; ++j)
		{
			if (a[i][j] == xing)
			{
				cout << "*";
				continue;
			}
			cout << a[i][j];
		}
		cout << "\n";
	}
	return 0;
}