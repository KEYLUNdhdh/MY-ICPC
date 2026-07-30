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

constexpr i64 MOD = 1e9 + 7, INF = 2e18;

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n + 2, 0);
    for (int i = 1;i <= n;i++)
        cin >> a[i];
    a[0] = -INF;
    a[n + 1] = INF;
    i64 ans = 0;
    for (int i = 1; i <= n;i++)
    {
        for (int j = i + 1;j <= n;j++)
        {
            int lb = 2 * a[i] - a[j];
            int pre = lower_bound(a.begin(), a.end(), lb) - a.begin();
            int ub = 2 * a[j] - a[i];
            int nxt = lower_bound(a.begin(), a.end(), ub) - a.begin() - 1;
            ans = (ans + qpow(2, pre - 1 + n - nxt)) % MOD;
        }
    }

    cout << ans;
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
    // cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    // cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}