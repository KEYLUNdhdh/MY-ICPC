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

void solve()
{
    int n;
    cin >> n;
    vector<i64> v(n + 1, 0), t(n + 1, 0);
    vector<i64> dis(n + 1, 0);
    vector<i64> prefix(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> v[i];
    for (int i = 1; i <= n;i++)
    {
        cin >> t[i];
        prefix[i] = prefix[i - 1] + t[i];
    }
    vector<i64> tag(n + 1, 0), sum(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        i64 num = v[i];
        i64 up = num + prefix[i - 1];
        auto it = lower_bound(prefix.begin(), prefix.end(), up) - prefix.begin();
        i64 lst = num - (prefix[it - 1] - prefix[i - 1]);
        tag[i] += 1;
        if(it <= n)
        {
            tag[it] -= 1;
            sum[it] += lst;
        }
    }
    for (int i = 1; i <= n;i++)
        tag[i] = tag[i - 1] + tag[i];
    for (int i = 1; i <= n;i++)
    {
        cout << tag[i] * t[i] + sum[i] << " ";
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