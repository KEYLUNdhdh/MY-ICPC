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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> pa(n + 1, -1);
    vector<int> dep(n + 1, 0);
    pa[1] = 0;
    dep[1] = 1;
    auto dfs = [&](auto self, int u,int p) -> void
    {
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            pa[v] = u;
            dep[v] = dep[u] + 1;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    vector<int> vis(n + 1, 0);
    int f = 1;
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        if(f)
        {
            int cnt = 0;
            if(dep[u] < dep[v])
                swap(u, v);
            while(dep[u] != dep[v])
            {
                if(vis[u])
                    cnt++;
                else
                    vis[u] = 1;
                if(cnt > 1)
                    f = 0;
                u = pa[u];
            }
            while(u != v)
            {
                if(vis[v])
                    cnt++;
                else
                    vis[v] = 1;
                if(vis[u])
                    cnt++;
                else
                    vis[u] = 1;
                if(cnt > 1)
                    f = 0;
                u = pa[u], v = pa[v];
            }
            if(vis[u])
                    cnt++;
            else
                vis[u] = 1;
            if(cnt > 1)
                f = 0;
        }
    }
    if(f)
        cout << "Yes\n";
    else
        cout << "No\n";
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