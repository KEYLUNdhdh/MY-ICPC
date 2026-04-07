#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    map<int, vector<int>> mp;
    for (int i = 1; i <= n;i++)
        mp[a[i]].push_back(i);
    i64 ans = 0;
    for(auto &[x,y] : mp)
    {
        //0作为哨兵节点
        y.insert(y.begin(), 0);
        for (int i = 1; i < y.size();i++)
        {
            int l = y[i - 1];
            int r = n - y[i] + 1;
            ans += 1ll * r * (r + 1) / 2 * (y[i] - l);
        }
    }
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}