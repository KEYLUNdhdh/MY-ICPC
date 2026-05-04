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
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct VirtualTree
{
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, dep;
    vector<vector<int>> st;
    int timer;

    vector<vector<int>> vtadj;
    vector<int> vtnodes;

    VirtualTree(int n_) : n(n_)
    {
        adj.resize(n + 1);
        vtadj.resize(n + 1);
        dfn.resize(n + 1, 0);
        dep.resize(n + 1, 0);
        st.assign(20, vector<int>(n + 1, 0));
        timer = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p, int d)
    {
        dfn[u] = ++timer;
        dep[u] = d;
        st[0][u] = p;
        for (int i = 1; i < 20;i++)
            st[i][u] = st[i - 1][st[i - 1][u]];
        for(int v : adj[u])
        {
            if(v != p)
                dfs(v, u, d + 1);
        }
    }

    void init(int root = 1)
    {
        dfs(root, 0, 1);
    }

    int getLCA(int u, int v)
    {
        if(dep[u] < dep[v])
            swap(u, v);
        for (int i = 19; i >= 0; i--)
        {
            if(dep[st[i][u]] >= dep[v])
                u = st[i][u];
        }

        if(u == v)
            return u;

        for (int i = 19; i >= 0;i--)
        {
            if(st[i][u] != st[i][v])
            {
                u = st[i][u];
                v = st[i][v];
            }
        }
        return st[0][u];
    }

    int build(vector<int> nodes)
    {
        if(nodes.empty())
            return 0;
        sort(nodes.begin(), nodes.end(), [&](int u, int v)
             { return dfn[u] < dfn[v]; });

        int k = nodes.size();
        for (int i = 0; i < k - 1;i++)
            nodes.push_back(getLCA(nodes[i], nodes[i + 1]));

        sort(nodes.begin(), nodes.end(), [&](int u, int v)
             { return dfn[u] < dfn[v]; });

        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        vtnodes = nodes;

        for (int i = 1; i < nodes.size();i++)
        {
            int p = getLCA(nodes[i - 1], nodes[i]);
            vtadj[p].push_back(nodes[i]);
        }

        return nodes[0];
    }

    void clear()
    {
        for(int u : vtnodes)
            vtadj[u].clear();
        vtnodes.clear();
    }
};
void solve()
{
    int n;
    cin >> n;
    VirtualTree vt(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        vt.addEdge(u, v);
    }

    vt.init();
    int q;
    cin >> q;
    vector<int> iscore(n + 1, 0);

    while(q--)
    {
        int k;
        cin >> k;
        vector<int> nodes(k);
        for (int i = 0; i < k;i++)
        {
            cin >> nodes[i];
            iscore[nodes[i]] = 1;
        }

        bool ok = true;
        for(int u : nodes)
        {
            if(iscore[vt.st[0][u]])
            {
                ok = false;
                break;
            }
        }

        if(!ok)
        {
            cout << -1 << "\n";
            for(int u : nodes)
                iscore[u] = 0;
            continue;
        }

        int root = vt.build(nodes);
        int ans = 0;

        auto dfs = [&](auto self, int u) -> int
        {
            int cntchild = 0;
            for(int v : vt.vtadj[u])
            {
                cntchild += self(self, v);
            }

            if(iscore[u])
            {
                ans += cntchild;
                return 1;
            }
            else
            {
                if(cntchild > 1)
                {
                    ans += 1;
                    return 0;
                }
                else if(cntchild == 1)
                    return 1;
                else
                    return 0;
            }
        };
        dfs(dfs, root);
        cout << ans << "\n";
        vt.clear();
        for (int u : nodes)
            iscore[u] = 0;
    }
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