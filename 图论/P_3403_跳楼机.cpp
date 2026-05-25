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

void solve()
{
    i64 h, x, y, z;
    cin >> h >> x >> y >> z;

    vector<vector<pll>> adj(x);
    for (int i = 0; i < x;i++)
    {
        adj[i].push_back({y, (i + y) % x});
        adj[i].push_back({z, (i + z) % x});
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    vector<i64> ans(x, INF);

    ans[0] = 0;
    pq.push({0, 0});
    while(!pq.empty())
    {
        auto [dis, u] = pq.top();
        pq.pop();

        if(dis > ans[u])
            continue;

        for(auto &[w, v] : adj[u])
        {
            if(ans[u] + w < ans[v])
            {
                ans[v] = ans[u] + w;
                pq.push({ans[v], v});
            }
        }
    }

    i64 res = 0;
    for (int i = 0; i < x;i++)
    {
        if(ans[i] <= h - 1)
            res += (h - 1 - ans[i]) / x + 1;
    }

    cout << res;
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