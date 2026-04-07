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
//这题讨论要很小心
void solve()
{
    int n;
    cin >> n;
    vector<ld> a(n + 1, 0), b(n + 1, 0);
    vector<ld> prefixa(n + 1, 0), prefixb(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i] >> b[i];
    //对sort后的做前缀和
    sort(a.begin(), a.end(), greater<ld>());
    sort(b.begin(), b.end(), greater<ld>());
    for (int i = 1; i <= n;i++)
    {
        prefixa[i] = prefixa[i - 1] + a[i - 1];
        prefixb[i] = prefixb[i - 1] + b[i - 1];
    }
    auto check = [&](ld x) -> bool
    {
        for (int i = 2; i <= 2 * n; i++)
        {
            auto pos = lower_bound(prefixa.begin(), prefixa.end(), x + i) - prefixa.begin();
            if(pos == n + 1 || pos >= i)//如果i不够选，或者A数组全选都达不到要求
                continue;
            int rest = i - pos;
            if(rest >= n)//有多余的就可以全选
                rest = n;
            if (prefixb[rest]>= x + i)
                return true;
        }
        return false;
    };
    ld l = 0, r = 1e9 + 7;
    while (r - l >= 1e-7)
    {
        ld mid = (l + r)/ (ld)2.0;
        if(check(mid))
            l = mid;
        else
            r = mid;
    }
    cout << fixed << setprecision(4) << l;
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