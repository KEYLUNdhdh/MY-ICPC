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
using u32 = unsigned int;
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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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
    //x -> y
    void pretoSuf(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        f[x] = y;
        siz[y] += siz[x];
        part--;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};

struct query
{
    int st, dest, e, id;
};

// 之前牛客遇到过，离线查询，倒着处理问题，用并查集维护连通性
// 看成是一个个岛屿冒出来
void solve()
{
    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    vector<i64> h(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> h[i];

    vector<int> seq(n + 1, 0);
    iota(seq.begin(), seq.end(), 0);
    sort(seq.begin() + 1, seq.end(), [&](int a, int b){ return h[a] < h[b];});
    // debugarr(seq)
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        if(h[u] >= h[v])
            adj[u].push_back(v);
        else
            adj[v].push_back(u);
    }
    // debugarr(seq)

    int q;
    cin >> q;
    vector<query> qr(q);
    vector<int> ans(q);
    for (int i = 0; i < q;i++)
        cin >> qr[i].st >> qr[i].dest >> qr[i].e, qr[i].id = i;

    sort(qr.begin(), qr.end(), [&](query a, query b){return h[a.st] + a.e < h[b.st] + b.e;});
    int idx = 1;
    // debugarr(seq)

    for (int i = 0; i < q;i++)
    {
        auto &[st, dest, e, id] = qr[i];
        i64 lim = h[st] + e;
        while(idx <= n && h[seq[idx]] <= lim)
        {
            int u = seq[idx++];
            for(int v : adj[u])
                dsu.merge(u, v);    
        }

        if(dsu.same(st, dest))
            ans[id] = 1;
        else
            ans[id] = 0;
    }

    // debugarr(seq)

    for (int i = 0; i < q;i++)
        if(ans[i])
            cout << "YES\n";
        else
            cout << "NO\n";
    cout << "\n";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}