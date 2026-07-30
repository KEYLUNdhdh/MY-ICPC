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
// bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

// k其实约束的是什么？
// 每个点我能重复选几次
// 这个挺关键。
// 我们应该贪心的去选
// 所以 度小于等于 k 的点它的所有边我都应该选。
// 会有连锁问题吗， 会有。
// 所以优先从大的边处理
// 有道理的
// 没道理的
// 那就dp吧
struct e
{
    i64 u, v;
    i64 w;

    bool operator<(const e &b) const
    {
        return w < b.w;
    }
};
void solve()
{
    int n, k;
    cin >> n >> k;

    vector<vector<pll>> adj(n + 1);
    // vector<i64> maxx(n + 1, k), deg(n + 1, 0);
    // vector<e> edges;
    for (int i = 1; i <= n - 1;i++)
    {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    // for (int i = 1;i <= n;i++)
    //     sort(adj[i].begin(), adj[i].end(), [](pll p, pll q){return p.first > q.first;});
        // 0 k - 1 1 k
    vector<array<i64, 2>> dp(n + 1, {0, 0});
    auto dfs = [&](auto self, int u, int p) -> void
    {
        for(auto &[w, v] : adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u);
        }
        int lim0 = k - 1, lim1 = k;

        sort(adj[u].begin(), adj[u].end(), [&](pll p, pll q){
            int vp = p.second, vq = q.second;
            int wp = p.first, wq = q.first;
            return wp + dp[vp][0] - dp[vp][1] > wq + dp[vq][0] - dp[vq][1];
        });
        // debug(u)
        for(auto &[w, v] : adj[u])
        {
            if(v == p)
                continue;
            if(lim1 >= 1)
            {
                if(w + dp[v][0] > dp[v][1])
                    dp[u][1] += w + dp[v][0], lim1--;
                else
                    dp[u][1] += dp[v][1];
            }
            else
                dp[u][1] += dp[v][1];
            
            if(lim0 >= 1)
            {
                if(w + dp[v][0] > dp[v][1])
                    dp[u][0] += w + dp[v][0], lim0--;
                else
                    dp[u][0] += dp[v][1];
            }
            else
                dp[u][0] += dp[v][1];
        }
    };

    dfs(dfs, 1, 0);
    // for (int i = 1;i <= n;i++)
    // {
    //     cerr << dp[i][0] << " " << dp[i][1] << "\n";
    // }
    // cutline
    cout << max(dp[1][0], dp[1][1]) << "\n";
}

// bool ED;
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