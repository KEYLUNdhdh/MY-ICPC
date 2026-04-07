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
constexpr int MOD = 1e9 + 7, INF = 1e9;
//我们定义 dp[i][j][p][0/1]：
//i：当前考虑到了字符串 A 的第 i 个字符。
//j：当前匹配到了字符串 B 的第 j 个字符。
//p：当前已经划分出了 p 个子串。
//0/1：第 i 个字符 A[i] 是（1）否（0）被选中参与匹配。
void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    string a, b;
    cin >> a >> b;
    a = " " + a;
    b = " " + b;
    vector<vector<array<i64, 2>>> dp(m + 1, vector<array<i64, 2>>(k + 1, {0, 0}));
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        vector<vector<array<i64, 2>>> nxt(m + 1, vector<array<i64, 2>>(k + 1, {0, 0}));
        nxt[0][0][0] = 1;
        for (int j = 1; j <= m;j++)
        {
            for (int p = 1; p <= k;p++)
            {
                if(a[i] != b[j])
                {
                    //xuan
                    nxt[j][p][1] = 0;
                    //bu
                    nxt[j][p][0] = (dp[j][p][0] + dp[j][p][1]) % MOD;
                }
                else
                {
                    //bu
                    nxt[j][p][0] = (dp[j][p][0] + dp[j][p][1]) % MOD;
                    //xuan
                    if(p == 0)
                    {
                        nxt[j][p][1] = dp[j - 1][p][1] % MOD;
                    }
                    else
                    {
                        nxt[j][p][1] = (dp[j - 1][p][1] + dp[j - 1][p - 1][0] + dp[j - 1][p - 1][1]) % MOD;
                    }
                }
            }
        }
        dp = nxt;
   }
   cout << (dp[m][k][0] + dp[m][k][1]) % MOD;
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