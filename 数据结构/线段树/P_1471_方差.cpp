#include <bits/stdc++.h>
#define lyc_fan_club main
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
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) // PII 
{
    return os << "(" << p.first << ", " << p.second << ")\n";
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) //vector
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &d) //deque
{
    os << "[";
    for (int i = 0; i < d.size(); ++i)
    {
        if (i)
            os << ", ";
        os << d[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v) //set
{
    os << "[";
    for (auto x = v.begin(); x != v.end(); x++)
    {
        if (x != v.begin())
            os << ", ";
        os << *x;
    }
    return os << "]\n";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &v) //map
{
    os << " {";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << "(" << it->first << " -> " << it->second << ")"; //键值对
    }
    return os << "}\n";
}

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
constexpr int MOD = 998244353, INF = 1e9;
struct SegmentTree
{
    int n;
    vector<db> addTag, sum, sumpow;
    SegmentTree(int n_) : n{n_}, addTag(4 * n + 1, 0), sum(4 * n + 1), sumpow(4 * n + 1, 0) {}
    void pull(int p, int l, int r)
    {
        sum[p] = (sum[p << 1] + sum[p << 1 | 1]);
        sumpow[p] = sumpow[p << 1] + sumpow[p << 1 | 1];
    }

    void init(int p,int l, int r, const vector<db> &a)
    {
        if(l == r)
        {
            sum[p] = a[l];
            sumpow[p] = a[l] * a[l];
            return;
        }
        int m = l + r >> 1;
        init(p << 1, l, m, a);
        init(p << 1 | 1, m + 1, r, a);
        pull(p, l, r);
        return;
    }
    void push(int p,int l,int r)
    {
        if(addTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applyAdd(2 * p, l, m, addTag[p]);
            applyAdd(2 * p + 1, m + 1, r, addTag[p]);
            addTag[p] = 0;
        }
    }
    db querysum(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sum[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return (querysum(2 * p, l, m, x, y) + querysum(2 * p + 1, m + 1, r, x, y));
    }
    db querysump(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sumpow[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return (querysump(2 * p, l, m, x, y) + querysump(2 * p + 1, m + 1, r, x, y));
    }
    db queryave(int x,int y)
    {
        db tmp = querysum(1, 1, n, x, y);
        int len = y - x + 1;
        return tmp / len;
    }

    db querys(int x, int y)
    {
        db sm = querysum(1, 1, n, x, y);
        db smp = querysump(1, 1, n, x, y);
        int len = y - x + 1;
        return (smp / len - (sm / len) * (sm / len));
    }
    void applyAdd(int p,int l,int r,db v)
    {
        addTag[p] += v;
        int len = r - l + 1;
        sumpow[p] += 2 * v * sum[p] + len * v * v;
        sum[p] += len * v;
        return;
    }
    void rangeAdd(int p,int l,int r,int x,int y,db v)
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
        pull(p, l, r);
    }
    void rangeAdd(int x,int y,db v)
    {
        rangeAdd(1, 1, n, x, y, v);
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<db> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    SegmentTree sg(n);
    sg.init(1, 1, n, a);
    while(m--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            int x, y;
            db k;
            cin >> x >> y >> k;
            sg.rangeAdd(x, y, k);
        }
        else if(op == 2)
        {
            int x, y;
            cin >> x >> y;
            cout << fixed << setprecision(4) << sg.queryave(x, y) << "\n";
        }
        else
        {
            int x, y;
            cin >> x >> y;
            cout << fixed << setprecision(4) << sg.querys(x, y) << "\n";
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