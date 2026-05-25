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
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
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
constexpr i64 MOD = 998244353, INF = 1e9;
// P_1833_樱花
void solve()
{
    int h1, h2, m1, m2;
    char c;
    int n;
    cin >> h1 >> c >> m1 >> h2 >> c >> m2 >> n;

    i64 v = h2 * 60 + m2 - h1 * 60 - m1;

    vector<pll> item;
    vector<i64> dp(v + 1, 0);
    for (int i = 0;i < n;i++)
    {
        int t, c, p;
        cin >> t >> c >> p;
        if(p == 0)
        {
            for (int j = t; j <= v;j++)//完全背包，正序遍历
                chmax(dp[j], dp[j - t] + c);
        }
        else
        {
            for (int k = 1; k <= p;k <<= 1)//多重背包，二进制拆分。
            {
                p -= k;
                item.push_back({k * t, k * c});
            }
            if(p > 0)
                item.push_back({p * t, p * c});
        }
    }

    for(auto [t, c] : item)//对拆分完的做01背包
    {
        for (int j = v; j >= t;j--)
            chmax(dp[j], dp[j - t] + c);
    }

    cout << dp[v];
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}