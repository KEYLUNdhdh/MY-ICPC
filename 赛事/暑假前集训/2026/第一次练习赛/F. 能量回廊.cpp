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

struct SegmentTree 
{
    int n;
    vector<i64> lmax, rmax, suml, sumr, lTag, rTag;

    SegmentTree(int n_) : n(n_), lmax(n << 2 | 1, 0), rmax(n << 2 | 1, 0), suml(n << 2 | 1, 0), sumr(n << 2 | 1, 0), lTag(n << 2 | 1, 0), rTag(n << 2 | 1, 0) {}

    void init(int p, int l, int r, const vector<i64> &lm, const vector<i64> &rm)
    {
        if(l == r)
        {
            lmax[p] = lm[l];
            rmax[p] = rm[l];
            suml[p] = lm[l];
            sumr[p] = rm[l];
            return;
        }

        int m = l + r >> 1;
        init(p << 1, l, m, lm, rm);
        init(p << 1 | 1, m + 1, r, lm, rm);
        pull(p);
        return;
    }
    void pull(int p)
    {
        suml[p] = suml[p << 1] + suml[p << 1 | 1];
        sumr[p] = sumr[p << 1] + sumr[p << 1 | 1];
        lmax[p] = max(lmax[p << 1], lmax[p << 1 | 1]);
        rmax[p] = max(rmax[p << 1], rmax[p << 1 | 1]);
    }

    void push(int p, int l, int r)
    {
        int m = l + r >> 1;
        if(lTag[p])
        {
            apllyL(p << 1, l, m, lTag[p]);
            apllyL(p << 1 | 1, m + 1, r, lTag[p]);
            lTag[p] = 0;
        }
        if(rTag[p])
        {
            apllyR(p << 1, l, m, rTag[p]);
            apllyR(p << 1 | 1, m + 1, r, rTag[p]);
            rTag[p] = 0;
        }
    }

    void apllyL(int p, int l, int r, i64 v)
    {
        suml[p] = (r - l + 1) * v;
        lmax[p] = v;
        lTag[p] = v;
    }

    void apllyR(int p, int l, int r, i64 v)
    {
        sumr[p] = (r - l + 1) * v;
        rmax[p] = v;
        rTag[p] = v;
    }
    void rangeL(int p, int l, int r, int x, int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            apllyL(p, l, r, v);
            return;
        }

        int m = l + r >> 1;
        push(p, l, r);
        rangeL(p << 1, l, m, x, y, v);
        rangeL(p << 1 | 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeL(int x, int y, i64 v)
    {
        rangeL(1, 1, n, x, y, v);
    }


    void rangeR(int p, int l, int r, int x, int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            apllyR(p, l, r, v);
            return;
        }

        int m = l + r >> 1;
        push(p, l, r);
        rangeR(p << 1, l, m, x, y, v);
        rangeR(p << 1 | 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeR(int x, int y, i64 v)
    {
        rangeR(1, 1, n, x, y, v);
    }

    int fL(int p, int l, int r, int x, i64 v)
    {
        if(r < x || lmax[p] < v)
            return n + 1;
        if(l == r)
            return l;
        
        push(p, l, r);
        int m = l + r >> 1;
        int res = fL(p << 1, l, m, x, v);
        if(res != n + 1)
            return res;
        return fL(p << 1 | 1, m + 1, r, x, v);
    }

    int fR(int p, int l, int r, int x, i64 v)
    {
        if(l > x || rmax[p] < v)
            return 0;
        if(l == r)
            return l;

        push(p, l, r);
        int m = l + r >> 1;
        int res = fR(p << 1 | 1, m + 1, r, x, v);
        if(res != 0)
            return res;
        return fR(p << 1, l, m, x, v);
    }

    void swL(int x, i64 v)
    {
        int pos = fL(1, 1, n, x, v);
        rangeL(x, pos - 1, v);
    }

    void swR(int x, i64 v)
    {
        int pos = fR(1, 1, n, x, v);
        rangeR(pos + 1, x, v);
    }
};
void solve()
{
    int n;
    cin >> n;
    i64 maxx = 0, sum = 0;
    vector<i64> h(n + 1, 0), rm(n + 1, 0), lm(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> h[i];
        chmax(maxx, h[i]);
        sum += h[i];
    }

    for (int i = 1; i <= n;i++)
        lm[i] = max(lm[i - 1], h[i]);

    rm[n] = h[n];
    for (int i = n - 1; i >= 1; i--)
        rm[i] = max(rm[i + 1], h[i]);

    SegmentTree sg(n);
    sg.init(1, 1, n, lm, rm);

    int q;
    cin >> q;
    while (q--)
    {
        int x;
        i64 v;
        cin >> x >> v;
        h[x] += v;
        sum += v;
        chmax(maxx, h[x]);
        sg.swL(x, h[x]);
        sg.swR(x, h[x]);
        i64 ans = -sum - n * maxx + sg.suml[1] + sg.sumr[1];
        cout << ans << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}