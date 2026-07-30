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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

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

// 翻转 - xi
// 0 -> 1 + y1
void solve()
{
    int n;
    string s;
    cin >> n >> s;
    s = "*" + s;
    for (int i = 1;i <= n;i++)
        if(s[i] == 'S')
            s[i] = '1';
        else
            s[i] = '0';

    vector<i64> x(n + 1, 0), y(n, 0);
    for (int i = 1; i <= n;i++)
        cin >> x[i];
    for (int i = 1; i <= n - 1;i++)
        cin >> y[i];

    vector<array<i64, 2>> dp(n + 1, {0, 0});
    for (int i = 1; i <= n;i++)
    {
        if(s[i] == '1')
        {
            dp[i][1] = max(dp[i - 1][0] + y[i - 1], dp[i - 1][1]);
            dp[i][0] = -x[i] + max(dp[i - 1][0], dp[i - 1][1]);
        }
        else
        {
            dp[i][1] = max(-x[i] + dp[i - 1][0] + y[i - 1], dp[i - 1][1] - x[i]);
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        }
    }

    cout << max(dp[n][0], dp[n][1]) << "\n";
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
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}