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
constexpr i64 MOD = 998244353, INF = 2e18;
void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n, 0);
    map<int, int> mp;
    i64 cnt = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        mp[a[i]]++;
    }
    i64 mex = 0;
    vector<i64> dp(n + 1, INF);
    for (int i = 0; i <= n;i++)
    {
        if(mp[i] == 0)
        {
            dp[i] = 0;
            mex = i;
            break;
        }
    }
    for (int i = mex - 1; i >= 0;i--)
    {
        for (int j = i + 1; j <= mex;j++)
        {
            i64 cost = 1ll * j * (mp[i] - 1) + i;
            chmin(dp[i], dp[j] + cost);
        }
    }

    cout << dp[0] << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}