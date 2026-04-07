#include <iostream>
#include <algorithm>
using namespace std;
int a[101] = { 0 };
int cnt = 0;

void check(int p)
{
	if (p == 0 || p == 1) return;
	for (int i = 0; i < p - 1; i++)
	{
		for (int j = i + 1; j < p; j++)
		{
			if (a[i] + a[j] == a[p])
			{
				cnt++;
				return;
			}
			
		}
	}
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, a + n);
	int i = 0;
	while (i != n)check(i++);
	cout << cnt;
}