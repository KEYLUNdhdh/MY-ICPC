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
typedef tuple<int, int, int> piii;
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
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);

    for (int i = 1; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<i64> siz(n + 1, 0);
    vector<i64> ans(n + 1, 0);
    auto dfs1 = [&](auto self, int u, int p) -> i64
    {
        siz[u] = 1;
        for(int v : adj[u])
        {
            if(v == p)
                continue;

            siz[u] += self(self, v, u);
            ans[u] += ans[v];
        }
        ans[u] += siz[u];
        return siz[u];
    };

    dfs1(dfs1, 1, 0);
    debug(ans[1])

    auto dfs2 = [&](auto self, int u, int p) -> void
    {
        for(int v : adj[u])
        {
            if(v == p)
                continue;

            ans[v] = ans[u] + n - siz[v] - siz[v];
            self(self, v, u);
        }
    };

    dfs2(dfs2, 1, 0);
    debug(ans[1])

    i64 maxx = 0;
    for (int i = 1; i <= n;i++)
        chmax(maxx, ans[i]);

    cout << maxx;
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