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
struct date
{
    int y, m, d;
};
date in(string tmp)
{
    date tp;
    string y, m, d;
    y = tmp.substr(0, 4);
    m = tmp.substr(5, 2);
    d = tmp.substr(8, 2);
    tp.y = stoi(y), tp.m = stoi(m), tp.d = stoi(d);
    return tp;
}

int dis(date q)
{
    int y = q.y;
    int m = q.m;
    int d = q.d;
    vector<int> month = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int res = 0;
    res += 365 * (y - 1);
    for (int i = 1; i < m;i++)
        res += month[i];
    res += d - 1;
    return res;
}
void solve()
{
    int n;
    cin >> n;
    int ans = 0;
    date s, e;
    string tmp;
    cin >> tmp;
    s = in(tmp);
    cin >> tmp;
    e = in(tmp);
    // cerr << s.y << " " << s.m << " " << s.d << "\n";
    // cerr << e.y << " " << e.m << " " << e.d << "\n";

    for (int i = 0; i < n;i++)
    {
        cin >> tmp;
        date x = in(tmp);
        // cerr << x.y << " " << x.m << " " << x.d << "\n";
        cin >> tmp;
        int k = stoi(tmp);
        // cerr  << k << "\n";
        int ss = dis(s);
        int ee = dis(e);
        int kk = dis(x);
        if(kk >= ss && kk <= ee)
            ans += k;
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