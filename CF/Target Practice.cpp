#include <iostream>
using namespace std;
char a[10][10] = {'0'};
int cnt = 0;
int check1(int i, int j)
{
	if (i == 0 || i == 9 || j == 0 || j == 9)
	{
		cnt += 1;
		return 1;
	}
	return 0;
}
int check2(int i, int j)
{
	if (i == 1 || j == 8 || i == 8 || j == 1)
	{
		cnt += 2;
		return 1;
	}
	return 0;
}
int check3(int i, int j)
{
	if (i == 2 || j == 7 || i == 7 || j == 2)
	{
		cnt += 3;
		return 1;
	}
	return 0;
}
int check4(int i, int j)
{
	if (i == 3 || j == 6 || i == 6 || j == 3)
	{
		cnt += 4;
		return 1;
	}
	return 0;
}
int check5(int i, int j)
{
	if (i == 4 || j == 5 || i == 5 || j == 4)
	{
		cnt += 5;
		return 1;
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; j++)
				cin >> a[i][j];
		for (int i = 0; i < 10; ++i)
			for (int j = 0; j < 10; ++j)
			{
				if (a[i][j] == 'X')
				{
					if (check1(i,j)) continue;
					if (check2(i, j)) continue;
					if (check3(i, j)) continue;
					if (check4(i, j)) continue;
					check5(i, j);
				}
			}
		cout << cnt << "\n";
		cnt = 0;
	}
	
}