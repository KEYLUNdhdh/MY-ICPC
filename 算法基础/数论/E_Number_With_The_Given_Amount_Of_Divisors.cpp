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
//反素数满足一个最小性质
vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
void solve()
{
    int n;
    cin >> n;

    i64 ans = INF;
    auto dfs = [&](auto self, int idx, i64 cur, int cnt, int precnt) -> void
    {
        if(idx >= 15 || cur >= ans || cnt > n)
            return;

        if(cnt == n)
        {
            chmin(ans, cur);
            return;
        }

        for (int i = 1; i <= precnt;i++)
        {
            if(cur * p[idx] >= ans)
                return;
            cur *= p[idx];
            self(self, idx + 1, cur, cnt * (i + 1), i);
        }
    };

    dfs(dfs, 0, 1, 1, INF);
    cout << ans;
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