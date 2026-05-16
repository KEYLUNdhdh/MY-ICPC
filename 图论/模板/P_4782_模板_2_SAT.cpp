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

    SCC() {}
    SCC(int n_)
    {
        init(n_);
    }
    //1 - index
    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, 0);
        low.resize(n + 1);
        bel.assign(n + 1, 0);
        stk.clear();
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
        for (int i = 1;i <= n;i++)
        {
            if(!dfn[i])
                dfs(i);
        }
        return bel;
    }
};

struct TwoSAT
{
    int n;
    SCC scc;
    vector<int> ans;

    TwoSAT() {}
    TwoSAT(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        scc.init(2 * n);
        ans.assign(n + 1, 0);
    }

    int getNode(int u, bool state)
    {
        return u + state * n;
    }

    void addClause(int u, bool fu, int v, bool fv)
    {
        scc.addEdge(getNode(u, !fu), getNode(v, fv));
        scc.addEdge(getNode(v, !fv), getNode(u, fu));
    }

    bool sol()
    {
        scc.work();

        for (int i = 1; i <= n;i++)
        {
            if(scc.bel[getNode(i, false)] == scc.bel[getNode(i, true)])
                return false;

            ans[i] = scc.bel[getNode(i, true)] < scc.bel[getNode(i, false)];
        }
        return true;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    TwoSAT ttt(n);

    for (int k = 0; k < m;k++)
    {
        int i, a, j, b;
        cin >> i >> a >> j >> b;
        ttt.addClause(i, a, j, b);
    }

    int f = ttt.sol();
    if(!f)
        cout << "IMPOSSIBLE";
    else
    {
        cout << "POSSIBLE\n";
        for (int i = 1; i <= n;i++)
            cout << ttt.ans[i] << " ";
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