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
struct DSU
{
    vector<int> f, siz;
    vector<pii> his;
    int part;
    DSU() {}
    DSU(int n)
    {
        init(n);
    }
    void init(int n)
    {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        his.clear();
        part = n;
    }
    int find(int x)
    {
        while(x != f[x])
            x = f[x];
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
        // if(siz[x] < siz[y])
        //     swap(x, y);
        his.push_back({y, x});
        siz[x] += siz[y];
        f[y] = x;
        part--;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
    void undo()
    {
        if(his.empty())
            return;
        auto [y, x] = his.back();
        his.pop_back();
        siz[x] -= siz[y];
        f[y] = y;
        part++;
    }
    int hissize()
    {
        return his.size();
    }
    void rollback(int tag)
    {
        while(his.size() > tag)
            undo();
    }
};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> p[i];

    DSU dsu(n);
    vector<pii> edges(m + 1);
    for (int i = 1; i <= m;i++)
        cin >> edges[i].first >> edges[i].second;

    vector<pii> query(q);
    vector<int> vis(m + 1, 0);
    for(int i = 0;i < q;i++)
    {
        cin >> query[i].first >> query[i].second;
        if(query[i].first == 2)
            vis[query[i].second] = 1;
    }

    for (int i = 1; i <= m;i++)
    if(!vis[i])
    {
        int u = edges[i].first, v = edges[i].second;
        if(p[u] > p[v])
            dsu.merge(u, v);
        else
            dsu.merge(v, u);
    }

    for (int i = q - 1; i >= 0;i--)
        if(query[i].first == 2) 
        {
            int k = query[i].second;
            int u = edges[k].first, v = edges[k].second;
            if(p[u] > p[v])
                dsu.merge(u, v);
            else
                dsu.merge(v, u);
        }

    for (int k = 0; k < q;k++)
    {
        auto &[op, idx] = query[k];
        if(op == 1)
        {

        }
    }
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
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}