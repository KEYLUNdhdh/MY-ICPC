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
const int MAX = 2e4 + 5;

i64 qpow(i64 a, i64 b)
{
    a %= MOD;
    i64 res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}
void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n);
    unordered_map<int, int> mp;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        mp[a[i]]++;
    }
    i64 ans = n;//len = 1
    for(auto &[x, y] : mp)//d = 0
    {
        ans = (ans + qpow(2, y) - 1 - y + MOD) % MOD;
    }
    vector<i64> dp(MAX + 1, 0);
    for (int d = -MAX; d <= MAX;d++)
    {
        if(d == 0)
            continue;
        for (int i = 0; i < n;i++)
        {
            int h = a[i];
            int prev = h - d;
            int cntpre = 0;
            if(prev >= 0 && prev <= MAX)
                cntpre = dp[prev];
            ans = (ans + cntpre) % MOD;
            dp[h] = (dp[h] + cntpre + 1) % MOD;
        }
        for (int i = 0; i < n;i++)
            dp[a[i]] = 0;
    }
    cout << ans << "\n";
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