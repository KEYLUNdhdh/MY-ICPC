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
constexpr i64 MOD = 998244353, INF = 1e9;
int P = 998244353;
struct SegmentTree
{
    int n;
    vector<i64> addTag, sum, maxx;
    SegmentTree(int n_) : n{n_}, addTag(4 * n + 1, 0), sum(4 * n + 1), maxx(4 * n + 1, 0) {}

    void build(int p, int l, int r, const vector<i64> &a)
    {
        if(l == r)
        {
            sum[p] = a[l];
            maxx[p] = a[l];
            return;
        }

        int m = l + r >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        pull(p);
    }
    void pull(int p)
    {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        maxx[p] = max(maxx[p << 1], maxx[p << 1 | 1]);
    }
    void push(int p,int l,int r)
    {
        if(addTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applyAdd(p << 1, l, m, addTag[p]);
            applyAdd(p << 1 | 1, m + 1, r, addTag[p]);
            addTag[p] = 0;
        }
    }

    int rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sum[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return (rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y));
    }

    int rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }

    void applyAdd(int p,int l,int r,i64 v)
    {
        addTag[p] = (1ll * addTag[p] + 1ll * v);
        sum[p] = (1ll * sum[p] + 1ll * (r - l + 1) * v);
        maxx[p] += v;
    }

    void rangeAdd(int p,int l,int r,int x,int y,int v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyAdd(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeAdd(int x,int y,int v)
    {
        rangeAdd(1, 1, n, x, y, v);
    }

    void modify(int p, int l, int r)
    {
        if(l == r)
        {
            i64 del = sum[p] / 2;
            sum[p] -= del;
            maxx[p] -= del;
            return;
        }

        push(p, l, r);
        int m = l + r >> 1;
        i64 lhs = maxx[p << 1], rhs = maxx[p << 1 | 1];
        if(lhs >= rhs)
            modify(p << 1, l, m);
        else
            modify(p << 1 | 1, m + 1, r);
        pull(p);
    }
};

void solve()
{
    int n;
    cin >> n;

    vector<i64> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    for (int i = 1; i <= n;i++)
        cin >> b[i];
    SegmentTree seg(n);
    seg.build(1, 1, n, a);
    for (int i = 1; i <= n;i++)
    {
        i64 add = b[i];
        seg.rangeAdd(1, n, add);
        seg.modify(1, 1, n);
    }

    cout << seg.sum[1];
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