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
    i64 a, b, h, w, n;
    cin >> a >> b >> h >> w >> n;

    vector<i64> mul(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> mul[i];

    sort(mul.rbegin(), mul.rend());

    int up = min<int>(34, mul.size() - 1);
    i64 ans = INF;
    i64 lim = max(a, b);
    map<int, set<int>> mp;

    auto dfs1 = [&](auto self, i64 curh, i64 curw, int step) -> void
    {
        if(step >= ans || step > up)
            return;
        if((curh >= a && curw >= b) || (curw >= a && curh >= b))
        {
            ans = step;
            return;
        }
        if(mp[step].find(curh) != mp[step].end())
            return;

        mp[step].insert(curh);
        if(curh < lim)
            self(self, curh * mul[step], curw, step + 1);

        if(curh != curw && curw < lim)   
            self(self, curh, curw * mul[step], step + 1);
        return;
    };

    // auto dfs2 = [&](auto self, i64 curh, i64 curw, int step) -> void
    // {
    //     if(step >= ans || step > up)
    //         return;
    //     if(curh >= b && curw >= a)
    //     {
    //         ans = step;
    //         return;
    //     }
    //     if(curh < b)
    //         self(self, curh * mul[step], curw, step + 1);

    //     if(curw < a)
    //         self(self, curh, curw * mul[step], step + 1);
    //     return;
    // };

    dfs1(dfs1, h, w, 0);

    if(ans == INF)
        cout << -1;
    else
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