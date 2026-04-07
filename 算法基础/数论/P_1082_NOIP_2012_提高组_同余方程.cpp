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

struct exgcd
{
    struct result
    {
        i64 x, y, g;
        bool f;
    };
    static result solve(i64 a,i64 b,i64 c)
    {
        i64 x = 1, y = 0, g = a;
        function<void(i64, i64)> dfs = [&](i64 a, i64 b)
        {
            if(b == 0)
            {
                g = a;
                x = 1, y = 0;
                return;
            }
            dfs(b, a % b);
            i64 tp = x;
            x = y;
            y = tp - (i64)(a / b) * y;
        };
        dfs(a, b);
        if(g < 0)
        {
            g = -g;
            x = -x;
            y = -y;
        }
        if(c % g)
        {
            return {0, 0, g, false};
        }
        i64 factor = c / g;
        return {x * factor, y * factor, g, true};
    }
    static pair<i64,i64> minx(i64 a,i64 b,i64 c)
    {
        result res = solve(a, b, c);
        if(!res.f)
            return {-1, -1};
        if(c == 0)
            return {0, (i64)res.g};
        i64 bg = b / res.g;   
        if(bg < 0)
            bg = -bg;
        i64 k = -res.x / bg;
        while(res.x + k * bg < 0)
            k++;
        while(res.x + (k - 1) * bg >= 0)
            k--;
        i64 x = res.x + k * bg;
        return {x, (i64)res.g};
    }
};
void solve()
{
    i64 a, b;
    cin >> a >> b;
    auto [x, y, g, f] = exgcd::solve(a, b, 1);
    // debug(x)
    // debug(y)
    // debug(g)
    // debug(f)
    cout << (x + b) % b;
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