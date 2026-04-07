#include <bits/stdc++.h>
#define lyc_fan_club main
#define int long long
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

void solve()
{
    int n, h, k;
    cin >> n >> h >> k;
    vector<int> a(n + 1), prefix(n + 1, 0);
    vector<int> dpmin(n + 1, INF), dpmax(n + 1, -INF);
    int sum = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        sum += a[i];
        prefix[i] = prefix[i - 1] + a[i];
        dpmin[i] = min(dpmin[i - 1], a[i]);
    }
    dpmax[n] = a[n];
    for (int i = n - 1; i >= 1;i--)
    {
        dpmax[i] = max(dpmax[i + 1], a[i]);
    }
    int len = h / sum;
    int rest = h % sum;
    if (rest == 0)
    {
        int ans = len * n + (len - 1) * k;
        cout << ans << "\n";
        return;
    }
    int l = -1, r = n + 1;
    auto check = [&](int x) -> bool
    {
        int ini = prefix[x];
        int minn = dpmin[x];
        int maxx = (x + 1 <= n ? dpmax[x + 1] : 0);
        if(minn < maxx)
            ini = ini - minn + maxx;
        return ini >= rest;
    };
    while (l + 1 < r)
    {
        int mid = l + r >> 1;
        if(check(mid))
            r = mid;
        else
            l = mid;
    }
    int ans = len * (n + k) + r;
    cout << ans << "\n";
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