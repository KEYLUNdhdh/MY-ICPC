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
constexpr i64 MOD = 998244353, INF = 1e9;

// minus 1 is the beishu of k, 
// k | (sum of 1) && k <= n
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    int f = 1;
    vector<int> cnt(32, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        if(a[i] != 0)
            f = 0;
        for (int k = 0;k <= 30;k++)
        {
            if((1ll << k) & a[i])
                cnt[k]++;
        }
    }
    if(f)
    {
        for (int i = 1; i <= n;i++)
            cout << i << " ";
        cout << "\n";
    }
    int g = -1;
    for (int i = 0; i <= 30;i++)
    {
        if(cnt[i] != 0 && g == -1)
            g = cnt[i];
        else if(cnt[i] != 0)
        {
            g = gcd(g, cnt[i]);
        }
    }

    for (int i = 1; i <= g;i++)
        if(g % i == 0)
            cout << i << " ";
    cout << "\n";
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