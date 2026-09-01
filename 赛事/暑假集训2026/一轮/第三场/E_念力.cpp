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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;
constexpr ld eps = 1e-12;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> s(m + 1, 0);
    for (int i = 1; i <= m;i++)
        cin >> s[i];

    
    // 所有独立 s[i] 跳 i 步赢的概率
    vector<vector<ld>> dp(n + 1, vector<ld>(n + 1, 0.));
    for (int i = 1; i <= n - 1;i++)
        dp[i][1] = 1. / (ld)(n - i);

    for (int k = 2; k <= n - 1; k++)
    {
        for (int i = 1; i + k <= n;i++)
        {
            for (int j = 1; j + i <= n - 1;j++)
                dp[i][k] += dp[i + j][k - 1];
            dp[i][k] *= 1. / (ld)(n - i);
        }
    }
    debug(n)

    // 所有独立 s[i] 前 i 步赢的概率
    vector<vector<ld>> pre(n + 1, vector<ld>(n + 1, 0.));
    for (int i = 1; i <= n - 1;i++)
    {
        for (int k = 1; k <= n;k++)
            if(k == 1)
                pre[i][k] = dp[i][k];
            else
                pre[i][k] = pre[i][k - 1] + dp[i][k];
    }
    debug(n)

    // 所有给定 m 个 s[i] 前 i 步不赢的概率
    vector<ld> k(n + 1, 1);
    for (int i = 1; i <= n - 1;i++)
    {
        for (int j = 1; j <= m;j++)
            k[i] *= (1. - pre[s[j]][i]);
    }
    debug(n)
    vector<ld> ans(m + 1, 0);
    for (int i = 1; i <= m;i++)
    {
        i64 num = s[i];
        for (int j = 1; j <= n - 1;j++)
            if(abs(1. - pre[num][j - 1]) <= eps)
                continue;
            else
                ans[i] += dp[num][j] * (k[j - 1]) / (1. - pre[num][j - 1]);
    }

    for (int i = 1; i <= m;i++)
        cout << fixed << setprecision(12) << ans[i] << " ";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}