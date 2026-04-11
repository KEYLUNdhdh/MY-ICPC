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
const int P = 998244353;
//为了解决“跨越边界”的问题，我们需要让线段树的每个节点（Node）维护 4 个变量：
// sum：当前区间的总和。
// lmax：当前区间的最大前缀和（必须包含区间最左端点的最大连续和）。
// rmax：当前区间的最大后缀和（必须包含区间最右端点的最大连续和）。
// mmax：当前区间的最大子段和（可以出现在区间内任何位置，也就是我们最终要求的答案）。
struct SegmentTree {
    int n;
    std::vector<int> sum, lmax, rmax, mmax, eTag;
    SegmentTree(int n_) : n(n_), sum(4 * n + 1, 0), lmax(4 * n + 1), rmax(4 * n + 1), mmax(4 * n + 1), eTag(4 * n + 1) {}

    void pull(int p) 
    {
        int lhs = p << 1;
        int rhs = p << 1 | 1;
        sum[p] = sum[lhs] + sum[rhs];
        lmax[p] = max(lmax[lhs], lmax[rhs] + sum[lhs]);
        rmax[p] = max(rmax[rhs], rmax[lhs] + sum[rhs]);
        mmax[p] = max(max(mmax[rhs], mmax[lhs]), rmax[lhs] + lmax[rhs]);
    }

    void init(int p, int l, int r, const vector<int> &a)
    {
        if(l == r)
        {
            sum[p] = lmax[p] = rmax[p] = mmax[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        init(p << 1, l, m, a);
        init(p << 1 | 1, m + 1, r, a);
        pull(p);
    }
    //注意剪枝啊
    void sw(int p ,int l, int r, int pos, int val)
    {
        if(l == r && r == pos)
        {
            sum[p] = lmax[p] = rmax[p] = mmax[p] = val;
            return;
        }
        int m = l + r >> 1;
        if(pos <= m)
            sw(p << 1, l, m, pos, val);
        else
            sw(p << 1 | 1, m + 1, r, pos, val);
        pull(p);
    }
    
    struct node
    {
        int sum, lmax, rmax, mmax;
    };
    //query返回结构体，然后我们拼一拼
    node query(int p, int l, int r, int x, int y) 
    {
        if(l >= x && r <= y)
        {
            return {sum[p], lmax[p], rmax[p], mmax[p]};
        }

        int m = l + r >> 1;
        if(y <= m)
            return query(p << 1, l, m, x, y);
        if(x >= m + 1)
            return query(p << 1 | 1, m + 1, r, x, y);
        node ll = query(p << 1, l, m, x, y);
        node rr = query(p << 1 | 1, m + 1, r, x, y);
        node tmp;
        tmp.sum = ll.sum + rr.sum;
        tmp.lmax = max(ll.lmax, ll.sum + rr.lmax);
        tmp.rmax = max(rr.rmax, rr.sum + ll.rmax);
        tmp.mmax = max(max(ll.mmax, rr.mmax), ll.rmax + rr.lmax);

        return tmp;
    }
    
    int query(int x, int y) 
    {
        node tmp = query(1, 1, n, x, y);
        return tmp.mmax;
    }
    
    
};
void solve()
{
    int n, m;
    cin >> n >> m;
    SegmentTree sg(n);
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    sg.init(1, 1, n, a);
    while (m--)
    {
        int k;
        cin >> k;
        // debug(k)
        if (k == 1)
        {
            int a, b;
            cin >> a >> b;
            if (a > b)
                swap(a, b);
            // debug(a)
            cout << sg.query(a, b) << "\n";
        }
        else
        {
            int p, s;
            cin >> p >> s;
            sg.sw(1, 1, n, p, s);
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