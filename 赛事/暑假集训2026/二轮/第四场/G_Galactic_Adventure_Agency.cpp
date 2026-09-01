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
    vector<vector<pll>> adj(n + 1);
    vector<array<i64, 3>> co(n + 1);
    for (int i = 1; i < n;i++)
    {
        i64 u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    for (int i = 1; i <= n;i++)
        cin >> co[i][0] >> co[i][1] >> co[i][2];

    vector<array<i64, 8>> dpl(n + 1), dpr(n + 1);
    i64 ans = 0;
    auto dfs = [&](auto self, int u, int p, i64 w) -> void
    {
        for (int i = 0; i < 8;i++)
        {
            int c1 = (i & 1) ? 1 : -1;
            int c2 = (i & 2) ? 1 : -1;
            int c3 = (i & 4) ? 1 : -1;
            i64 val = c1 * co[u][0] + c2 * co[u][1] + c3 * co[u][2];
            dpl[u][i] = w + val;
            dpr[u][i] = w - val;
        }

        for(auto &[v, ww] : adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u, w + ww);

            for (int i = 0; i < 8;i++)
            {
                chmax(ans, dpl[u][i] + dpr[v][i] - 2 * w);
                chmax(ans, dpl[v][i] + dpr[u][i] - 2 * w);
            }

            for (int i = 0; i < 8;i++)
            {
                chmax(dpl[u][i], dpl[v][i]);
                chmax(dpr[u][i], dpr[v][i]);
            }
        }
    };

    dfs(dfs, 1, 0, 0);
    cout << ans;
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}