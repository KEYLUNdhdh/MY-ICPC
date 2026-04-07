#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
const i64 MOD = 1e9 + 7;

//其中 Ev[x] 是完全遍历并离开以 [x] 为根的子树所需的时间。
void solve()
{
    int n;
    cin >> n;
    vector<i64> l(n + 1, 0), r(n + 1, 0);
    vector<i64> sz(n + 1, 0);
    vector<i64> ev(n + 1, 0);
    vector<i64> ans(n + 1, 0);
    for (i64 i = 1; i <= n;i++)
        cin >> l[i] >> r[i];
    auto dfs = [&](auto self, i64 x) -> void
    {
        sz[x] = 1;
        if(l[x])
        {
            self(self, l[x]);
            sz[x] += sz[l[x]];
        }
        if(r[x])
        {
            self(self, r[x]);
            sz[x] += sz[r[x]];
        }
        ev[x] = 2 * sz[x] - 1;
        ev[x] %= MOD;
    };
    dfs(dfs, 1);

    auto df = [&](auto self, i64 sum, i64 x) -> void
    {
        ans[x] = (sum + ev[x]) % MOD;
        if(l[x])
            self(self, ans[x], l[x]);
        if(r[x])
            self(self, ans[x], r[x]);
    };
    df(df, 0, 1);
    for (int i = 1; i <= n;i++)
        cout << ans[i] << " ";
    cout << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    i64 T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}