#include <bits/stdc++.h>
#define lyc_fan_club main
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
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) // PII 
{
    return os << "(" << p.first << ", " << p.second << ")\n";
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) //vector
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &d) //deque
{
    os << "[";
    for (int i = 0; i < d.size(); ++i)
    {
        if (i)
            os << ", ";
        os << d[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v) //set
{
    os << "[";
    for (auto x = v.begin(); x != v.end(); x++)
    {
        if (x != v.begin())
            os << ", ";
        os << *x;
    }
    return os << "]\n";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &v) //map
{
    os << " {";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << "(" << it->first << " -> " << it->second << ")"; //键值对
    }
    return os << "}\n";
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
constexpr int MOD = 998244353, INF = 1e9;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    vector<int> dep(n + 1, 0);
    vector<vector<int>> fa(n + 1, vector<int>(32, 0));

    for (int i = 0; i < n - 1;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto self, int u, int pa) -> void
    {
        dep[u] = dep[pa] + 1;
        fa[u][0] = pa;
        for (int i = 1; i <= 30;i++)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for(int v : adj[u])
        {
            if(v != pa)
                self(self, v, u);
        }
        return;
    };

    dep[0] = 0;
    dfs(dfs, 1, 0);

    auto lca = [&](int u, int v) -> void
    {
        int oriu = u, oriv = v;
        if(dep[u] < dep[v])
            swap(u, v);
        for (int i = 30; i >= 0;i--)
        {
            if(dep[fa[u][i]] >= dep[v])
                u = fa[u][i];
        }
        int pa = -1;
        if(u == v)
            pa = u;
        else
        {
            for (int i = 30; i >= 0;i--)
            {
                if(fa[u][i] != fa[v][i])
                {
                    u = fa[u][i];
                    v = fa[v][i];
                }
            }
            pa = fa[u][0];
        }
        int cntr = dep[oriv] - dep[pa];
        int cntl = dep[oriu] - dep[pa];
        int cnt = cntr + cntl + 1;
        int node1 = -1, node2 = -1;
        if(cnt % 2 == 1)
        {
            int m = (cnt + 1) / 2;
            if(m <= cntl)
            {
                int up = m - 1;
                node1 = oriu;
                for (int i = 0;i < 31;i++)
                {
                    if(up & (1 << i))
                    {
                        node1 = fa[node1][i];
                    }
                }
                cout << node1 << "\n";
            }
            else if(m == cntl + 1)
                cout << pa << "\n";
            else
            {
                int up = cnt - m;
                node1 = oriv;
                for (int i = 0;i < 31;i++)
                {
                    if(up & (1 << i))
                    {
                        node1 = fa[node1][i];
                    }
                }
                cout << node1 << "\n";
            }
        }
        else
        {
            int m = cnt / 2;
            if(m <= cntl)
            {
                int up = m - 1;
                node1 = oriu;
                for (int i = 0;i < 31;i++)
                {
                    if(up & (1 << i))
                    {
                        node1 = fa[node1][i];
                    }
                }
            }
            else if(m == cntl + 1)
                node1 = pa;
            else
            {
                int up = cnt - m;
                node1 = oriv;
                for (int i = 0;i < 31;i++)
                {
                    if(up & (1 << i))
                    {
                        node1 = fa[node1][i];
                    }
                }
            }
            
            m += 1;
            if(m <= cntl)
            {
                int up = m - 1;
                node2 = oriu;
                for (int i = 0;i < 31;i++)
                {
                    if(up & (1 << i))
                    {
                        node2 = fa[node2][i];
                    }
                }
            }
            else if(m == cntl + 1)
                node2 = pa;
            else
            {
                int up = cnt - m;
                node2 = oriv;
                for (int i = 0;i < 31;i++)
                {
                    if(up & (1 << i))
                    {
                        node2 = fa[node2][i];
                    }
                }
            }
            if(node1 > node2)
                swap(node1, node2);
            cout << node1 << " " << node2 << "\n";
        }
    };
    while(q--)
    {
        int l, r;
        cin >> l >> r;
        lca(l, r);
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