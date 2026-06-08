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
constexpr i64 MOD = 998244353, INF = 2e18;

vector<int> p = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
void solve()
{
    i64 l, r;
    cin >> l >> r;

    i64 ans = INF;
    i64 anscnt = 0;
    auto dfs = [&](auto self, int idx, i64 cur, i64 cnt, int precnt)
    {
        if(idx >= 11 || cur > r)
            return;

        if(cur >= l && cur <= r)
        {
            if(anscnt < cnt)
            {
                anscnt = cnt;
                ans = cur;
            }
            else if(anscnt == cnt && cur < ans)
                ans = cur;
        }
        for (int i = 1; i <= precnt;i++)
        {
            if(cur * p[idx] > r)
                return;
            cur *= p[idx];
            self(self, idx + 1, cur, cnt * (i + 1), i);
        }
    };

    dfs(dfs, 0, 1, 1, 100);
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