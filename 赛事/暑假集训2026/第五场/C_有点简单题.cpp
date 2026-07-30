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

constexpr i64 P = 998244353;
struct SegmentTree
{
    int n;
    vector<i64> mulTag, addTag, sum, eTag, maxx, minn, hasE;
    SegmentTree(int n_) : n{n_}, mulTag(4 * n + 1, 1), addTag(4 * n + 1, 0), sum(4 * n + 1), eTag(4 * n + 1, 0), maxx(4 * n + 1, -INF), minn(4 * n + 1, INF), hasE(4 * n + 1, 0) {}

    void init(int p, int l, int r, const vector<i64> &a)
    {   
        if(l == r)
        {
            sum[p] = a[l];
            maxx[p] = a[l];
            minn[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        init(p << 1, l, m, a);
        init(p << 1 | 1, m + 1, r, a);
        pull(p);
    }

    void pull(int p)
    {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        maxx[p] = max(maxx[p << 1], maxx[p << 1 | 1]);
        minn[p] = min(minn[p << 1], minn[p << 1 | 1]);
    }

    void mul(int p,i64 v)
    {
        mulTag[p] = 1ll * mulTag[p] * v;
        addTag[p] = 1ll * addTag[p] * v;
        sum[p] = 1ll * sum[p] * v;
        i64 premax = maxx[p];
        i64 premin = minn[p];
        if(v < 0)
        {
            
            maxx[p] = premin * v;
            minn[p] = premax * v;
        }
        else
        {
            maxx[p] = premax * v;
            minn[p] = premin * v;
        }
    }
    void push(int p,int l,int r)
    {
        if(hasE[p])
        {
            int m = l + r >> 1;
            applyE(p << 1, l, m, eTag[p]);
            applyE(p << 1 | 1, m + 1, r, eTag[p]);
            hasE[p] = 0;
        }
        if(mulTag[p] != 1)
        {
            mul(2 * p, mulTag[p]);
            mul(2 * p + 1,mulTag[p]);
            mulTag[p] = 1;
        }
        if(addTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applyAdd(2 * p, l, m, addTag[p]);
            applyAdd(2 * p + 1, m + 1, r, addTag[p]);
            addTag[p] = 0;
        }
    }
    i64 rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sum[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    i64 rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }
    void rangeMul(int p,int l,int r,int x,int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
            return mul(p, v);
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeMul(2 * p, l, m, x, y, v);
        rangeMul(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeMul(int x,int y,i64 v)
    {
        rangeMul(1, 1, n, x, y, v);
    }
    void applyAdd(int p,int l,int r,i64 v)
    {
        addTag[p] = addTag[p] + v;
        sum[p] = sum[p] + 1ll * (r - l + 1) * v;
        maxx[p] += v;
        minn[p] += v;
    }
    void rangeAdd(int p,int l,int r,int x,int y,i64 v)
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
    void rangeAdd(int x,int y,i64 v)
    {
        rangeAdd(1, 1, n, x, y, v);
    }

    void applyE(int p, int l, int r, i64 v)
    {
        sum[p] = (r - l + 1) * v;
        maxx[p] = v;
        minn[p] = v;
        addTag[p] = 0;
        mulTag[p] = 1;
        eTag[p] = v;
        hasE[p] = 1;
    }
    void rangeE(int p, int l, int r, int x, int y, i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyE(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeE(2 * p, l, m, x, y, v);
        rangeE(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeE(int x, int y, i64 v)
    {
        rangeE(1, 1, n, x, y, v);
    }
    i64 rangeQueryMax(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return -INF;
        if(l >= x && r <= y)
            return maxx[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return max(rangeQueryMax(2 * p, l, m, x, y),  rangeQueryMax(2 * p + 1, m + 1, r, x, y));
    }
    i64 rangeQueryMax(int x,int y)
    {
        return rangeQueryMax(1, 1, n, x, y);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    string s, f;
    cin >> s >> f;

    s = "*" + s, f = "*" + f;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        a[i] = (f[i] - '0');

    SegmentTree seg(n);
    seg.init(1, 1, n, a);
    vector<pii> query(q);

    for (int i = 0; i < q;i++)
        cin >> query[i].first >> query[i].second;
    reverse(query.begin(), query.end());

    for(auto &[l, r] : query)
    {
        int len = r - l + 1;
        int cnt1 = seg.rangeQuery(l, r), cnt0 = len - cnt1;
        int ub = len / 2;

        if(cnt1 == cnt0)
        {
            cout << "NO\n";
            return;
        }

        if(cnt1 < cnt0)
            seg.rangeE(l, r, 0);
        else
            seg.rangeE(l, r, 1);
    }

    string t = "";
    for (int i = 1; i <= n;i++)
        t += (seg.rangeQuery(i, i) + '0');
    t = "*" + t;
    // debug(t)
    // debug(s)
    // cutline
    if(t == s)
        cout << "YES\n";
    else
        cout << "NO\n";
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
    // cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    // cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}