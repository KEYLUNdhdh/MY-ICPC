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
// 【分治的切分点】队伍的第一个人必然是 A（否则一开始就没钱找）。我们去寻找：钱箱里的 50 元余额，在队伍中“第一次重新变回 0” 是在什么时候？
//假设这个“第一次变回 0”发生在这 2n 个人中的第 2k 个位置。既然是余额变回 0，说明第 2k 个人必然是 B，他消耗掉了第 1 个人带来的那张 50 元。这样一来，我们就成功地把原本长达 2n 的队伍，劈成了两个完全独立的部分：
// 左半部分（包含在 A 和 B 之间的人）：也就是队伍的第 2 到第 2k-1 个人。这里面一共有 k-1 对 A 和 B。
//因为第 2k 个人才是“第一次”让余额归零的，说明在这中间的任何时刻，余额都严格 >0。这就等价于他们自己内部也是一个合法的购票序列。
//👉 这里的合法排队方案数是：f(k-1)
//右半部分（B 之后的人）：也就是队伍的第 2k+1 到第 2n 个人。这里面一共有 n-k 对 A 和 B。
//从第 2k+1 个人开始，钱箱又回到了初始状态（余额为 0），他们也要完成合法的购票。
// 👉 这里的合法排队方案数是：f(n-k)
//【合并答案】根据乘法原理，对于固定的切分点 k，方案数为：f(k-1) * f(n-k)。而这个切分点 k 可以是 1 到 n 之间的任何一个数。我们把所有可能的情况加起来，就得到了卡特兰数的递推公式：
void solve()
{
    i64 n;
    cin >> n;
    vector<i64> memo(n + 1, 0);

    auto sol = [&](auto self, i64 now) -> i64
    {
        if(now == 0 || now == 1)
            return 1;
        if(memo[now] != 0)
            return memo[now];
        i64 sum = 0;
        for (int i = 0;i < now;i++)
            sum += self(self, i) * self(self, now - 1 - i);
        return memo[now] = sum;
    };

    i64 ans = sol(sol, n);
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
