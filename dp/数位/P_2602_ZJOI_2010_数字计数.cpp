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
constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    i64 a, b;
    cin >> a >> b;

    auto sol = [&](i64 n, int d) -> i64
    {
        vector<int> dig;
        i64 tmp = n;
        while(tmp > 0)
        {
            dig.push_back(tmp % 10);
            tmp /= 10;
        }

        vector<vector<i64>> memo(dig.size(), vector<i64>(dig.size() + 1, -1));

        auto dfs = [&](auto self, int pos, int cnt, bool lim, bool num) -> i64
        {
            if(pos < 0)
                return cnt; 

            if(!lim && num && memo[pos][cnt] != -1)
                return memo[pos][cnt];

            i64 res = 0;
            int up = lim ? dig[pos] : 9;
            for (int i = 0;i <= up;i++)
            {
                if(!num && i == 0)
                    res += self(self, pos - 1, cnt, lim && (i == up), false);
                else
                {
                    int nxt = cnt + (i == d ? 1 : 0);
                    res += self(self, pos - 1, nxt, lim && (i == up), true);
                }
            }

            if(!lim && num)
                memo[pos][cnt] = res;

            return res;
        };

        return dfs(dfs, dig.size() - 1, 0, true, false);
    };

    for (int i = 0; i <= 9;i++)
    {
        i64 ans = sol(b, i) - sol(a - 1, i);
        cout << ans << " ";
    }
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