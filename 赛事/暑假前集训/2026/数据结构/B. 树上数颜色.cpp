#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------\n";}
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

struct DSUonTree
{
    int n;
    vector<vector<int>> adj;
    vector<int> color;
    vector<int> sz, son;

    vector<int> cnt;
    int maxcnt;
    i64 sumcolor;
    vector<i64> ans;
    int skip;

    DSUonTree(int n_, const vector<int> &c) : n(n_), color(c)
    {
        adj.resize(n + 1);
        sz.resize(n + 1, 0);
        son.resize(n + 1, 0);

        cnt.resize(n + 1, 0);
        ans.resize(n + 1, 0);
        maxcnt = 0;
        sumcolor = 0;
        skip = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfsSz(int u, int p)
    {
        sz[u] = 1;
        int maxsub = 0;
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            dfsSz(v, u);
            sz[u] += sz[v];
            if(sz[v] > maxsub)
            {
                maxsub = sz[v];
                son[u] = v;
            }
        }
    }

    void add(int u, int p, int val)
    {
        int c = color[u];
        cnt[c] += val;

        if(val == 1)
        {
            if(cnt[c] > maxcnt)
            {
                maxcnt = cnt[c];
                sumcolor = c;
            }
            else if(cnt[c] == maxcnt)
            {
                sumcolor += c;
            }
        }

        for(int v : adj[u])
        {
            if(v == p || v == skip)
                continue;
            add(v, u, val);
        }
    }

    void dfsDSU(int u, int p, bool keep)
    {
        for(int v : adj[u])
        {
            if(v == p || v == son[u])
                continue;
            dfsDSU(v, u, false);
        }

        if(son[u])
        {
            dfsDSU(son[u], u, true);
            skip = son[u];
        }

        add(u, p, 1);
        skip = 0;

        ans[u] = sumcolor;

        if(!keep)
        {
            add(u, p, -1);
            maxcnt = 0;
            sumcolor = 0;
        }
    }

    vector<i64> run(int root = 1)
    {
        dfsSz(root, 0);
        dfsDSU(root, 0, true);
        return ans;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<int> c(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> c[i];
    DSUonTree ds(n, c);
    for (int i = 1; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        ds.addEdge(u, v);
    }

    vector<i64> res = ds.run();
    for (int i = 1;i <= n;i++)
        cout << res[i] << " ";

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