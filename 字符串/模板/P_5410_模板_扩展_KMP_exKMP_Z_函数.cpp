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
struct EXKMP
{
    vector<int> z;
    vector<int> p;

    void get_z(const string& b)
    {
        int m = b.size();
        z.assign(m, 0);
        if(m == 0)
            return;
        z[0] = m;
        for (int i = 1, l = 0, r = -1; i < m;i++)
        {
            if(i <= r && z[i - l] < r - i + 1)
                z[i] = z[i - l];
            else
            {
                z[i] = max(0, r - i + 1);
                while(i + z[i] < m && b[z[i]] == b[i + z[i]])
                    z[i]++;
                
            }
            if(z[i] > r - i + 1)
            {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }

    void get_p(const string& a, const string& b)
    {
        int n = a.size(), m = b.size();
        p.assign(n, 0);
        for (int i = 0, l = 0, r = -1; i < n;i++)
        {
            if(i <= r && z[i - l] < r - i + 1)
                p[i] = z[i - l];
            else
            {
                p[i] = max(0, r - i + 1);
                while(i + p[i] < n && p[i] < m && a[i + p[i]] == b[p[i]])
                    p[i]++;
                
            }
            if(p[i] > r - i + 1)
            {
                l = i;
                r = i + p[i] - 1;
            }
        }
    }
};
void solve()
{
    string a, b;
    cin >> a >> b;
    EXKMP k;
    k.get_z(b);
    k.get_p(a, b);
    i64 xz = 0, xp = 0;
    for (int i = 0; i < k.z.size();i++)
        xz ^= 1ll * (i + 1) * (k.z[i] + 1);
    for (int i = 0; i < k.p.size();i++)
        xp ^= 1ll * (i + 1) * (k.p[i] + 1);
    cout << xz << "\n" << xp;
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