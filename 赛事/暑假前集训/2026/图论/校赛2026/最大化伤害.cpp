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
using db = double;
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
//定义 C[x] 表示原数组中，是 x 的倍数的数字的总个数。
// 如果我们将这 C[x] 个数字全部放在最前面，它们产生的前缀 GCD 至少是 x。

//我们可以定义状态 dp[x]：表示排好前 C[x] 个元素（也就是把所有 x 的倍数都用上），且最后一个元素对应的当前前缀 GCD 为 x 时，能产生的最大伤害和。

//基于上面的思考，对于任何一个 y，我们可以去枚举它的倍数 x（即 x = 2y, 3y, 4y...）：
// dp[y] = max(dp[y], dp[x] + (C[y] - C[x]) * y)
// 最开始的基础情况是，如果不从任何更大的倍数转移过来，直接把这 C[y] 个数拿来产生 y 的伤害：dp[y] = C[y] * y。
// 最终的答案就是 dp[1]，因为 C[1] 等于 n，代表我们把所有 n 个数字都用完了，GCD 降到了 1。

void solve()
{
    int n;
    cin >> n;
    vector<i64> a(n);
    i64 maxx = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        chmax(maxx, a[i]);
    }
    vector<int> c(maxx + 1, 0);
    vector<int> cnt(maxx + 1, 0);

    for (int i = 0; i < n;i++)
    {
        cnt[a[i]]++;
    }
    for (int i = 1; i <= maxx;i++)
    {
        for (int j = 1; i * j <= maxx;j++)
        {
            if(cnt[i * j])
                c[i] += cnt[i * j];
        }
    }
    vector<i64> dp(maxx + 1, 0);
    for (int i = maxx; i >= 1;i--)
    {
        dp[i] = cnt[i] * i;
        for (int k = 1; k * i <= maxx;k++)
        {
            chmax(dp[i], dp[i * k] + (c[i] - c[i * k]) * i);
        }
    }
    cout << dp[1];
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