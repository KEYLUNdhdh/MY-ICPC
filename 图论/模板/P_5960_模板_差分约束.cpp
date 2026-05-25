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
constexpr i64 MOD = 998244353, INF = 1e9;

struct DiffConstraint
{
    int n;

    vector<vector<pll>> adj;
    vector<i64> dist;
    vector<int> count;
    vector<int> inQueue;

    DiffConstraint(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<pll>());
        dist.assign(n + 1, 0);
        count.assign(n + 1, 0);
        inQueue.assign(n + 1, 0);
    }

    void addEdge(int u, int v, i64 w) 
    {
        adj[u].push_back({v, w});
    }

    bool sol()
    {
        queue<int> q;

        for (int i = 1; i <= n;i++)
        {
            dist[i] = 0;
            inQueue[i] = 1;
            count[i] = 1;
            q.push(i);
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            inQueue[u] = 0;

            for(const auto &[v, w] : adj[u])
            {
                if(dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;

                    if(!inQueue[v])
                    {
                        q.push(v);
                        inQueue[v] = 1;
                        count[v]++;

                        if(count[v] >= n)
                            return false;
                    }
                }
            }
        }
        return true;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    DiffConstraint diff(n);
    for (int i = 0; i < m;i++)
    {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        diff.addEdge(v, u, w);
    }

    if(diff.sol())
    {
        for (int i = 1; i <= n;i++)
            cout << diff.dist[i] << " ";
    }
    else
        cout << "NO";
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