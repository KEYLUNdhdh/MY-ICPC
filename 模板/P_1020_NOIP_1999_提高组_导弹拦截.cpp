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
//LIS 二分优化算法求最长子序列
//狄尔沃斯定理：下降子序列的最少覆盖数 = 该序列的最长上升子序列（LIS）的长度。
//狄尔沃斯定理：将一个序列剖成若干个单调不升子序列的最小个数等于该序列最长上升子序列的个数
void solve()
{
    int x;
    vector<int> a;
    while(cin >> x)
        a.push_back(x);
    deque<int> d;
    int n = a.size();
    int max1 = 0, max2 = 0;
    for (int i = 0; i < n;i++)
    {
        if(d.empty() || a[i] <= d.back())
            d.push_back(a[i]);
        else
        {
            auto it = upper_bound(d.begin(), d.end(), a[i], greater<int>());
            *it = a[i];
        }
        chmax(max1, (int)d.size());
    }
    d.clear();
    for (int i = 0; i < n;i++)
    {
        if(d.empty() || a[i] > d.back())
            d.push_back(a[i]);
        else
        {
            auto it = lower_bound(d.begin(), d.end(), a[i]);
            *it = a[i];
        }
        chmax(max2, (int)d.size());
    }
    cout << max1 << "\n" << max2 ;
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