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
constexpr i64 MOD = 998244353, INF = 2e18;
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

struct BoundedMaxFlow
{
    int n, s, t;
    int S, T;

    Dinic dinic;
    vector<i64> delta;
    i64 sumLower;

    BoundedMaxFlow(int n_, int s_, int t_)
    {
        init(n_, s_, t_);
    }

    void init(int n_, int s_, int t_)
    {
        n = n_;
        s = s_;
        t = t_;
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

    i64 sol()
    {
        for (int i = 1; i <= n;i++)
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

        dinic.addEdge(t, s, INF);

        int tsIdx = dinic.adj[t].size() - 1;

        i64 flow1 = dinic.maxFlow(S, T);

        if(flow1 != sumLower)
            return -1;

        i64 baseFlow = dinic.adj[t][tsIdx].flow;

        dinic.adj[t][tsIdx].cap = 0;
        dinic.adj[t][tsIdx].flow = 0;
        int stIdx = dinic.adj[t][tsIdx].rev;
        dinic.adj[s][stIdx].cap = 0;
        dinic.adj[s][stIdx].flow = 0;

        i64 extraFlow = dinic.maxFlow(s, t);

        return baseFlow + extraFlow;
    }
};
void solve()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    BoundedMaxFlow bmf(n, s, t);

    for (int i = 0; i < m;i++)
    {
        int u, v, l, r;
        cin >> u >> v >> l >> r;

        bmf.addEdge(u, v, l, r);
    }

    i64 ans = bmf.sol();
    if(ans != -1)
        cout << ans;
    else
        cout << "N";
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