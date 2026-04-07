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
    int n, q;
    cin >> n >> q;
    vector<int> d(n + 1, 0), c(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> d[i] >> c[i];
    deque<int> re;
    vector<int> nxt(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        while(!re.empty() && d[i] > d[re.back()])
        {
            nxt[re.back()] = i;
            re.pop_back();
        }
        re.push_back(i);
    }
    while(!re.empty())
    {
        nxt[re.back()] = 0;
        re.pop_back();
    }
    vector<vector<int>> jump(n + 1, vector<int>(20, 0));
    vector<vector<i64>> sum(n + 1, vector<i64>(20, 0));
    for (int i = 1; i <= n;i++)
    {
        jump[i][0] = nxt[i];
        sum[i][0] = c[nxt[i]];
    }
    for (int j = 1; j <= 19;j++)
    {
        for (int i = 1; i <= n;i++)
        {
            jump[i][j] = jump[jump[i][j - 1]][j - 1];
            sum[i][j] = sum[i][j - 1] + sum[jump[i][j - 1]][j - 1];
        }
    }
    while(q--)
    {
        int r;
        i64 v;
        cin >> r >> v;
        if(c[r] >= v)
        {
            cout << r << "\n";
            continue;
        }
        v -= c[r];
        for (int j = 19; j >= 0;j--)
        {
            if(jump[r][j] != 0 && v > sum[r][j])
            {
                v -= sum[r][j];
                r = jump[r][j];
            }
        }
        cout << jump[r][0] << "\n";
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