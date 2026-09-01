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

template<class T>
T qpow(T a,T b,T MOD)
{
    T res = 1;
    a = (a % MOD + MOD) % MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

template <class T>
T inv(T a,T p)
{
    return qpow(a, p - 2, p);
}

struct Lagrange
{
    int n;
    vector<i64> x, y;

    Lagrange() : n(0) {}

    void addPoint(i64 px, i64 py)
    {
        x.push_back(px);
        y.push_back(py);
        n++;
    }

    i64 query(i64 k)
    {
        k = (k % MOD + MOD) % MOD;
        i64 ans = 0;
        for (int i = 0;i < n;i++)
        {
            i64 num = 1;
            i64 den = 1;

            for (int j = 0;j < n;j++)
            {
                if(i == j)
                    continue;

                num = num * (k - x[j] + MOD) % MOD;
                den = den * (x[i] - x[j] + MOD) % MOD;
            }

            i64 term = y[i] * num % MOD * inv(den, MOD) % MOD;
            ans = (ans + term) % MOD;
        }
        return ans;
    }
};

void solve()
{
    i64 n, k;
    cin >> n >> k;

    int lim = min(n + 1, k + 1);
    vector<vector<i64>> dp(n + 1, vector<i64>(lim, 0));
    vector<vector<i64>> pre(n + 1, vector<i64>(lim, 0));

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto self, int u, int p) -> void
    {
        for (int i = 0; i < lim;i++)
            dp[u][i] = 1;

        for (int v : adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u);
            for (int x = 0; x < lim;x++)
            {
                dp[u][x] = dp[u][x] * pre[v][x] % MOD;
            }
        }
        pre[u][0] = dp[u][0];
        for (int x = 1; x < lim;x++)
            pre[u][x] = (pre[u][x - 1] + dp[u][x]) % MOD;
    };

    dfs(dfs, 1, 0);
    if(k <= n)
        cout << dp[1][k];
    else
    {
        Lagrange lg;
        for (int i = 0; i < n;i++)
            lg.addPoint(i, dp[1][i]);

        cout << lg.query(k);
    }
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