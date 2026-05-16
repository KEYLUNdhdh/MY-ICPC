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

struct SCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;

    vector<int> num;
    vector<int> vnum;
    SCC() {}
    SCC(int n_, vector<int> num_)
    {
        init(n_, num_);
    }
    //1 - index
    void init(int n_, vector<int> num_)
    {
        n = n_;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.resize(n + 1);
        bel.assign(n + 1, 0);
        stk.clear();
        num = num_;
        vnum.push_back(-INF);
        cur = cnt = 1;
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
            if(!dfn[y])
            {
                dfs(y);
                low[x] = min(low[x], low[y]);
            }
            else if(!bel[y])
            {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if(dfn[x] == low[x])
        {
            int y;
            int sum = 0;
            do{
                y = stk.back();
                sum += num[y];
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            vnum.push_back(sum);
            cnt++;
        }
    }

    vector<int> work()
    {
        for (int i = 1;i <= n;i++)
        {
            if(!dfn[i])
                dfs(i);
        }
        return bel;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> num(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> num[i];

    SCC scc(n, num);
    vector<pii> edges;
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        scc.addEdge(u, v);
    }

    scc.work();

    vector<vector<int>> vadj(scc.cnt + 1);
    vector<int> ind(scc.cnt + 1, 0);
    for (int i = 0; i < m;i++)
    {
        auto &[u, v] = edges[i];
        if(scc.bel[u] != scc.bel[v])
        {
            vadj[scc.bel[u]].push_back(scc.bel[v]);
            ind[scc.bel[v]]++;
        }
    }

    deque<pii> q;
    int maxx = 0;
    for (int i = 1; i < scc.cnt;i++)
    {
        if(ind[i] == 0)
        {
            q.push_back({scc.vnum[i], i});
            chmax(maxx, scc.vnum[i]);
        }
    }

    
    while(!q.empty())
    {
        auto [sum, u] = q.front();
        q.pop_front();

        for(int v : vadj[u])
        {
            ind[v]--;
            if(ind[v] == 0)
            {
                q.push_back({sum + scc.vnum[v], v});
                chmax(maxx, sum + scc.vnum[v]);
            }
        }   
    }
    cout << maxx;
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