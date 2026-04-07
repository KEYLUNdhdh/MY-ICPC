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
struct DSU
{
    vector<int> f, siz;
    int part;
    DSU() {};
    DSU(int n)
    {
        init(n);
    }
    //input n,open n + 1
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        part = n;
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x,int y)
    {
        return find(x) == find(y);
    }
    bool merge(int x,int y)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        part--;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> init(n + 1, vector<int>(n + 1, 0));
    vector<bitset<8005>> p(n + 1), q(n + 1);
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= n;j++)
        {
            char c;
            cin >> c;
            init[i][j] = c - '0';
            if(init[i][j])
            {
                p[i][j] = 1;
                q[j][i] = 1;
            }
        }
    vector<pii> e;
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= n;j++)
        {
            if(i != j && init[i][j] && (p[i] & q[j]).count() == 2)
                e.push_back({i, j});
        }
    if(e.size() != n - 1)
    {
        cout << "No\n";
        return;
    }
    DSU d(n);
    for(auto &[x, y] : e)
        d.merge(x, y);
    if(d.part != 1)
    {
        cout << "No\n";
        return;
    }
    vector<vector<int>> adj(n + 1);
    for(auto &[x, y] : e)
        adj[x].push_back(y);
    for (int i = 1; i <= n;i++)
    {
        bitset<8005> ac;
        queue<int> q;
        q.push(i);
        ac.set(i);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int v : adj[u])
            {
                if(!ac[v])
                {
                    ac[v] = 1;
                    q.push(v);
                }
            }
        }
        if(ac != p[i])
        {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    for(auto &[x, y] : e)
        cout << x << " " << y << "\n";
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