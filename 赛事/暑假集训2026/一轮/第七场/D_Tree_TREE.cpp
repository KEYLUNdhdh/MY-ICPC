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
using u32 = unsigned int;
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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> sz(n + 1, 0);
    vector<i64> ans(n + 1, 0);
    i64 cur = 0;
    auto dfs = [&](auto self, int u, int p) -> void
    {
        sz[u] = 1;
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u);
            sz[u] += sz[v];
        }

        if(sz[u] >= k)
            cur++;
    };
    dfs(dfs, 1, 0);
    ans[1] = cur;

    auto dfs2 = [&](auto self, int u, int p) -> void
    {
        if(u > 1)
        {
            int np = n - sz[u];
            int nu = n;
            ans[u] = ans[p] - 1 - (sz[u] >= k) + (np >= k) + 1;
        }
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u);
        }
    };
    dfs(dfs2, 1, 0);
    i64 sum = 0;
    for (int i = 1; i <= n;i++)
        sum += ans[i];
    cout << sum << "\n";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}