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
    int n, q;
    cin >> n >> q;

    vector<i64> v(n + 1, 0), c(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> v[i];
    for (int i = 1; i <= n;i++)
        cin >> c[i];

    while(q--)
    {
        i64 a, b;
        i64 ans = 0;
        cin >> a >> b;
        vector<i64> maxx(n + 1, -INF);
        vector<i64> dp(n + 1, 0);
        pll mx1 = {0, -INF}, mx2 ={0, -INF};
        for (int i = 1; i <= n;i++)
        {
            int co = c[i];
            // 同色
            i64 res1 = maxx[co] + v[i] * a;
            // 异色
            i64 res2;
            if(co != mx1.first)
                res2 = mx1.second + v[i] * b;
            else
                res2 = mx2.second + v[i] * b;
            dp[i] = max({res1, res2, v[i] * b});
            chmax(maxx[co], dp[i]);
            chmax(ans, dp[i]);
            // 更新mx
            if(co == mx1.first)
                chmax(mx1.second, dp[i]);
            else
            {
                pll tmp = mx1;
                if(maxx[co] > mx1.second)
                {
                    mx1.first = co;
                    mx1.second = maxx[co];
                    mx2 = tmp;
                }
                else if(maxx[co] > mx2.second)
                {
                    mx2.first = co;
                    mx2.second = maxx[co];
                }
            }
        }
        cout << ans << "\n";
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