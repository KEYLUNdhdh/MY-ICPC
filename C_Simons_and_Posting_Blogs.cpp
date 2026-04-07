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
bool cmp(deque<int> &a, deque<int> &b)
{
    int idx = 0;
    while(idx < a.size() && idx < b.size() && a[idx] == b[idx])
        idx++;
    if(idx == a.size())
        return true;
    else if(idx == b.size())
        return false;
    else
        return a[idx] < b[idx];
}
void solve()
{
    int n;
    cin >> n;
    vector<deque<int>> a(n + 1);
    vector<int> vis(1e6 + 5, 0);
    for (int i = 1; i <= n;i++)
    {
        int l;
        cin >> l;
        a[i].assign(l, 0);
        for (int j = l - 1; j >= 0;j--)
            cin >> a[i][j];
    }
    while(1)
    {
        int minn = 1e9;
        vector<int> poss;
        int f = 0;
        for (int i = 1; i <= n;i++)
        {
            if(!a[i].empty())
            {
                while(!a[i].empty() && vis[a[i].front()])
                    a[i].pop_front();
                f = 1;
                if(a[i].front() < minn)
                {
                    poss.clear();
                    minn = a[i].front();
                    poss.push_back(i);
                }
                else if(a[i].front() == minn)
                {
                    poss.push_back(i);
                }
            }
        }
        vector<deque<int>> tmp;
        for(int k : poss)
        {
            tmp.push_back(a[k]);
        }
        sort(tmp.begin(), tmp.end(), cmp);
        int pos = -1;
        for (int k : poss)
        {
            if(a[k] == tmp[0])
            {
                pos = k;
                break;
            }
        }
        if (!f)
            break;
        for (int j = 0; j < a[pos].size();j++)
        {
            if(!vis[a[pos][j]])
            {
                cout << a[pos][j] << " ";
                vis[a[pos][j]]++;
            }
        }
        a[pos].clear();
        for (int i = 1; i <= n;i++)
        {
            while(!a[i].empty() && vis[a[i].front()])
                a[i].pop_front();
        }
    }
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