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
    int tp;
    map<int, int> mp;
    for (int i = 0; i < n;i++)
    {
        cin >> tp;
        mp[tp]++;
    }
    int lst = -1;
    int cnt = 0;
    int ans = 0;
    for(auto &[x,y] : mp)
    {
        ans += min(mp[x], mp[x - 1]);
    }
    cout << n - ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}