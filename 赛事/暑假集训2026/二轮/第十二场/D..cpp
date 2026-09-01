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
constexpr i64 MOD = 1e9 + 7, INF = 2e18;


void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n + 1, 0), pre(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i], pre[i] = pre[i - 1] ^ a[i];
    vector<i64> p(62, 0);
    p[0] = 1;
    for (int i = 1; i < 62;i++)
        p[i] = p[i - 1] * 2 % MOD;
    vector<array<i64, 2>> s(62, {0, 0});
    vector<i64> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < 62;i++)
        s[i][0] = 1;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 0; j < 62;j++)
        {
            i64 cur = (1ll << j) & pre[i];
            if(cur)
                dp[i] = (dp[i] + p[j] * s[j][0] % MOD) % MOD;
            else
                dp[i] = (dp[i] + p[j] * s[j][1] % MOD) % MOD;
        }

        for (int j = 0; j < 62;j++)
        {
            i64 cur = (1ll << j) & pre[i];
            if(cur)
                s[j][1] = (dp[i] + s[j][1]) % MOD;
            else
                s[j][0] = (dp[i] + s[j][0]) % MOD;
        }
    }

    cout << dp[n];
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