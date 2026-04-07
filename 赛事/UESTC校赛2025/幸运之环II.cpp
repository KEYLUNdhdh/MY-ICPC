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
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> ind(n + 1, 0);
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ind[v]++;
        ind[u]++;
    }
    deque<int> d;
    for (int i = 1; i <= n;i++)
    {
        if(ind[i] == 1)
            d.push_back(i), vis[i] = 1;
    } 
    while(!d.empty())
    {
        int u = d.front();
        d.pop_front();
        for(int v : adj[u])
        {
            ind[v]--;
            if(ind[v] == 1)
            {
                vis[v] = 1;
                d.push_back(v);
            }
        }
    }
    vector<int> res;
    int s = -1;
    for (int i = 1; i <= n;i++)
    {
        if(!vis[i])
        {
            s = i;
            break;
        }
    }
    int cur = s;
    while(1)
    {
        res.push_back(cur);
        vis[cur] = 1;
        int f = 0;
        for(int v : adj[cur])
        {
            if(!vis[v])
            {
                f = 1;
                cur = v;
                break;
            }
        }
        if(!f)
            break;
    }
    int minn = INF;
    int pos = -1;
    for (int i = 0; i < res.size(); i++)
    {
        if (res[i] < minn)
        {
            minn = res[i];
            pos = i;
        }
    }

    int len = res.size();
    int idxl = (pos - 1 + len) % len; 
    int idxr = (pos + 1) % len;

    cout << len << " ";
    if (res[idxr] < res[idxl])
    {
        for (int i = 0; i < len; i++)
            cout << res[(pos + i) % len] << " ";
    }
    else
    {
        for (int i = 0; i < len; i++)
            cout << res[(pos - i + len) % len] << " ";
    }
    cout << "\n";
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