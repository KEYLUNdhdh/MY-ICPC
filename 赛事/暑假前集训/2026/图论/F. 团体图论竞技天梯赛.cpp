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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

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
constexpr i64 MOD = 998244353;
const i64 INF = 2e18;

struct Dinic
{
    struct Edge
    {
        int to;
        i64 cap;
        i64 flow;
        int rev;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> ptr;

    Dinic () {}
    Dinic(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<Edge>());
        level.resize(n + 1);
        ptr.resize(n + 1);
    }

    void addEdge(int from, int to , i64 cap)
    {
        adj[from].push_back({to, cap, 0, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, (int)adj[from].size() - 1});
    }

    bool bfs(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for(auto &[to, cap, flow, rev] : adj[u])
            {
                if(cap - flow > 0 && level[to] == -1)
                {
                    level[to] = level[u] + 1;
                    q.push(to);
                }
            }
        }

        return level[t] != -1;
    }

    i64 dfs(int v, int t, i64 pushed)
    {
        if(pushed == 0)
            return 0;
        if(v == t)
            return pushed;

        for (int &cid = ptr[v]; cid < adj[v].size(); cid++)
        {
            auto &[to, cap, flow, rev] = adj[v][cid];
            int tr = to;

            if(level[v] + 1 != level[tr] || cap - flow == 0)
                continue;

            i64 push = dfs(tr, t, min(pushed, cap - flow));
            if(push == 0)
                continue;

            flow += push;
            adj[tr][rev].flow -= push;
            return push;
        }
        return 0;
    }

    i64 maxFlow(int s, int t)
    {
        i64 flow = 0;
        while(bfs(s, t))
        {
            fill(ptr.begin(), ptr.end(), 0);

            while(i64 pushed = dfs(s, t, INF))
                flow += pushed;
        }
        return flow;
    }
};

struct BoundedCirculation
{
    int n;
    int S, T;

    Dinic dinic;
    vector<i64> delta;
    i64 sumLower;

    BoundedCirculation(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        S = 0;
        T = n + 1;

        dinic.init(T);
        delta.assign(n + 2, 0);
        sumLower = 0;
    }

    void addEdge(int u, int v, i64 l, i64 r)
    {
        dinic.addEdge(u, v, r - l); 
        delta[v] += l;              
        delta[u] -= l;
    }

    bool sol()
    {
        for (int i = 1; i <= n; i++)
        {
            if(delta[i] > 0)
            {
                dinic.addEdge(S, i, delta[i]);
                sumLower += delta[i];
            }
            else if (delta[i] < 0)
            {
                dinic.addEdge(i, T, -delta[i]);
            }
        }

        return dinic.maxFlow(S, T) == sumLower;
    }
};

void solve()
{
    int n, p, q;
    cin >> n >> p >> q;

    int m = 2 * n;
    vector<i64> df(m + 2, 0), dg(m + 2, 0);

    vector<pii> norm;

    for (int i = 1; i <= n;i++)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 1)
        {
            df[l]++;
            df[r + 1]--;
        }
        else
        {
            dg[l]++;
            dg[r + 1]--;
            norm.push_back({l, r});
        }
    }

    vector<int> f(m + 2, 0), g(m + 2, 0);

    BoundedCirculation bc(m + 1);
    for (int t = 1; t <= m;t++)
    {
        f[t] = f[t - 1] + df[t];
        g[t] = g[t - 1] + dg[t];

        i64 l = max<i64>(0, g[t] - q);
        i64 r = p - f[t];
        if (l > r)
        {
            cout << "No\n";
            return;
        }
        else
            bc.addEdge(t, t + 1, l, r);
    }

    for(auto &[l ,r] : norm)
        bc.addEdge(r + 1, l, 0, 1);

    if(bc.sol())
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