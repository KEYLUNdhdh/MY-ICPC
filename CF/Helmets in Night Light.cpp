#include <iostream>
#include <algorithm>
#include <map>
#define int long long
using namespace std;
int t, n,p,ans,a[100005],b[100005];
void wayout()
{
	multimap < const int, int > ab;
	cin >> n >> p;
	int col = n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	for (int i = 0; i < n; ++i) ab.insert(make_pair(b[i], a[i]));
	auto it = ab.begin();
	ans = 0;
	while (col--)
	{
		if (col == n-1)
		{
			ans += p;continue;
		}
		if (it->first >= p)
		{
			ans += p; continue;
		}
		if (it->second != 0)
		{
			ans += it->first;
			it->second--;
		}
		else
		{
			it++;
			if (it->first >= p)
			{
				ans += p; continue;
			}
			ans += it->first;
			it->second--;
		}
	}
	cout << ans << "\n";
	ab.clear();
}

signed main()
{
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) wayout();
	return 0;
}