#include <bits/stdc++.h>
#define lyc_fan_club main
#ifndef ONLINE_JUDGE
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x) {       \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(x)
#define debugarr(x)
#define cutline
#endif
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

void solve()
{
    int  n;
    debug(n);
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
#ifndef ONLINE_JUDGE
    cerr << "\n----------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}