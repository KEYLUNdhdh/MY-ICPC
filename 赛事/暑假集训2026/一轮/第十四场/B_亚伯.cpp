// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
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
#define KEYLUN main
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
void debug_out() { cerr << "\n"; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char* names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char* names, Head H, Tail... T) {
    while (*names == ' ' || *names == ',') names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i) {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[') bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']') bracket--;
        else if (names[i] == ',' && bracket == 0) break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H) cerr << v << " ";
    cerr << "\n"; 
    
    debugarr_out(names + i + 1, T...);
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template<class T> void chmin(T &a, T b) { if (a > b) a = b; }
template<class T> void chmax(T &a, T b) { if (a < b) a = b; }
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;


void solve()
{
    int n;
    cin >> n;
    int m = n;
    vector<vector<int>> adj(n + 1);
    vector<int> siz(n + 1, 0);
    for (int i = 2; i <= n;i++)
    {
        int p;
        cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }

    vector<i64> hp(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> hp[i];

    vector<vector<array<i64, 2>>> dp(n + 1, vector<array<i64, 2>>(n + 1, {INF, INF}));

    // dp[u][j][0/1] u为根的子树，有 j 个节点不适用魔法，且u本身是否使用魔法的最小代价
    // 0 不用 1 用
    auto dfs = [&](auto self, int u, int p) -> void
    {
        // u本身初始化
        siz[u] = 1;
        dp[u][0][1] = 0;
        dp[u][1][0] = hp[u];
        // 感觉转移没问题啊
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u);
            vector<array<i64, 2>> ndp(n + 1, {INF, INF});

            for (int j = 0; j <= siz[u];j++)
            {
                for (int k = 0;k <= siz[v];k++)
                {
                    // u 用魔法
                    if(dp[u][j][1] != INF)
                    {
                        i64 minn = min(dp[v][k][0], dp[v][k][1]);
                        if(minn != INF)
                            chmin(ndp[j + k][1], dp[u][j][1] + minn);
                    }

                    // u 不用魔法
                    if(dp[u][j][0] != INF)
                    {
                        i64 mv0 = (dp[v][k][0] != INF) ? (dp[v][k][0] + hp[v]) : INF;
                        i64 mv1 = dp[v][k][1];
                        i64 minn = min(mv0, mv1);
                        if(minn != INF)
                            chmin(ndp[j + k][0], dp[u][j][0] + minn);
                    }

                }
            }
            siz[u] += siz[v];
            swap(dp[u], ndp);
        }
    };

    dfs(dfs, 1, 0);
    vector<i64> ans(m + 1, INF);
    for (int i = 0; i <= m;i++)
    {
        int idx = m - i;
        ans[idx] = min(dp[1][i][0], dp[1][i][1]);
        debug(i, idx, ans[idx]);
    }
    for (int i = 1; i <= m;i++)
        chmin(ans[i], ans[i - 1]);
    for (int i = 0; i <= m;i++)
        cout << ans[i] << " ";
    cout << "\n";
    cutline
    // auto dfs1 = [&](auto self, int u, int p) -> void
    // {
    //     dp[u][0] = hp[u];
    //     for(int v : adj[u])
    //     {
    //         if(v == p)
    //             continue;
    //         self(self, v, u);
    //         dp[u][0] += dp[v][0] + hp[v];
    //         cost[u].push_back(hp[v]);
    //         siz[u] += siz[v];
    //     }
    //     sort(cost[u].rbegin(), cost[u].rend());
    //     int len = cost[u].size();
    //     for (int i = len - 2; i >= 0;i--)
    //         cost[u][i] = cost[u][i + 1] + cost[u][i];
    //     cost[u].push_back(0);
    // };
    // dfs1(dfs1, 1, 0);

    // auto dfs2 = [&](auto self, int u, int p) -> void
    // {
    //     siz[u] = 1;
    //     // for (int k = 1; k <= min<int>(m, adj[u].size() - 1);k++)
    //     // {
    //     //     dp[u][k] = cost[u][k];
    //     //     debugarr(cost[u]);
    //     //     debug(u, k, dp[u][k]);
    //     //     // for (int i = min<int>(m, adj[u].size() - 1); i >= k;i--)
    //     //     // {
    //     //     //     chmin(dp[u][i], dp[u][i - k] + cost[u][k]);
    //     //     // }
    //     // }
    //     for(int v : adj[u])
    //     {
    //         if(v == p)
    //             continue;
    //         self(self, v, u);
    //         for (int mu = min(m, siz[u] + siz[v]); mu >= 0;mu--)
    //         {
    //             // if(dp[u][mu] == INF)
    //             //     continue;
    //             for (int mv = min(siz[v], m - mu); mv >= 0;mv--)
    //             {
    //                 if(dp[v][mv] != INF)
    //                     chmin(dp[u][mv + mu], dp[u][mu] + dp[v][mv]);
    //             }
    //             siz[u] += siz[v];
    //         }
    //     }

    //     // 在 u 处抹除 k 个儿子
    //     for (int k = 1; k <= min<int>(m, adj[u].size() - 1);k++)
    //     {
    //         if(dp[u][k] != INF)
    //             dp[u][k] += cost[u][k];
    //         // for (int i = min<int>(m, adj[u].size() - 1); i >= k;i--)
    //         // {
    //         //     chmin(dp[u][i], dp[u][i - k] + cost[u][k]);
    //         // }
    //     }
    // };

    // dfs2(dfs2, 1, 0);
    // // for (int i = 1; i <= n;i++)
    // //     cerr << dp[i][0] << " ";
    // // cerr << "\n";

    // for (int i = 1; i <= n;i++)
    // {
    //     for (int j = 0; j <= m;j++)
    //         cerr << dp[i][j] << " ";
    //     cerr << "\n";
    // }
    // cutline
    // for (int i = 0; i <= n; i++)
    //     cout << dp[1][i] << " ";
    // cout << "\n";
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}