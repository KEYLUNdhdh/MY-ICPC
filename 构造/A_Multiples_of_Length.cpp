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
//利用n - 1的长度去构造n的倍数，然后直接减去就可以
void solve()
{
    i64 n;
    cin >> n;
    vector<i64> a(n + 1, 0);
    for (i64 i = 1; i <= n;i++)
        cin >> a[i];
    if(n == 1)
    {
        cout << 1 << " " << 1 << "\n" << -a[1] << "\n";
        cout << 1 << " " << 1 << "\n" << 0 << "\n";
        cout << 1 << " " << 1 << "\n" << 0 << "\n";
        return;
    }
    cout << 2 << " " << n << "\n";
    i64 k = n - 1;
    for (i64 i = 2; i <= n;i++)
    {
        cout << k * a[i] << " ";
        a[i] = a[i] + k * a[i];
    }
    cout << "\n";
    // debugarr(a)
    cout << 1 << " " << n << "\n";
    for (i64 i = 1; i <= n;i++)
    {
        if(i == 1)
            cout << n << " ";
        else
            cout << -a[i] << " ";
    }
    a[1] += n;
    cout << "\n";
    cout << 1 << " " << 1 << "\n";
    cout << -a[1];
}


signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    i64 T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}