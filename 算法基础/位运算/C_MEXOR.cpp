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

void solve()
{
    int n, k;
    cin >> n >> k;

    k = k ^ n;
    // if(n == 1)
    // {
    //     if(k == 1)
    //         cout << "YES\n0\n";
    //     else
    //         cout << "NO\n";
    //     return;
    // }

    i64 up = 1;
    while(up < k)
        up <<= 1;

    if(up > k)
        up >>= 1;

    i64 up2 = 1;
    while(up2 < n - 1)
        up2 <<= 1;

    if(up2 > n - 1)
        up2 >>= 1;
    if(up > up2)
    {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    vector<int> ans;
    vector<int> vis(n, 0);
    for (int i = 0; i < 32;i++)
    {
        if((1 << i) & k)
            ans.push_back((1 << i)), vis[(1 << i)] = 1;
    }

    for (int i = 1; i <= n - 1;i++)
        if(!vis[i])
            cout << i << " ";

    cout << 0 << " ";

    for(int k : ans)
        cout << k << " ";
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