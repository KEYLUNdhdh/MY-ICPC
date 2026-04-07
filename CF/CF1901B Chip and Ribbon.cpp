#include <iostream>
using namespace std;
#define int long long
int n, a[200005], ans;

void wayout()
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	a[0] = 0;
	ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] > a[i - 1])
			ans += a[i] - a[i - 1];
	}
	cout << ans - 1 << "\n";
}

signed main()
{
	int t;
	cin >> t;
	while (t--) wayout();
	return 0;
}