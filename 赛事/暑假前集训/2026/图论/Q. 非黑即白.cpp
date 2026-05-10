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
    vector<pii> edges;
    vector<int> co(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> co[i];
    
    for(int i = 1;i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    DSU ds(n);
    for (int i = 0; i < n - 1;i++)
    {
        auto &[u, v] = edges[i];
        if(co[u] == co[v])
            ds.merge(u, v);
    }

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1;i++)
    {
        auto &[u, v] = edges[i];
        int fu = ds.find(u);
        int fv = ds.find(v);

        if(fu != fv)
        {
            adj[fu].push_back(fv);
            adj[fv].push_back(fu);
        }
    }

    int r = ds.f[1];

    auto bfs = [&](int s) -> array<int, 2>
    {
        deque<int> q;
        q.push_back(s);
        vector<int> dis(n + 1, -1);
        int maxx = 0;
        int idx = s;
        dis[s] = 0;
        while(!q.empty())
        {
            int u = q.front();
            q.pop_front();

            for(int v : adj[u])
            {
                if(dis[v] == -1)
                {
                    dis[v] = dis[u] + 1;
                    if(dis[v] > maxx)
                    {
                        maxx = dis[v];
                        idx = v;
                    }
                    q.push_back(v);
                }
            }
        }

        return {maxx, idx};
    };

    auto [maxx, idx] = bfs(r);
    auto [tmp, idx2] = bfs(idx);

    cout << (tmp + 1) / 2;
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