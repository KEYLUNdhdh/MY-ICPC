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

struct MCFGraph
{
    struct Edge
    {
        int to;
        i64 cap;
        i64 flow;
        i64 cost;
        int rev;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<i64> h;
    vector<i64> dist;
    vector<int> prevV;
    vector<int> prevE;

    MCFGraph() {}
    MCFGraph(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<Edge>());
        h.assign(n + 1, 0);
        dist.resize(n + 1, 0);
        prevV.resize(n + 1);
        prevE.resize(n + 1);
    }

    void addEdge(int from, int to, i64 cap, i64 cost)
    {
        adj[from].push_back({to, cap, 0, cost, (int)adj[to].size()});
        adj[to].push_back({from, 0, 0, -cost, (int)adj[from].size() - 1});
    }

    pll work(int s, int t)
    {
        i64 maxFlow = 0;
        i64 minCost = 0;

        while(1)
        {
            priority_queue<pll, vector<pll>, greater<pll>> pq;

            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            pq.push({0, s});

            while(!pq.empty())
            {
                auto [d, u] = pq.top();
                pq.pop();

                if(dist[u] < d)
                    continue;

                for (int i = 0; i < adj[u].size(); i++)
                {
                    auto &[to, cap, flow, cost, rev] = adj[u][i];
                    if(cap - flow > 0)
                    {
                        i64 reducedCost = cost + h[u] - h[to];

                        if(dist[to] > dist[u] + reducedCost)
                        {
                            dist[to] = dist[u] + reducedCost;
                            prevV[to] = u;
                            prevE[to] = i;
                            pq.push({dist[to], to});
                        }
                    }
                }
            }

            if(dist[t] == INF)
                break;

            for (int i = 1; i <= n;i++)
            {
                if(dist[i] != INF)
                    h[i] += dist[i];
            }

            i64 push = 2e18;
            for (int v = t; v != s; v = prevV[v])
            {
                int u = prevV[v];
                int idx = prevE[v];
                push = min(push, adj[u][idx].cap - adj[u][idx].flow);
            }

            maxFlow += push;
            minCost += push * h[t];

            for (int v = t; v != s; v=  prevV[v])
            {
                int u = prevV[v];
                int idx = prevE[v];
                int rev = adj[u][idx].rev;

                adj[u][idx].flow += push;
                adj[v][rev].flow -= push;
            }
        }
        return {maxFlow, minCost};
    }
};

void solve()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MCFGraph mcfg(n);

    for (int i = 0; i < m;i++)
    {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        mcfg.addEdge(u, v, w, c);
    }

    auto [maxflow, mincost] = mcfg.work(s, t);

    cout << maxflow << " " << mincost;
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