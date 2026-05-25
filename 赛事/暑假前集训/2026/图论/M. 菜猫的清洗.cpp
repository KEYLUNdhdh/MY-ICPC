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
constexpr i64 MOD = 998244353, INF = 2e18;

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

    vector<i64> work(int s, int t)
    {
        i64 maxFlow = 0;
        i64 minCost = 0;
        vector<i64> ans;
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

            for (int i = 0; i <= n;i++)
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
            ans.push_back(push * h[t]);
            for (int v = t; v != s; v=  prevV[v])
            {
                int u = prevV[v];
                int idx = prevE[v];
                int rev = adj[u][idx].rev;

                adj[u][idx].flow += push;
                adj[v][rev].flow -= push;
            }
        }
        return ans;
    }
};

struct func
{
    i64 a, b, c;
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<func> f(n + 1);
    set<i64> st;
    for (int i = 1; i <= n;i++)
    {
        cin >> f[i].a >> f[i].b >> f[i].c;

        i64 mid = -(f[i].b) / (2 * f[i].a);
        if(mid < 1)
            mid = 1;
        else if(mid > m)
            mid = m;
        i64 l = max<i64>(mid - n, 1);
        i64 r = min<i64>(mid + n, m);

        for (int j = l; j <= r;j++)
            st.insert(j);
    }

    vector<i64> nl(st.begin(), st.end());

    int s = 0;
    int t = n + nl.size() + 1;

    MCFGraph mcfg(t);

    for (int i = 1; i <= n;i++)
        mcfg.addEdge(s, i, 1, 0);

    for (int i = 1; i <= nl.size();i++)
        mcfg.addEdge(n + i, t, 1, 0);

    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= nl.size();j++)
        {
            i64 id = nl[j - 1];
            i64 cost = f[i].a * id * id + f[i].b * id + f[i].c;
            mcfg.addEdge(i, n + j, 1, cost);
        }
    }

    vector<i64> ans = mcfg.work(s, t);

    for (int i = 0; i < ans.size();i++)
    {
        ans[i] = ans[i] + (i > 0 ? ans[i - 1] : 0);
        cout << ans[i] << " ";
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