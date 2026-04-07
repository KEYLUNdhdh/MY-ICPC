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
    int l, r, ck;
};
// 1 odd // 0 even
void solve()
{
    int n;
    int m;
    cin >> n >> m;
    vector<f> a(m);
    vector<int> uni;
    for (int i = 0; i < m;i++)
    {
        string s;
        cin >> a[i].l >> a[i].r >> s;
        uni.push_back(a[i].l - 1);
        uni.push_back(a[i].r);
        if(s == "even")
            a[i].ck = 0;
        else
            a[i].ck = 1;
    }
    sort(uni.begin(), uni.end());
    uni.erase(unique(uni.begin(), uni.end()), uni.end());
    auto g = [&](int k)
    {
        return lower_bound(uni.begin(), uni.end(), k) - uni.begin();
    };
    DSU ds(uni.size(), 2);
    for (int i = 0; i < m;i++)
    {
        auto &l = a[i].l;
        auto &r = a[i].r;
        auto ck = a[i].ck;
        l = g(l - 1);
        r = g(r);
        if(!ds.merge(l, r, ck))
        {
            cout << i;
            return;
        }
    }
    cout << m;
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