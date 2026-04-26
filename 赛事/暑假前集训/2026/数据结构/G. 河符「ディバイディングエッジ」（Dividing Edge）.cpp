#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------\n";}
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
constexpr int MOD = 998244353, INF = 1e9;
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
    int n, m;
    cin >> n >> m;
    vector<pii> edge(m + 1, {0, 0});
    for (int i = 1; i <= m;i++)
        cin >> edge[i].first >> edge[i].second;
    vector<vector<pii>> prefix(m + 1), suff(m + 1);
    DSU dsu(n);
    for (int i = 1; i <= m;i++)
    {
        prefix[i] = prefix[i - 1];
        int u = edge[i].first;
        int v = edge[i].second;
        if(dsu.merge(u, v))
        {
            prefix[i].push_back({u, v});
        }
    }
    int u = edge[m].first;
    int v = edge[m].second;
    DSU ds(n);
    if(ds.merge(u, v))
        suff[m].push_back({u, v});
    for (int i = m - 1; i >= 1;i--)
    {
        suff[i] = suff[i + 1];
        int u = edge[i].first;
        int v = edge[i].second;
        if(ds.merge(u, v))
        {
            suff[i].push_back({u, v});
        }
    }
    int k;
    cin >> k;
    while(k--)
    {
        int l, r;
        cin >> l >> r;
        DSU tmp(n);
        for(auto &[u, v] : prefix[l - 1])
        {
            tmp.merge(u, v);
        }

        if(r < m)
        {
            for(auto &[u, v] : suff[r + 1])
            {
                tmp.merge(u, v);
            }
        }

        cout << tmp.part << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}