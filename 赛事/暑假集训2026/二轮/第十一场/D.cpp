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
void debug_out(Head H, Tail... T)
{
    cerr << " " << H;
    debug_out(T...);
}
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char *names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char *names, Head H, Tail... T)
{
    while (*names == ' ' || *names == ',')
        names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i)
    {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[')
            bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']')
            bracket--;
        else if (names[i] == ',' && bracket == 0)
            break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H)
        cerr << v << " ";
    cerr << "\n";

    debugarr_out(names + i + 1, T...);
}
#define cutline                             \
    {                                       \
        cerr << "----------------------\n"; \
    }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template <class T>
void chmin(T &a, T b)
{
    if (a > b)
        a = b;
}
template <class T>
void chmax(T &a, T b)
{
    if (a < b)
        a = b;
}
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

void solve()
{
    string a, b;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    a = "*" + a, b = "*" + b;
    vector<vector<int>> dp(n + 2, vector<int>(m + 2, inf));
    vector<array<int, 2>> nxta(n + 2, {n + 1, n + 1}), nxtb(m + 2, {m + 1, m + 1});
    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i + 1] == '1')
        {
            nxta[i][1] = i + 1;
            nxta[i][0] = nxta[i + 1][0];
        }
        else
        {
            nxta[i][0] = i + 1;
            nxta[i][1] = nxta[i + 1][1];
        }
    }

    for (int i = m - 1; i >= 0; i--)
    {
        if (b[i + 1] == '1')
        {
            nxtb[i][1] = i + 1;
            nxtb[i][0] = nxtb[i + 1][0];
        }
        else
        {
            nxtb[i][0] = i + 1;
            nxtb[i][1] = nxtb[i + 1][1];
        }
    }

    dp[n + 1][m + 1] = 0;
    for (int i = n + 1; i >= 0; i--)
    {
        for (int j = m + 1; j >= 0; j--)
        {
            // 0
            int nxi = nxta[i][0], nxj = nxtb[j][0];
            chmin(dp[i][j], dp[nxi][nxj] + 1);
            // 1
            nxi = nxta[i][1], nxj = nxtb[j][1];
            chmin(dp[i][j], dp[nxi][nxj] + 1);
        }
    }

    string ans = "";
    int x = 0, y = 0;
    debug(x, y);
    while (!(x == n + 1 && y == m + 1))
    {
        int nx0 = nxta[x][0], ny0 = nxtb[y][0], nx1 = nxta[x][1], ny1 = nxtb[y][1];
        if(dp[nx0][ny0] + 1 == dp[x][y])
        {
            ans += '0';
            x = nx0, y = ny0;
        }
        else
        {
            ans += '1';
            x = nx1, y = ny1;
        }
        debug(x, y);
    }
    cout << ans;
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}