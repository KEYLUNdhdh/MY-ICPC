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

typedef pair<int, int> pii;
struct EBCC
{
    int n;
    vector<vector<pii>> adj;
    vector<int> dfn, low, stk;
    int dfncnt, ebccnt, bridgecnt;
    vector<vector<int>> ebc;
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
            while(1)
            {
                int x = stk.back();
                stk.pop_back();
                comp.push_back(x);
                if(x == u)
                    break;
            }
            ebc.push_back(comp);
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

    for (int i = 1; i <= m;i++)
    {
        int u, v;
        cin >> u >> v;
        ebcc.addEdge(u, v, i);
    }

    ebcc.work();

    cout << ebcc.ebccnt << "\n";
    for(auto vec : ebcc.ebc)
    {
        cout << vec.size() << " ";
        for(int k : vec)
            cout << k << " ";
        cout << "\n";
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