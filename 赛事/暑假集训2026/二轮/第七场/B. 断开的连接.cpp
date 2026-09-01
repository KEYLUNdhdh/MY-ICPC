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
vector<vector<i64>> dp(51, vector<i64>(10, 0));

void precom()
{
    for (int i = 0; i < 10;i++)
        dp[0][i] = 1;
    for (int i = 1; i <= 50; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int k = j; k < 10;k++)
                dp[i][j] += dp[i - 1][k];
        }
    }
}

void solve()
{
    string s;
    cin >> s;
    if(s == "Alice")
    {
        i64 x;
        cin >> x;
        int lst = 0;
        string ans = "";
        for (int i = 50; i >= 1;i--)
        {
            for (int d = lst; d < 10;d++)
            {
                if(x < dp[i - 1][d])
                {
                    ans += to_string(d);
                    lst = d;
                    break;
                }
                else
                    x -= dp[i - 1][d];
            }
        }

        cout << ans << endl;
    }
    else
    {
        string p;
        cin >> p;
        debug(p);
        sort(p.begin(), p.end());
        i64 x = 0;
        int lst = 0;
        for (int i = 0; i < 50;i++)
        {
            int len = 50 - i;
            int cur = p[i] - '0';
            debug(lst, i, len, cur);
            for (int d = lst; d < cur;d++)
                x += dp[len - 1][d];
            lst = cur;
        }
        cout << x << endl;
    }
}

bool ED;

signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    precom();
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}