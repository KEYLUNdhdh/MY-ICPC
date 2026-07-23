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

// https://codeforces.com/gym/705722
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
        f[x] = y;
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
        part--;
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

    DSU dsu(n + 1);

    vector<int> a(n + 2, 0), b(m);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    for (int i = 0; i < m;i++)
        cin >> b[i];

    for (int i = n; i >= 1;i--)
    {
        if(a[i] == 1)
            dsu.merge(i, i + 1);
    }

    for (int i = 0; i < m; i++)
    {
        int ans = 0;
        int cur = b[i];
        while(cur <= n)
        {
            if(a[cur] > 1)
            {
                a[cur]--;
                if(a[cur] == 1)
                    dsu.merge(cur, cur + 1);
                cur = cur + a[cur] + 1;
                ans++;
                if(cur > n)
                {
                    cout << ans << "\n";
                    break;
                }
            }
            else
            {
                int nxt = dsu.find(cur);
                ans += nxt - cur;
                cur = nxt;
                if(cur > n)
                {
                    cout << ans << "\n";
                    break;
                }
            }
        }
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