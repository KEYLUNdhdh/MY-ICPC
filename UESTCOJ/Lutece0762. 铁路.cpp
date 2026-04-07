#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    if (n > 1 && k == 0)
    {
        cout << 0 << "\n";
        return;
    }
    if (n <=1)
    {
        cout << 0 << "\n";
        return;
    }
    if (k == 1 && n > 2)
    {
        cout << 0 << "\n";
        return;
    }
    int ans = min(n * (n - 1) / 2, n * k / 2);
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t --)
    {
        solve();
    }
    return 0;
}