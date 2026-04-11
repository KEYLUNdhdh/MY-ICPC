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
constexpr i64 MOD = 998244353, INF = 2e18;
//很好的题目，考验我的手搓SegmentTree功底
//我觉得以后直接外部写一个applyAdd之类的，在rangeAdd时直接调用，这样更清晰也更爽
struct SegmentTree
{
    int n;
    vector<i64> addTag, eTag, maxx;
    vector<int> set;
    SegmentTree(int n_) : n(n_), addTag(4 * n_ + 1, 0), eTag(4 * n_ + 1, -1), maxx(4 * n_ + 1), set(4 * n_ + 1, 0) {}
    void init(int p, int l, int r, const vector<i64> &a)
    {
        if(l == r)
        {
            maxx[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        init(2 * p, l, m, a);
        init(2 * p + 1, m + 1, r, a);
        pull(p);
    }   

    void pull(int p)
    {
        maxx[p] = max(maxx[2 * p], maxx[2 * p + 1]);
    }
    void applySet(int p, i64 val)
    {
        eTag[p] = val;
        set[p] = 1;
        addTag[p] = 0;
        maxx[p] = val;
    }
    void applyAdd(int p, i64 val)
    {
        maxx[p] += val;
        if(set[p])
            eTag[p] += val;
        else
            addTag[p] += val;
    }
    void push(int p,int l, int r)
    {
        int lhs = 2 * p;
        int rhs = 2 * p + 1;
        if(set[p])
        {
            applySet(lhs, eTag[p]);
            applySet(rhs, eTag[p]);
            set[p] = 0;
        }
        else if(addTag[p] != 0)
        {
            applyAdd(lhs, addTag[p]);
            applyAdd(rhs, addTag[p]);
            addTag[p] = 0;
        }
    }

    void rangeE(int p, int l, int r, int x, int y, i64 val)
    {
        if(l > y || x > r)
            return;
        if(l >= x && r <= y)
        {
            applySet(p, val);
            return;
        }
        int m = l + r >> 1;
        push(p, l, r);
        rangeE(2 * p, l, m, x, y, val);
        rangeE(2 * p + 1, m + 1, r, x, y, val);
        pull(p);
    }

    void rangeE(int x, int y, i64 val)
    {
        rangeE(1, 1, n, x, y, val);
    }
    void rangeAdd(int p, int l, int r, int x, int y, i64 val)
    {
        if(l > y || x > r)
            return;
        if(l >= x && r <= y)
        {
            applyAdd(p, val);
            return;
        }
        int m = l + r >> 1;
        push(p, l, r);
        rangeAdd(2 * p, l, m, x, y, val);
        rangeAdd(2 * p + 1, m + 1, r, x, y, val);
        pull(p);
    }

    void rangeAdd(int x, int y, i64 val)
    {
        rangeAdd(1, 1, n, x, y, val);
    }
    i64 rangeQuery(int p, int l, int r, int x, int y)
    {
        if(l > y || x > r)
            return -INF;
        if(l >= x && r <= y)
        {
            return maxx[p];
        }
        int m = l + r >> 1;
        push(p, l, r);
        return (max(rangeQuery(2 * p, l, m, x, y),
                    rangeQuery(2 * p + 1, m + 1, r, x, y)));
    }

    i64 rangeQuery(int x, int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    SegmentTree sg(n);
    sg.init(1, 1, n, a);
    while(q--)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            i64 l, r, x;
            cin >> l >> r >> x;
            sg.rangeE(l, r, x);
        }
        else if(op == 2)
        {
            i64 l, r, x;
            cin >> l >> r >> x;
            sg.rangeAdd(l, r, x);
        }
        else
        {
            i64 l, r;
            cin >> l >> r;
            cout << sg.rangeQuery(l, r) << "\n";
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