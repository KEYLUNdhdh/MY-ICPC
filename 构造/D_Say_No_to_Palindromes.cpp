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
//假设第一个字母是 a，第二个字母是 b，为了不和它们相等，第三个字母必须是 c。同理，第四个字母不能是 b 也不能是 c，必须是 a。你会发现，一旦前两个字母确定了，整个字符串的排列就只能无限循环下去了！
//所以我们枚举六个开头，然后递推下去就行
void solve()
{
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<string> a(6);
    a[0] = "ab", a[1] = "ac", a[2] = "ba", a[3] = "bc", a[4] = "ca", a[5] = "cb";
    auto sw = [&](int k) -> void
    {
        for (int i = 2; i < n;i++)
        {
            for (int j = 0; j < 3;j++)
            {
                char ch = 'a' + j;
                if(ch != a[k][i - 1] && ch != a[k][i - 2])
                    a[k].push_back(ch);
            }
        }
    };
    for (int i = 0; i < 6;i++)
        sw(i);
    vector<vector<int>> dp(6, vector<int>(n + 1, 0));
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < 6;j++)
        {
            if(a[j][i] != s[i])
                dp[j][i] = (i == 0 ? 1 : dp[j][i - 1] + 1);
            else
                dp[j][i] = (i == 0 ? 0 : dp[j][i - 1]);
        }
    }
    while(m--)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        debug(l)debug(r)
        cutline
        int ans = INF;
        for (int i = 0; i < 6;i++)
            chmin(ans, dp[i][r] - (l >= 1 ? dp[i][l - 1] : 0));
        cout << ans << "\n";
    }
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