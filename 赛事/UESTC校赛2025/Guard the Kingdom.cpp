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
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n;i++)
    {
        int v;
        cin >> v;
        adj[i].push_back(v);
        adj[v].push_back(i);
    }
    vector<int> t(m);
    for (int i = 0; i < m;i++)
        cin >> t[i];
    vector<int> c(k);
    for (int i = 0; i < k;i++)
        cin >> c[i];
    vector<int> d(n + 1, -1);
    queue<int> q;
    for(int cc : c)
    {
        d[cc] = 0;
        q.push(cc);
    }
    int maxd = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        maxd = max(maxd, d[u]);
        for(int v : adj[u])
        {
            if(d[v] == -1)
            {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    vector<vector<int>> node(maxd + 1);
    for (int i = 1; i <= n;i++)
        node[d[i]].push_back(i);
    vector<int> rc(n + 1, 0);
    for(int cc : c)
        rc[cc] = 1;
    for (int dd = 1; dd <= maxd;dd++)
    {
        for(int u : node[dd])
        {
            for(int v : adj[u])
            {
                if(d[v] == dd - 1)
                    rc[u] += rc[v];
            }
        }
    }
    vector<int> tr(n + 1, 0);
    for(int r : t)
        tr[r] = 1;
    for (int dd = maxd; dd >= 1;dd--)
    {
        for(int u : node[dd])
        {
            if(tr[u] > 0)
            {
                for (int v : adj[u])
                {
                    if(d[v] == dd - 1)
                        tr[v] += tr[u];
                }
            }
        }
    }
    for (int i = 0; i < m;i++)
        cout << rc[t[i]] << " ";
    cout << "\n";
    for(int i = 0; i < k; i++)
        cout<< tr[c[i]] << " ";
    cout << "\n";
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