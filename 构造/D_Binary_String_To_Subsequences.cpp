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
//用桶去存我们的子序列
//以子序列结尾去区分
void solve()
{
    int n;
    cin >> n;
    string a;
    cin >> a;
    deque<deque<int>> e0, e1;
    for (int i = 0; i < n;i++)
    {
        if(a[i] == '0')
        {
            if(e1.empty())
            {
                deque<int> tmp = {i};
                e0.push_back(tmp);
            }
            else
            {
                deque<int> tmp = e1.front();
                tmp.push_back(i);
                e1.pop_front();
                e0.push_back(tmp);
            }
        }
        else
        {
            if(e0.empty())
            {
                deque<int> tmp = {i};
                e1.push_back(tmp);
            }
            else
            {
                deque<int> tmp = e0.front();
                tmp.push_back(i);
                e0.pop_front();
                e1.push_back(tmp);
            }
        }
    }
    vector<int> res(n, -1);
    cout << e0.size() + e1.size() << "\n";
    int tot = 1;
    for(auto d : e0)
    {
        for(int k : d)
            res[k] = tot;
        tot++;
    }
    for(auto d : e1)
    {
        for(int k : d)
            res[k] = tot;
        tot++;
    }
    for(int k : res)
        cout << k << " ";
    cout << "\n";
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