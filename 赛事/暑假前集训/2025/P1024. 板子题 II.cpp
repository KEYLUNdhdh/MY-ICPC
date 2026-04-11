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
template<typename T>
struct FenWick
{
    int n, m;
    struct Node
    {
        T d1, d2, d3, d4;
        Node() : d1(0), d2(0), d3(0), d4(0) {}
    };

    vector<Node> tr;
    FenWick(int n_ = 0, int m_ = 0)
    {
        init(n_, m_);
    }

    void init(int n_ = 0, int m_ = 0)
    {
        n = n_;
        m = m_;
        tr.assign((n + 1) * (m + 1), Node());
    }

    inline int id(int x, int y) const
    {
        return x * (m + 1) + y;
    }

    void add(int x, int y, T v)
    {
        for (int i = x; i <= n;i += i & (-i))
        {
            for (int j = y; j <= m;j += j & (-j))
            {
                int pos = id(i, j);
                tr[pos].d1 += v;
                tr[pos].d2 += v * x;
                tr[pos].d3 += v * y;
                tr[pos].d4 += v * x * y;
            }
        }
    }

    void rangeAdd(int x1, int y1, int x2, int y2    , T v)
    {
        add(x1, y1, v);
        add(x2 + 1, y1, -v);
        add(x1, y2 + 1, -v);
        add(x2 + 1, y2 + 1, v);
    }

    T query(int x, int y)
    {
        T ans{};
        for (int i = x; i > 0; i-= i & (-i))
        {
            for (int j = y; j > 0;j -= j & (-j))
            {
                int pos = id(i, j);
                ans += tr[pos].d1 * (x + 1) * (y + 1) - tr[pos].d2 * (y + 1) - tr[pos].d3 * (x + 1) + tr[pos].d4;
            }
        }
        return ans;
    }

    T rangeSum(int x1, int y1, int x2, int y2)
    {
        return query(x2, y2) - (query(x1 - 1, y2)) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    FenWick<i64> t(n, m);
    int op;
    while(cin >> op)
    {
        if(op == 1)
        {
            int a, b, c, d, x;
            cin >> a >> b >> c >> d >> x;
            t.rangeAdd(a, b, c, d, x);
        }
        else
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << t.rangeSum(a, b, c, d) << "\n";
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