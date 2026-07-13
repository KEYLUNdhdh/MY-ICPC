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
    string n;
    cin >> n;
    reverse(n.begin(), n.end());
    vector<vector<vector<vector<i64>>>> memo(n.size(), vector<vector<vector<i64>>>(3, vector<vector<i64>>(2, vector<i64>(1024, -1))));
    auto dfs = [&](auto self, int pos, int rem3, int has3, int mask, int lim, int num) -> i64
    {
        if(pos < 0)
        {
            if(!num)
                return 0;
            int c1 = (rem3 == 0) ? 1 : 0;
            int c2 = has3 ? 1 : 0;
            int c3 = (__builtin_popcount(mask) == 3) ? 1 : 0;

            return (c1 + c2 + c3 == 1) ? 1 : 0;
        }

        if(!lim && num && memo[pos][rem3][has3][mask] != -1)
            return memo[pos][rem3][has3][mask];

        i64 res = 0;
        int up = lim ? (n[pos] - '0') : 9;
        for (int i = 0; i <= up;i++)
        {
            if(!num && i == 0)
                res = (res + self(self, pos - 1, 0, 0, 0, lim && (i == up), false)) % MOD;
            else
            {
                int nxtrem3 = (rem3 + i) % 3;
                int nxthas3 = has3 | (i == 3);
                int nxtmask = mask | (1 << i);

                res = (res + self(self, pos - 1, nxtrem3, nxthas3, nxtmask, lim && (i == up), true)) % MOD;
            }
        }

        if(!lim && num)
            memo[pos][rem3][has3][mask] = res;

        return res;
    };

    i64 ans = dfs(dfs, n.size() - 1, 0, 0, 0, true, false);
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