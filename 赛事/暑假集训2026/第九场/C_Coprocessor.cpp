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
// bool ST;
// 妈的读题读错了
// e0 main e1 co
constexpr i64 MOD = 998244353, INF = 1e9;
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> e(n, 0);
    for (int i = 0; i < n;i++)
        cin >> e[i];

    vector<vector<int>> adj(n);
    vector<int> ind(n, 0), oud(n, 0);
    for (int i = 1; i <= m;i++)
    {
        int t1, t2;
        cin >> t1 >> t2;

        adj[t2].push_back(t1);
        ind[t1]++;
        oud[t2]++;
    }


    queue<int> q;
    vector<i64> dp(n, 0);
    for (int i = 0; i < n;i++)
    {
        if(ind[i] == 0)
        {
            q.push(i);
        }
    }


    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        
        for(int v : adj[u])
        {
            ind[v]--;
            if(ind[v] == 0)
                q.push(v);
            if(e[u] == 0 && e[v] == 1)
                chmax(dp[v], dp[u] + 1);
            else    
                chmax(dp[v], dp[u]);
        }
    }
    debugarr(dp)
    i64 ans = 0;
    for (int i = 0; i < n;i++)
    {
        if(oud[i] == 0)
        {
            chmax(ans, dp[i]);
        }
    }
    cout << ans;
}

// bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}