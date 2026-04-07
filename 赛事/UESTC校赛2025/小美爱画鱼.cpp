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
struct seg
{
    int c;
    int x1, x2;
    bool operator<(const seg& b)
    {
        if(c != b.c)
            return c > b.c;
        else if(x1 != b.x1)
            return x1 < b.x1;
        else
            return x2 < b.x2;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<seg> s(n);
    for (int i = 0; i < n;i++)
    {
        int y1, y2;
        cin >> s[i].x1 >> y1 >> s[i].x2 >> y2;
        s[i].c = s[i].x1 + y1;
    }
    sort(s.begin(), s.end());
    bool f = 1;
    i64 len = 0;
    int i = 0;
    while(i < n)
    {
        int j = i;
        while (j < n && s[j].c == s[i].c)
            j++;
        int cs = s[i].x1;
        int ce = s[i].x2;
        for (int k = i + 1;k < j;k++)
        {
            if(s[k].x1 < ce)
            {
                f = 0;
                ce = max(ce, s[k].x2);
            }
            else
            {
                len += ce - cs;
                cs = s[k].x1;
                ce = s[k].x2;
            }
        }
        len += ce - cs;
        i = j;
    }
    if(f)
        cout << "YES\n";
    else
        cout << "NO\n";
    cout << len << "\n";
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