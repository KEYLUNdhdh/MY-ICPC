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
constexpr int P = 1e9 + 7;
struct SegmentTree
{
    int n;
    vector<int>  eTag, sum;
    SegmentTree(int n_) : n{n_}, eTag(4 * n + 1, 0), sum(4 * n + 1) {}
    void pull(int p)
    {
        sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % P;
    }
    void push(int p,int l,int r)
    {
        if(eTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applye(2 * p, l, m, eTag[p]);
            applye(2 * p + 1, m + 1, r, eTag[p]);
            eTag[p] = 0;
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
        return (rangeQuery(2 * p, l, m, x, y) % P + rangeQuery(2 * p + 1, m + 1, r, x, y) % P);
    }
    int rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y) % P;
    }
    void applye(int p,int l,int r,i64 v)
    {
        
    }
    void rangee(int p,int l,int r,int x,int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applye(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangee(2 * p, l, m, x, y, v);
        rangee(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangee(int x,int y,i64 v)
    {
        rangee(1, 1, n, x, y, v);
    }
};


void solve()
{
    
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}