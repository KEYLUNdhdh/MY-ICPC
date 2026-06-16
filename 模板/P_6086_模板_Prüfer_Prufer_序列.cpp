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
struct Prufer
{
    static vector<int> treeToPrufer(int n, const vector<pii> &edges)
    {
        vector<int> pruferSeq;
        if(n <= 2)
            return pruferSeq;

        vector<int> degree(n + 1, 0);
        vector<int> xorSum(n + 1, 0);

        for(const auto &[u, v] : edges)
        {
            degree[u]++;
            degree[v]++;
            xorSum[u] ^= v;
            xorSum[v] ^= u;
        }

        int ptr = 1;
        while(ptr <= n && degree[ptr] != 1)
            ptr++;

        int leaf = ptr;

        for (int i = 0; i < n - 2;i++)
        {
            int neighbor = xorSum[leaf];
            pruferSeq.push_back(neighbor);

            degree[leaf]--;
            degree[neighbor]--;
            xorSum[neighbor] ^= leaf;

            if(degree[neighbor] == 1 && neighbor < ptr)
                leaf = neighbor;
            else
            {
                ptr++;
                while(ptr <= n && degree[ptr] != 1)
                    ptr++;
                leaf = ptr;
            }
        }
        return pruferSeq;
    }

    static vector<pii> pruferToTree(int n, const vector<int> &pruferSeq)
    {
        vector<pii> edges;
        if(n == 2)
        {
            edges.push_back({1, 2});
            return edges;
        }

        vector<int> degree(n + 1, 1);
        for(int node : pruferSeq)
            degree[node]++;

        int ptr = 1;
        while(ptr <= n && degree[ptr] != 1)
            ptr++;

        int leaf = ptr;
        for(int node : pruferSeq)
        {
            edges.push_back({leaf, node});
            degree[leaf]--;
            degree[node]--;

            if(degree[node] == 1 && node < ptr)
                leaf = node;
            else
            {
                ptr++;
                while(ptr <= n && degree[ptr] != 1)
                    ptr++;
                leaf = ptr;
            }
        }

        int u = -1, v = -1;
        for (int i = 1; i <= n;i++)
        {
            if(degree[i] == 1)
            {
                if(u == -1)
                    u = i;
                else
                    v = i;
            }
        }

        if(u != -1 && v != -1)
            edges.push_back({u, v});

        return edges;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    if(m == 1)
    {
        vector<pii> edges;
        for (int i = 1; i < n;i++)
        {
            int v;
            cin >> v;
            edges.push_back({i, v});
        }

        auto prufer = Prufer::treeToPrufer(n, edges);
        i64 ans = 0;
        for (i64 i = 0; i < prufer.size();i++)
            ans ^= ((i + 1) * prufer[i]);

        cout << ans;
    }
    else
    {
        vector<int> pa(n + 1, 0);
        vector<int> prufer(n - 2);
        for (int i = 0; i < n - 2;i++)
            cin >> prufer[i];

        auto edges = Prufer::pruferToTree(n, prufer);
        vector<vector<int>> adj(n + 1);
        for(auto &[u, v] : edges)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        auto dfs = [&](auto self, int u, int p) -> void
        {
            pa[u] = p;
            for(int v : adj[u])
            {
                if(v == p)
                    continue;

                self(self, v, u);
            }
        };

        dfs(dfs, n, 0);
        i64 ans = 0;
        for (i64 i = 1; i < n;i++)
            ans ^= i * pa[i];

        cout << ans;
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