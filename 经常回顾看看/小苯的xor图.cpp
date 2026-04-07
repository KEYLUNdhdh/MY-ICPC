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
//既然是异或，我们单独盯着二进制的第 k 位看
//假设中心点 v 在第 k 位的值为 b_v（0 或 1）。
//第 0 类： 第 k 位是 0 的邻居，假设有 c_0 个。
//第 1 类： 第 k 位是 1 的邻居，假设有 c_1 个。
//我们要从邻居里挑两个点 u 和 w，使得它们加上中心点 v 后，在第 k 位的异或和为 1（因为只有异或结果是 1，才会对最终的答案产生 2^k 的贡献）。
//这就有两种情况：
//当中心点 v 的第 k 位 b_v = 0 时：为了让三者异或和为 1，必须满足 u 和 w 在这一位的异或和为 1。也就是必须一 0 一 1。组合数就是：c_0  * c_1 种选法。
//当中心点 v 的第 k 位 b_v = 1 时：为了让三者异或和为 1，必须满足 u 和 w 在这一位的异或和为 0。也就是 u 和 w 必须同 0 或同 1。组合数就是：从 0 里选两个，或者从 1 里选两个。
//显然根据上面思路先大枚举每个二进制位，再枚举每个点进行处理
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    vector<i64> de(n + 1, 0);
    vector<pll> edge(m);
    for (int i = 0; i < m;i++)
    {
        cin >> edge[i].first >> edge[i].second;
        de[edge[i].first]++;
        de[edge[i].second]++;
    }
    i64 sum = 0;
    for (int k = 0; k < 30;k++)
    {
        vector<i64> cnt1(n + 1, 0);
        for(auto& e : edge)
        {
            int u = e.first;
            int v = e.second;
            if((a[u] >> k) & 1)
                cnt1[v]++;
            if((a[v] >> k) & 1)
                cnt1[u]++;
        }
        i64 summ = 0;
        for (int v = 1; v <= n;v++)
        {
            if(de[v] < 2)
                continue;
            i64 c1 = cnt1[v];
            i64 c0 = de[v] - c1;
            i64 w = 0;
            if((a[v] >> k) & 1)
            {
                w = c0 * (c0 - 1) / 2 + c1 * (c1 - 1) / 2;
            }
            else
            {
                w = c0 * c1;
            }
            w %= MOD;
            summ = (summ + w) % MOD;
        }
        sum = (sum + summ * (1ll << k)) % MOD;
    }
    cout << sum;
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