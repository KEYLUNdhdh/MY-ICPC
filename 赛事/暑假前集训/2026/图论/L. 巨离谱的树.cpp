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
vector<map<i64, int>> mp(9);
void precom()
{

    vector<int> pruferSeq;
    vector<int> dis;
    vector<int> discnt;
    vector<pii> edges;
    vector<vector<int>> adj;    

    auto mapping = [&](const vector<int> cc, int n) -> i64
    {
        i64 res = 0;
        for (int i = 1; i < n;i++)
        {
            int x = cc[i];
            res = (res << 6) | x;
        }
        return res;
    };

    auto dfsdist = [&](auto self, int u, int p, int d) -> void
    {
        discnt[d]++;
        for(int v : adj[u])
        {
            if(v != p)
                self(self, v, u, d + 1);
        }
    };

    auto process = [&](vector<int> prufer, int n) -> void
    {
        edges = Prufer::pruferToTree(n, prufer);
        dis.assign(n + 1, 0);
        discnt.assign(n + 1, 0);
        adj.assign(n + 1, vector<int>());

        for(auto &[u, v] : edges)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 1; i <= n;i++)
            dfsdist(dfsdist, i, 0, 0);

        vector<int> cc(n, 0);
        for (int i = 1; i < n;i++)
            cc[i] = discnt[i] / 2;

        i64 res = mapping(cc, n);
        
        mp[n][res]++;
    };
    
    auto dfs = [&](auto self, int idx, int n) -> void
    {
        if(idx == n - 2)
        {
            process(pruferSeq, n);
            return;
        }
        for (int i = 1; i <= n;i++)
        {
            pruferSeq.push_back(i);
            self(self, idx + 1, n);
            pruferSeq.pop_back();
        }
    };

    for (int n = 2; n <= 8;n++)
    {
        pruferSeq.clear();
        dfs(dfs, 0, n);
    }

    
}

void solve()
{
    int n;
    cin >> n;
    vector<int> c(n, 0);
    for (int i = 1; i < n;i++)
        cin >> c[i];
    
    auto mapping = [&](const vector<int> cc, int n) -> i64
    {
        i64 res = 0;
        for (int i = 1; i < n;i++)
        {
            int x = cc[i];
            res = (res << 6) | x;
        }
        return res;
    };

    i64 res = mapping(c, n);
    if(mp[n].count(res))
        cout << mp[n][res] << "\n";
    else
        cout << 0 << "\n";
}
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    precom();
    while(T--)
        solve();

    return 0;
}