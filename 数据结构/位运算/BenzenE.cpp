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

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n), idd(70, 0);
    vector<i64> bas(64, 0);
    vector<u64> mask(64, 0);
    i64 pre = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        pre ^= a[i];
    }
    for (int i = 0; i < n;i++)
        cin >> b[i];
    if(pre == 0)
    {
        for (int i = 0; i < n;i++)
            cout << a[i] << " ";
        cout << "\n";
        return;
    }
    int cnt = 0;
    for (int i = 0; i < n;i++)
    {
        int v = a[i] ^ b[i];
        if(!v)
            continue;
        i64 cur = v;
        u64 curm = 1ull << cnt;
        for (int j = 30; j >= 0;j--)
        {
            if((cur >> j) & 1)
            {
                if(!bas[j])
                {
                    bas[j] = cur;
                    mask[j] = curm;
                    idd[cnt++] = i;
                    break;
                }
                cur ^= bas[j];
                curm ^= mask[j];
            }
        }
    }
    u64 pk = 0;
    for (int i = 30; i >= 0;i--)
    {
        if((pre >> i) & 1)
        {
            if(!bas[i])
            {
                cout << -1 << "\n";
                return;
            }
            pre ^= bas[i];
            pk ^= mask[i];
        }
    }
    vector<int> usd(n);
    for (int i = 0; i < cnt;i++)
    {
        if((pk >> i) & 1)
        {
            usd[idd[i]] = 1;
        }
    }
    for (int i = 0; i < n;i++)
    {
        cout << (usd[i] ? b[i] : a[i]) << " ";
    }
    cout << "\n";
    return;
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