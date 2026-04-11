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
struct Fenwick
{
    int n;
    vector<T> t1, t2;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        t1.assign(n + 1, T{});
        t2.assign(n + 1, T{});
    }

    void add(int x, T v)
    {
        T v2 = v * x;
        for (int i = x; i <= n;i += i & (-i))
        {
            t1[i] += v;
            t2[i] += v2;
        }
    }

    void rangeAdd(int l, int r, T v)
    {
        add(l, v);
        add(r + 1,v);
    }
    T sum(int x)
    {
        T sum1{}, sum2{};
        for (int i = x; i > 0;i -= i & (-i))
        {
            sum1 += t1[i];
            sum2 += t2[i];
        }
        return sum1 * (x + 1) - sum2;
    }    
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1, 0);
    Fenwick<i64> fen(n + 2);

    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        i64 ci = a[i] - 2 * a[i - 1] + (i >= 2 ? a[i - 2] : 0);
        fen.add(i, ci);
    }

    for (int i = 0; i < m;i++)
    {
        int op;
        cin >> op;
        if(op == 1)
        {
            i64 l, r, k, d;
            cin >> l >> r >> k >> d;
            fen.add(l, k);
            fen.add(l + 1, d - k);
            fen.add(r + 1, -(k + (r - l + 1) * d));
            fen.add(r + 2, k + (r - l) * d);
        }
        else
        {
            int p;
            cin >> p;
            cout << fen.sum(p) << "\n";
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