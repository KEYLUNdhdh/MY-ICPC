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

    vector<vector<i64>> dp(n + 1, vector<i64>(k + 1, 0));
    vector<i64> siz(n + 1, 0);
    vector<i64> tmp;
    auto dfs = [&](auto self, int u, int p) -> void
    {
        siz[u] = 1;
        dp[u][0] = 1;

        for(int v : adj[u])
        {
            if(v == p)
                continue;

            self(self, v, u);
            i64 sumv = 0;
            for (int i = 0; i <= k;i++)
                sumv = (sumv + dp[v][i]) % MOD;

            tmp.assign(k + 1, 0ll);
            for (int x = 0; x <= min<i64>(k, siz[u]);x++)
            {
                tmp[x] = (tmp[x] + sumv * dp[u][x]) % MOD;

                for (int y = 0; y <= min<i64>(k, siz[v]);y++)
                {
                    if(x + y + 1 <= k)
                    {
                        i64 len = max(x, y + 1);
                        tmp[len] = (tmp[len] + dp[u][x] * dp[v][y]) % MOD;
                    }
                }
            }
            swap(dp[u], tmp);
            siz[u] += siz[v];
        }
    };

    dfs(dfs, 1, 0);
    i64 ans = 0;
    for (int i = 0; i <= k;i++)
        ans = (ans + dp[1][i]) % MOD;

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