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
constexpr int MOD = 998244353, INF = 1e9;
struct rail
{
    int a, b, c;
};
void solve()
{
    i64 n, m;
    cin >> n >> m;
    vector<i64> p(m + 1, 0);
    for (i64 i = 1; i <= m;i++)
        cin >> p[i];
    vector<rail> ra(n);
    vector<i64> rec(n + 1, 0);
    for (i64 i = 1; i <= n - 1;i++)
        cin >> ra[i].a >> ra[i].b >> ra[i].c;
    for (i64 i = 1; i <= m - 1;i++)
    {
        i64 u = p[i];
        i64 v = p[i + 1];
        if(u < v)
        {
            rec[u]++;
            rec[v]--;       
        }
        else
        {
            rec[v]++;
            rec[u]--;
        }   
    }
    for (i64 i = 1; i <= n;i++)
        rec[i] = rec[i - 1] + rec[i];
    // debug(rec);
    i64 ans = 0;
    for (i64 i = 1; i <= n - 1;i++)
    {
        i64 cnt = rec[i];
        ans += min(ra[i].a * cnt, ra[i].c + ra[i].b * cnt);
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