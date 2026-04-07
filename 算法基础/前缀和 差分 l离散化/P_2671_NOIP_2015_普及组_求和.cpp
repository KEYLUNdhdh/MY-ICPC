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
constexpr int MOD = 10007, INF = 1e9;

struct da
{
    i128 k = 0, prefixx = 0, prefixnum = 0, prefixxnum = 0;
};

ostream &operator<<(ostream &os, i128 n) {
    string s;
    if(n == 0)
        s = "0";
    if(n < 0)
    {
        s += "-";
        n = -n;
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

istream &operator>>(istream &is,i128& n)
{
    n = 0;
    string s;
    is >> s;
    for (int i = 0; i < s.size();i++)
    {
        n = n * 10 + s[i] - '0';
    }
    return is;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> num(n + 1, 0);
    vector<int> color(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> num[i];
    for (int i = 1; i <= n;i++)
        cin >> color[i];
    vector<array<da, 2>> sum(m + 5);
    for (int i = 1; i <= n;i++)
    {
        int pos = i % 2;
        int co = color[i];
        sum[co][pos].k++;
        sum[co][pos].prefixnum = (sum[co][pos].prefixnum + num[i]) % MOD;
        sum[co][pos].prefixx = (i + sum[co][pos].prefixx) % MOD;
        sum[co][pos].prefixxnum = ((i128)i * num[i] + sum[co][pos].prefixxnum) % MOD;
    }
    i128 ans = 0;
    for (int i = 1; i <= m;i++)
    {
        for (int pos = 0; pos <= 1; pos++) 
        {
            if (sum[i][pos].k < 2) continue;
            
            i128 k_term = (sum[i][pos].k - 2) % MOD;
            i128 part1 = k_term * sum[i][pos].prefixxnum % MOD;
            i128 part2 = sum[i][pos].prefixnum * sum[i][pos].prefixx % MOD;
            
            ans = (ans + part1 + part2) % MOD;
        }
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