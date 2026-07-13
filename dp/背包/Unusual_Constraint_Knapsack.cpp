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
    i64 n, W;
    cin >> n >> W;

    vector<i64> w(n + 1, 0), v(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> w[i] >> v[i];

    vector<i64> prev = v;
    i64 ans = 0;
    for (int i = 1; i <= n;i++)
        prev[i] = prev[i - 1] + prev[i];

    debugarr(prev)
    i64 tmp = 0;
    for (int i = n; i >= 1;i--)
    {
        if(W >= w[i])
        {
            chmax(ans, tmp + prev[i - 1]);// 更新一下不选的情况。

            //下面继续尝试选第 i 个的情况。
            W -= w[i];
            tmp += v[i];
        }
    }

    chmax(ans, tmp);
    cout << ans << "\n";
    cutline
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