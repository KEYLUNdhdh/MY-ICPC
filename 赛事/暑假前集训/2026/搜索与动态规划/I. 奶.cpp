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
    int n;
    cin >> n;
    vector<i64> a(n + 1, 0);
    for (int i = 2; i <= n;i++)
        cin >> a[i];

    vector<array<i64, 2>> memo(n + 1, {0, 0});
    vector<array<int, 2>> vis(n + 1, {0, 0});

    auto dfs = [&](auto self, int cur, int t) -> i64
    {   
        if(cur == 1)
            return -1;

        if(vis[cur][t] == 1)
            return -1;
        else if(vis[cur][t] == 2)
            return memo[cur][t];

        vis[cur][t] = 1;
        i64 nxt = cur;
        if(t == 0)
            nxt += a[cur];
        else
            nxt -= a[cur];

        i64 res = 0;
        if(nxt <= 0 || nxt > n)
            res = a[cur];
        else
        {
            i64 nx = self(self, nxt, t ^ 1);
            if(nx == -1)
                res = -1;
            else
                res = a[cur] + nx;
        }

        vis[cur][t] = 2;
        memo[cur][t] = res;

        return res;
    };

    for (int i = 2; i <= n;i++)
    {
        if(memo[i][0] == 0)
            dfs(dfs, i, 0);
        if(memo[i][1] == 0)
            dfs(dfs, i, 1);
    }
    for (int i = 1; i < n; i++)
    {
        if(memo[i + 1][1] == -1)
            cout << -1 << "\n";
        else
            cout << i + memo[i + 1][1] << "\n";
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