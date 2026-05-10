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

struct VBCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, low, isCut, stk;
    int dfncnt, vbccnt, cutcnt;
    vector<vector<int>> vbc;

    VBCC(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<int>());
        dfn.assign(n + 1, 0);
        low.resize(n + 1);
        isCut.assign(n + 1, 0);
        stk.clear();
        vbc.clear();
        dfncnt = vbccnt = cutcnt = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p = 0)
    {
        dfn[u] = low[u] = ++dfncnt;
        stk.push_back(u);
        int child = 0;

        if(p == 0 && adj[u].empty())
        {
            vbccnt++;
            stk.pop_back();
            vbc.push_back({u});
            return;
        }

        for(int v : adj[u])
        {
            if(!dfn[v])
            {
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);

                if(low[v] >= dfn[u])
                {
                    isCut[u] = 1;
                    vbccnt++;
                    vector<int> comp;
                    while(1)
                    {
                        int x = stk.back();
                        stk.pop_back();
                        comp.push_back(x);
                        if(x == v)
                            break;
                    }
                    comp.push_back(u);
                    vbc.push_back(comp);
                }
            }
            else if(v != p)
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(p == 0 && child < 2)
            isCut[u] = 0;
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
        for (int i = 1; i <= n;i++)
        {
            if(isCut[i])
                cutcnt++;
        }
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    VBCC vbcc(n);

    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        if(u != v)
            vbcc.addEdge(u, v);
    }

    vbcc.work();

    cout << vbcc.vbccnt << "\n";
    for(auto vec : vbcc.vbc)
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