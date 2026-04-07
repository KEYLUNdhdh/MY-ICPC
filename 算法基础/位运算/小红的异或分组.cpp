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
//因为a^a = 0，所以如果三个组的异或和相等，那么这三个组的异或和都应该是总体的异或和s
// 那么可以先求出后缀异或和为s的数组个数
// 然后从左到右枚举当前缀异或和为s时，累加后缀的异或和为s的个数，中间段不用考虑，因为异或和必为s
void solve()
{
    int n;
    cin >> n;
    i64 pre = 0;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        pre ^= a[i];
    }
    vector<i64> nxt(n + 1, 0);
    int next = a[n];
    nxt[n] = (next == pre ? 1 : 0);
    for (int i = n - 1; i >= 1;i--)
    {
        next ^= a[i];
        nxt[i] = (next == pre ? nxt[i + 1] + 1 : nxt[i + 1]);
    }
    i64 prefix = 0;
    i64 ans = 0;
    for (int i = 1; i <= n - 2;i++)
    {
        prefix ^= a[i];
        if(prefix == pre)
        {
            ans += nxt[i + 2];
        }
    }
    cout << ans;
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