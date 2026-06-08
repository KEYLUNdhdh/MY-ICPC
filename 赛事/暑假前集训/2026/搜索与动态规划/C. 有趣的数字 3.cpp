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
constexpr i64 MOD = 2520, INF = 1e9;

void solve()
{
    i64 l, r;
    cin >> l >> r;

    auto sol = [&](i64 n) -> i64
    {
        vector<int> dig;
        i64 tmp = n;
        while(tmp)
        {
            dig.push_back(tmp % 10);
            tmp /= 10;
        }
        
        vector<int> lcmIdx(2521, 0);
        int idx = 0;
        for (int i = 1; i <= 2520; i++) 
        {
            if (2520 % i == 0) 
                lcmIdx[i] = idx++;
        }
        vector<vector<vector<i64>>> memo(dig.size(), vector<vector<i64>>(48, vector<i64>(MOD + 1, -1)));
        auto dfs = [&](auto self, int pos, int rem, int curlcm, int lim, int num) -> i64
        {
            if(pos < 0)
                return (num && rem % curlcm == 0) ? 1 : 0;

            if(!lim && num && memo[pos][lcmIdx[curlcm]][rem] != -1)
                return memo[pos][lcmIdx[curlcm]][rem];

            i64 res = 0;
            int up = lim ? dig[pos] : 9;

            for (int i = 0; i <= up;i++)
            {
                if(!num && i == 0)
                {
                    res += self(self, pos - 1, 0, 1, lim && (i == up), false);
                }
                else if(i != 0)
                {
                    int nxtrem = (rem * 10 + i) % MOD;
                    int nxtlcm = curlcm * i / gcd(curlcm, i);
                    res += self(self, pos - 1, nxtrem, nxtlcm, lim && (i == up), true);
                }

            }

            if(!lim && num) 
                memo[pos][lcmIdx[curlcm]][rem] = res;

            return res;
        };
        return dfs(dfs, dig.size() - 1, 0, 1, 1, 0);
    };
 
    cout << sol(r) - sol(l - 1);
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