#include <bits/stdc++.h>
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
constexpr int MOD = 998244353, INF = 1e9;

struct SCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;
    SCC() {}
    SCC(int n_)
    {
        init(n_);
    }
    //0 - index
    void init(int n_)
    {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void dfs(int x)
    {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for(auto y : adj[x])
        {
            if(dfn[y] == -1)
            {
                dfs(y);
                low[x] = min(low[x], low[y]);
            }
            else if(bel[y] == -1)
            {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if(dfn[x] == low[x])
        {
            int y;
            do{
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }

    vector<int> work()
    {
        for (int i = 0;i < n;i++)
        {
            if(dfn[i] == -1)
                dfs(i);
        }
        return bel;
    }
};

void solve()
{
    int n, m, s;
    cin >> n >> m >> s;
    s--;

    SCC scc(n);
    vector<pii> edges;

    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        scc.addEdge(u, v);
        edges.push_back({u, v});
    }

    scc.work();

    vector<int> ind(scc.cnt, 0);
    for(auto &[u, v] : edges)
    {
        int uu = scc.bel[u];
        int vv = scc.bel[v];

        if(uu != vv)    
            ind[vv]++;
    }

    i64 ans = 0;
    int ss = scc.bel[s];

    for (int i = 0; i < scc.cnt;i++)
    {
        if(ind[i] == 0 && i != ss)
            ans++;
    }

    cout << ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}