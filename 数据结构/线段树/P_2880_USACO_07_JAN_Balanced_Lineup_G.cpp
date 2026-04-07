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
constexpr int P = 998244353, INF = 1e9;
struct SegmentTree {
    int n;
    vector<int> Max, a, Min;
    SegmentTree(int n_)
    {
        n = n_;
        Max.assign(4 * n + 5, 0);
        Min.assign(4 * n + 5, INF);
        a.assign(n + 1, 0);
        for (int i = 1;i <= n;i++)
            cin >> a[i];
        function<void(int, int, int)> build = [&](int l, int r, int p)
        {
            if (l == r)
            {
                Max[p] = a[l];
                Min[p] = a[l];
                return;
            }
            int mid = l + r >> 1;
            build(l, mid, 2 * p);
            build(mid + 1, r, 2 * p + 1);
            pull(p);
        };
        build(1, n, 1);
    }
    void pull(int p) 
    {
        Max[p] = max(Max[2 * p], Max[2 * p + 1]);
        Min[p] = min(Min[2 * p], Min[2 * p + 1]);
    }
    int queryMax(int p, int l, int r, int x, int y) 
    {
        if (l > y || r < x) 
        {
            return 0;
        }
        if (l >= x && r <= y) 
        {
            return Max[p];
        }
        int m = (l + r) / 2;
        return max(queryMax(2 * p, l, m, x, y), queryMax(2 * p + 1, m + 1, r, x, y));
    }
    int queryMin(int p, int l, int r, int x, int y) 
    {
        if (l > y || r < x) 
        {
            return INF;
        }
        if (l >= x && r <= y) 
        {
            return Min[p];
        }
        int m = (l + r) / 2;
        return min(queryMin(2 * p, l, m, x, y), queryMin(2 * p + 1, m + 1, r, x, y));
    }
    int query(int x, int y) 
    {
        return queryMax(1, 1, n, x, y) - queryMin(1, 1, n, x, y);
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    SegmentTree sg(n);
    while(q--)
    {
        int l, r;
        cin >> l >> r;
        cout << sg.query(l, r) << "\n";
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