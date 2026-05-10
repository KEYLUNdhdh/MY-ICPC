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
mt19937 rnd(time(0));

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
    int n, x;
    cin >> n >> x;
    vector<int> a(n, 0);
    for (int i = 0; i < n;i++)
        cin >> a[i];
    vector<vector<pll>> adj(n * 2);

    for (int i = n; i < (n * 2);i++)
    {
        adj[i].push_back({1, (i + 1) % n + n});
        adj[i].push_back({0, i - n});
    }
    for (int i = 0; i < n;i++)
    {
        adj[i].push_back({1, (i + a[i]) % n + n});
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, 0});

    vector<i64> ans(n * 2, INF);
    ans[0] = 0;
    while(!pq.empty())
    {
        auto [dis, u] = pq.top();
        pq.pop();

        if(dis > ans[u])
            continue;

        ans[u] = dis;
        for(auto &[w, v] : adj[u])
        {
            if(ans[u] + w < ans[v])
            {
                ans[v] = ans[u] + w;
                pq.push({ans[v], v});
            }
        }
    }

    cout << ans[x];
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