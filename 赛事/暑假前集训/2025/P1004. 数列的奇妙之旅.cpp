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
    vector<i64> sqTag;
    vector<array<i64, 7>> sum;
    SegmentTree(int n_, const vector<i64> &a) : n{n_}, sqTag(4 * n + 1, 0), sum(4 * n + 1)
    {
        init(1, 1, n, a);
    }

    void init(int p, int l, int r, const vector<i64> &a)
    {
        if(l == r)
        {
            i64 num = a[l];
            for (int i = 0; i < 7;i++)
            {
                sum[p][i] = num;
                num = sqrt(num);
            }
            return;
        }
        int m = l + r >> 1;
        init(p << 1, l, m, a);
        init(p << 1 | 1, m + 1, r, a);
        pull(p);
    }
    void pull(int p)
    {
        for (int i = 0; i <= 6;i++)
        {
            sum[p][i] = (sum[p << 1][i] + sum[p << 1 | 1][i]);
        }
    }
    void push(int p,int l,int r)
    {
        if(sqTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applys(2 * p, l, m, sqTag[p]);
            applys(2 * p + 1, m + 1, r, sqTag[p]);
            sqTag[p] = 0;
        }
    }
    i64 rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sum[p][0];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return (rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y));
    }
    i64 rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }
    
    void applys(int p,int l,int r,i64 cnt)
    {
        // pos[p] += cnt;
        // if(pos[p] > 6)
        //     pos[p] = 6;
        for (int i = 0; i <= 6;i++)
        {
            int idx = ((i + cnt <= 6) ? i + cnt : -1);
            if(idx == -1)
                sum[p][i] = sum[p][6];
            else
                sum[p][i] = sum[p][idx];
        }
        sqTag[p] += cnt;
    }
    void ranges(int p,int l,int r,int x,int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applys(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        ranges(2 * p, l, m, x, y, v);
        ranges(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void ranges(int x,int y)
    {
        ranges(1, 1, n, x, y, 1);
    }
};
//这种开方问题，我们考虑把array向前移动
//这种想法很关键，为状态机线段树
void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    SegmentTree sg(n, a);
    int m;
    cin >> m;
    while(m--)
    {
        int k, l, r;
        cin >> k >> l >> r;
        if(l > r)
            swap(l, r);
        if(k == 0)
        {
            sg.ranges(l, r);
        }
        else
        {
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