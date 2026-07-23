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

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    vector<int> deg(n + 1, 0);
    vector<int> vis(n + 1, 0);
    i64 minn = 0, maxx = 0;
    DSU dsu(n);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        dsu.merge(i, a[i]);
        deg[i]++, deg[a[i]]++;
    }

    int cntline = 0;
    int circle = 0;
    for (int i = 1; i <= n;i++)
    {
        if(deg[i] == 1)
        {
            int fa = dsu.find(i);
            if(!vis[fa])
                cntline++, vis[fa] = 1;
        }
    }

    for (int i = 1; i <= n;i++)
    {
        if (deg[i] == 2)
        {
            int fa = dsu.find(i);
            if(!vis[fa] && dsu.siz[fa] > 2)
                circle++, vis[fa] = 1;
            else if(!vis[fa])
                cntline++, vis[fa] = 1;
        }
    }
    if(cntline)
        minn = circle + 1, maxx = circle + cntline;
    else
        minn = maxx = circle;
    // maxx = circle + cntline;
    cout << minn << " " << max(maxx, minn) << "\n";
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