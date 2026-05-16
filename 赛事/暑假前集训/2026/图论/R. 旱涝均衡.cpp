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

struct EBCC
{
    int n;
    vector<vector<pii>> adj;
    vector<int> dfn, low, stk;
    int dfncnt, ebccnt, bridgecnt;
    vector<vector<int>> ebc;
    vector<i64> bel, a;
    vector<i64> sum;
    EBCC(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<pii>());
        dfn.assign(n + 1, 0);
        low.resize(n + 1, 0);
        a.resize(n + 1, 0);
        bel.resize(n + 1, 0);
        sum.clear();
        sum.push_back(-INF);
        stk.clear();
        ebc.clear();
        dfncnt = ebccnt = bridgecnt = 0;
    }
    
    void addEdge(int u, int v, int id)
    {
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
    }

    void dfs(int u, int inEdge = 0)
    {
        dfn[u] = low[u] = ++dfncnt;
        stk.push_back(u);

        for(auto &[v, id] : adj[u])
        {
            if(!dfn[v])
            {
                dfs(v, id);
                low[u] = min(low[u], low[v]);

                if(low[v] > dfn[u])
                    bridgecnt++;
            }
            else if(id != inEdge)
            {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if(low[u] == dfn[u])
        {
            ebccnt++;
            vector<int> comp;
            i64 tmp = 0;
            while(1)
            {
                int x = stk.back();
                stk.pop_back();
                bel[x] = ebccnt;
                tmp += a[x];
                comp.push_back(x);
                if(x == u)
                    break;
            }
            ebc.push_back(comp);
            sum.push_back(tmp);
        }
    }

    void work()
    {
        for (int i = 1; i <= n;i++)
        {
            if(!dfn[i])
            {
                stk.clear();
                dfs(i);
            }
        }
    }
};


void solve()
{
    int n, m;
    cin >> n >> m;
    EBCC ebcc(n);
    for (int i = 1; i <= n;i++)
        cin >> ebcc.a[i];
    vector<array<i64, 3>> edges;
    for (int i = 1; i <= m;i++)
    {
        i64 u, v, c;
        cin >> u >> v >> c;
        ebcc.addEdge(u, v, i);
        edges.push_back({u, v, c});
    }

    ebcc.work();
    vector<vector<pll>> adj(ebcc.ebccnt + 1);
    for (int i = 0;i < m;i++)
    {
        auto &[u, v, c] = edges[i];
        int uu = ebcc.bel[u];
        int vv = ebcc.bel[v];
        if(uu != vv)
        {
            adj[uu].emplace_back(vv, c);
            adj[vv].emplace_back(uu, c);
        }
    }

    int s = ebcc.bel[1];
    int f = 1;
    auto dfs = [&](auto self, int u, int p) -> i64
    {
        if(f == 0)
            return -1;
        i64 costu = ebcc.sum[u];
        for(auto &[v, c] : adj[u])
        {
            if(v != p)
            {
                i64 cost = self(self, v, u);
                if(f == 0)
                    return -1;
                if(abs(cost) > c)
                {
                    f = 0;
                    return -1;
                }
                else
                    costu += cost;
            }
        }
        return costu;
    };

    dfs(dfs, s, 0);
    if(f == 0)
        cout << "NO\n";
    else
        cout << "YES\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}