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
    vector<int> f, siz, d;
    int mod;

    DSU(int n,int mod_) : f(n + 1), siz(n + 1, 1), d(n + 1, 0), mod(mod_)
    {
        iota(f.begin(), f.end(), 0);
    }
    int find(int x)
    {
        if (x != f[x])
        {
            int root = find(f[x]);
            d[x] = (d[x] + d[f[x]] + mod) % mod;
            f[x] = root;
        }
        return f[x];
    }
    bool merge(int x,int y,int v)
    {
        int rootx = find(x);
        int rooty = find(y);
        if(rootx == rooty)
        {
            int check = (d[x] - d[y] + mod) % mod;
            return check == v;
        }
        if(siz[rootx] < siz[rooty])
        {
            swap(rootx, rooty);
            v = (mod - v) % mod;
            swap(x, y);
        }
        f[rooty] = rootx;
        siz[rootx] += siz[rooty];
        d[rooty] = (d[x] - d[y] - v + mod) % mod;
        return true;
    }
    //求x -> y
    int query(int x,int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if(rootx != rooty)
            return -1;
        return (d[x] - d[y] + mod) % mod;
    }
};
struct f
{
    int u, v, w;
    bool operator>(const f& b) const
    {
        return w > b.w;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    DSU ds(n, 2);
    vector<f> vec;
    for (int i = 0; i < m;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        vec.push_back({u, v, w});
    }
    sort(vec.begin(), vec.end(),greater<f>());
    for(auto &k : vec)
    {
        if(!ds.merge(k.u, k.v, 1))
        {
            cout << k.w;
            return;
        }
    }
    cout << 0;
    return;
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