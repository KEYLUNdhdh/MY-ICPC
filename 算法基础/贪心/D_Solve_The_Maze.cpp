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
//我们考虑贪心
//对B的封锁，最经济的做法是把紧挨着B但不是墙的那些给封锁上
//我们再从终点逆向BFS，看看所有好人是否与终点联通了
//但是我们要注意，sw函数只能封锁.但不能封锁G，意味着如果有B与G紧挨着，它可能会漏跑出去，所以我们最后再做一次循环判断
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> ma(n + 1, vector<char>(m + 1, '\0'));
    vector<pii> posb;
    vector<pii> posg;
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= m;j++)
        {
            cin >> ma[i][j];
            if(ma[i][j] == 'B')
                posb.push_back({i, j});
            else if(ma[i][j] == 'G')
                posg.push_back({i, j});
        }
    vector<int> dx = {0, 1, 0, -1};
    vector<int> dy = {1, 0, -1, 0};
    auto sw = [&](int i, int j) -> void
    {
        for (int k = 0; k < 4;k++)
        {
            int nx = i + dx[k];
            int ny = j + dy[k];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && ma[nx][ny] == '.')
                ma[nx][ny] = '#';
        }
    };
    for(auto &[x, y] : posb)
        sw(x, y);
    deque<pii> d;
    vector<vector<int>> ava(n + 1, vector<int>(m + 1, 0));
    if(ma[n][m] != '#')
    {
        d.push_back({n, m});
        ava[n][m] = 1;
    }
    while(!d.empty())
    {
        auto [x, y] = d.front();
        d.pop_front();
        for(int i = 0;i < 4;i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && ma[nx][ny] != '#' && !ava[nx][ny])
            {
                ava[nx][ny] = 1;
                d.push_back({nx, ny});
            }
        }
    }
    for(auto &[x, y] : posg)
    {
        if(!ava[x][y])
        {
            cout << "No\n";
            return;
        }
    }
    for(auto &[x, y] : posb)
    {
        if(ava[x][y])
        {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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