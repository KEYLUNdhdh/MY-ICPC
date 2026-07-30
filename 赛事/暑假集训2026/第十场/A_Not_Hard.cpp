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
// bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

const int MAXN = (1 << (22));
// 妈的今天怎么这么难
// 三小时两题有感觉吗
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);

    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
    }

    vector<int> dp(MAXN + 1, -1);
    for (int i = 1; i <= n;i++)
        dp[a[i]] = a[i];

    i64 mask = MAXN - 1;
    for (int k = 0; k <= 22;k++)
    {
        for (int j = 0; j <= mask;j++)
        {
            if(dp[j] == -1)
            {
                if(j & (1 << k))
                    dp[j] = dp[j ^ (1 << k)];
            }
        }
    }

    // for (int i = 1; i <= 100;i++)
    // {
    //     cerr << dp[i] << " ";
    // }

    for (int i = 1; i <= n; i++)
    {
        i64 rev = mask ^ a[i];
        cout << dp[rev] << " ";
    }
}

// bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}