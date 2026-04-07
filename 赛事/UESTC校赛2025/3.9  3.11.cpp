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

void solve()
{
    string a, b;
    char c;
    cin >> a >> c >> b;
    double aaa = stod(a), bbb = stod(b);
    //num
    char now;
    if(aaa > bbb)
        now = '>';
    else if(aaa == bbb)
        now = '=';
    else
        now = '<';
    int fn = 0, fs = 0;
    if(c == now)
        fn = 1;
    //s
    int ab, as, bb, bs;
    auto sw = [&](string s, int &x, int &y) -> void
    {
        int pos = s.find('.');
        string s1 = s.substr(0, pos);
        string s2 = s.substr(pos + 1);
        x = stoi(s1);
        y = stoi(s2);
        return;
    };
    sw(a, ab, as);
    sw(b, bb, bs);
    // debug(ab)debug(as)debug(bb)debug(bs)
    // cutline

    if(ab > bb)
        now = '>';
    else if(ab < bb)
        now = '<';
    else
    {
        if(as > bs)
            now = '>';
        else if(as < bs)
            now = '<';
        else
            now = '=';
    }
    if(now == c)
        fs = 1;
    if(fs && fn)
        cout << "Both\n";
    else if(fs)
        cout << "Version\n";
    else if(fn)
        cout << "Number\n";
    else
        cout << "?\n";
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