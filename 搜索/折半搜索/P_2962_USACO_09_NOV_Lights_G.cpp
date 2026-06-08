#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> adj(n + 1, 0);
    for (int i = 0; i < n;i++)
        adj[i] |= (1ll << i);

    for (int i = 0;i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u] |= (1ll << v);
        adj[v] |= (1ll << u);
    }

    i64 mask = (1ll << n) - 1;
    int len = n / 2;
    map<i64, int> mp;

    auto dfsl = [&](auto self, int idx, i64 cur, int cnt) -> void
    {
        if(idx == len)
        {
            if(mp.find(cur) == mp.end())
                mp[cur] = cnt;
            else
                chmin(mp[cur], cnt);
            return;
        }

        self(self, idx + 1, cur, cnt);
        self(self, idx + 1, cur ^ adj[idx], cnt + 1);
    };

    dfsl(dfsl, 0, 0, 0);

    i64 ans = INF;  
    debug(ans)
    auto dfsr = [&](auto self, int idx, i64 cur, int cnt) -> void
    {
        if(idx == n)
        {
            if(mp.count(cur ^ mask))
                chmin(ans, (i64)mp[cur ^ mask] + cnt);
            return;
        }

        self(self, idx + 1, cur, cnt);
        self(self, idx + 1, cur ^ adj[idx], cnt + 1);
    };

    dfsr(dfsr, len, 0, 0);
    debug(ans)
    cout << ans;
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}