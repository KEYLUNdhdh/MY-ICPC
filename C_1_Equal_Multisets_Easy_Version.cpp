#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------" << endl;}

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
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);
    vector<int> vis(n + 5, 0);
    vector<int> pos(n + 1, -1);
    int f = 0;
    for (int i = 0; i < n;i++)
        cin >> a[i],pos[a[i]] = i;
    for (int i = 0; i < n;i++)
    {
        cin >> b[i];
        if(b[i] != -1 && vis[b[i]])
            f = 1;
        else if(b[i] != -1)
            vis[b[i]] = 1;
    }
    if(f)
    {
        cout << "NO\n";
        return;
    }
    int l = n - k;
    int r = k - 1;
    if(l > r)
    {
        for (int i = 0; i < n;i++)
        {
            if(b[i] != -1 && b[i] != a[i])
            {
                cout << "NO\n";
                return;
            }
        }
    }
    else
    {
        for (int i = 0; i < l;i++)
        {
            if(b[i] != -1 && b[i] != a[i])
            {
                cout << "NO\n";
                return;
            }
        }
        for (int i = r + 1;i < n;i++)
        {
            if(b[i] != -1 && b[i] != a[i])
            {
                cout << "NO\n";
                return;
            }
        }
        for (int i = l; i <= r;i++)
        {
            if(b[i] == -1)
                continue;
            int p = pos[b[i]];
            if(p < l || p > r)
            {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
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