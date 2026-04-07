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
    vector<int> addTag, sum;
    SegmentTree(int n_) : n{n_}, addTag(4 * n + 1, 0), sum(4 * n + 1) {}
    void pull(int p)
    {
        sum[p] = (sum[2 * p] + sum[2 * p + 1]);
    }
    void push(int p, int l, int r)
    {
        if(addTag[p])
        {
            int mid = l + r >> 1;
            sum[2 * p] = mid - l + 1 - sum[2 * p];
            sum[2 * p + 1] = r - mid - sum[2 * p + 1];
            addTag[p] = 0;
            addTag[2 * p] ^= 1;
            addTag[2 * p + 1] ^= 1;
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
    void sw(int p,int l,int r,int x, int y)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            sum[p] = r - l + 1 - sum[p];
            addTag[p] ^= 1;
            return;
        }
        int mid = l + r >> 1;
        push(p, l, r);
        sw(2 * p, l, mid, x, y);
        sw(2 * p + 1, mid + 1, r, x, y);
        pull(p);
        return;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    SegmentTree sg(n);
    for (int i = 0; i < m;i++)
    {
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1)
        {
            cout << sg.rangeQuery(x, y) << "\n";
        }
        else
        {
            sg.sw(1, 1, n, x, y);
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