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

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    //010101...
    i64 tmp = 0;
    i64 ans = 0;
    int w0 = 0, w1 = 0;
    int sum = 0;
    for (int i = 0;i < n;i++)
    {
        if(i % 2 == 0 && s[i] != '0')
            w0++;
        else if(i % 2 == 1 && s[i] != '1')
            w1++;
        sum += s[i] - '0';
    }
    int up = n / 2;
    if(sum >= up)//delete 1
    {
        int dis = sum - up;
        w0 -= dis;
        tmp += dis;
        tmp += w0;
    }
    else//delete 0
    {
        int dis = up - sum;
        w1 -= dis;
        tmp += dis + w1;
    }
    w0 = 0, w1 = 0, sum = 0;
    //101010101....
    for (int i = 0;i < n;i++)
    {
        if(i % 2 == 0 && s[i] != '1')
            w1++;
        else if(i % 2 == 1 && s[i] != '0')
            w0++;
        sum += s[i] - '0';
    }
    up = (n + 1) / 2;
    if(sum >= up)//delete 1
    {
        int dis = sum - up;
        w0 -= dis;
        ans += dis;
        ans += w0;
    }
    else//delete 0
    {
        int dis = up - sum;
        w1 -= dis;
        ans += dis + w1;
    }
    cout << min(tmp, ans);
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