#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	//n个人，会走2n-3次
	int a[100000] = { 0 };//存储时间
	int N;
	cin >> N;
	int temp;
	int i = 1;
	while (cin >> temp)
	{
		a[i] = temp;
		i++;
	}
	sort(a+1, a + N+1);
	int sum = 0;
	if (N == 1)
	{
		cout << a[1];
		return 0;
	}
	if (N == 2)
	{
		cout << a[2];
		return 0;
	}
	if (N == 3)
	{
		cout << a[1] + a[2] + a[3];
		return 0;
	}
	int j = N;
	for (; j >3; )
	{
		int m = a[1] + a[2] * 2 + a[j];
		int n = a[1] * 2 + a[j] + a[j - 1];
		int temp = m > n ? n : m;
		sum += temp;
		j -= 2;
	}
	if (j == 3)
	{
		sum += a[1] + a[2] + a[3];
	}
	if (j == 2)
	{
		sum += a[2];
	}
	cout << sum;
}

