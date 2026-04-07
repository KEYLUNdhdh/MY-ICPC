#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
const int MOD = 998244353;

struct DSU
{
    vector<int> f, siz;
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
    bool merge(int x,int y,int d,int &res)
    {
        x = find(x);
        y = find(y);
        if(x == y)
            return false;
        if(siz[x] >= d)
            res--;
        if(siz[y] >= d)
            res--;
        if(siz[x] < siz[y])
            swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        if(siz[x] >= d)
            res++;
        return true;
    }
    int size(int x)
    {
        return siz[find(x)];
    }
};
void solve()
{
    int n, m, x, d;
    cin >> n >> m >> x >> d;
    struct city
    {
        int id, h;
    };
    DSU ds(n);
    vector<city> ci(n);
    for (int i = 0; i < n;i++)
        cin >> ci[i].h, ci[i].id = i + 1;
    sort(ci.begin(), ci.end(), [](city a, city b)
        { return a.h < b.h; });
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> up(x);
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < x;i++)
        cin >> up[i];
    vector<int> ans;
    int res = 0;
    reverse(up.begin(), up.end());
    for(auto height : up)
    {
        while(!ci.empty() && ci.back().h > height)
        {
            int u = ci.back().id;
            ci.pop_back();
            vis[u] = 1;
            if(ds.size(u) >= d)//特判d = 1
                res++;
            for(auto v : adj[u])
            {
                if(vis[v])
                {
                    ds.merge(u, v, d, res);
                }
            }
        }
        ans.push_back(res);
    }
    for (int i = ans.size() - 1;i  >= 0;i--)
        cout << ans[i] << "\n";
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