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
    int v;
    cin >> v;
    ld v1, v2, v3;
    ld w1, w2, w3;
    cin >> v1 >> w1;
    cin >> v2 >> w2;
    cin >> v3 >> w3;
    ld k1 = w1 / v1;
    ld k2 = w2 / v2;
    ld k3 = w3 / v3;
    ld maxx = max(max(k1, k2), k3);
    if(k1 == maxx){}
    else if(k2 == maxx)
    {
        swap(k1, k2);
        swap(v1, v2);
        swap(w1, w2);
    }
    else
    {
        swap(k1, k3);
        swap(v1, v3);
        swap(w1, w3);
    }
    i64 up = v / v1;
    up = (up >= 100 ? up - 100 : 0);
    i64 ans = up * w1;
    i64 re = v - up * v1;
    i64 maxxx = 0;
    for (i64 i = 0; v1 * i <= re;i++)
        for (i64 j = 0; v2 * j <= re;j++)
            for (i64 k = 0; k * v3 <= re;k++)
            {
                if(v1 * i + v2 * j + v3 * k > re)
                    continue;
                chmax(maxxx, i * (i64)w1 + j * (i64)w2 + k * (i64)w3);
            }
    cout << ans + maxxx << "\n";
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