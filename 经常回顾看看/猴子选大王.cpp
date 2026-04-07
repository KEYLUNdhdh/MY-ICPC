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
    int n, m;
    cin >> n >> m;
    vector<pll> ind(m + 1, {0, 0});
    for (int i = 1; i <= m;i++)
        ind[i].second = i;
    vector<pll> edge;
    for (int i = 0; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        if(u > v)
            swap(u, v);
        ind[u].first++;
        ind[v].first++;
        edge.push_back({u, v});
    }
    sort(ind.begin(), ind.end());
    sort(edge.begin(), edge.end());
    i64 ans = 0;
    if(ind[m - 1].first != ind.back().first)
    {
        i64 maxx = ind.back().first;
        i64 id = ind.back().second;
        for (int i = m - 1; i >= 1 && ind[i].first == ind[m - 1].first;i--)
        {
            auto &[x, y] = ind[i];
            i64 dis;
            if(y > id)
            {
                auto range = equal_range(edge.begin(), edge.end(), pll{id, y});
                dis = range.second - range.first;
            }
            else
            {
                auto range = equal_range(edge.begin(), edge.end(), pll{y, id});
                dis = range.second - range.first;
            }
            chmax(ans, x + maxx - dis);
        }
        cout << ans;
    }
    else
    {
        i64 maxx = ind.back().first;
        auto lw = lower_bound(ind.begin(), ind.end(), pll{maxx, 0});
        i64 cnt =  ind.end() - lw;
        if(cnt * (cnt - 1) / 2 > n)
            cout << 2 * maxx;
        else
        {
            int l = lw - ind.begin();
            for (int i = l;i <=m;i++)
            {
                for (int j = i + 1; j <= m;j++)
                {
                    int x = ind[i].second;
                    int y = ind[j].second;
                    if(x > y)
                        swap(x, y);
                    auto range = equal_range(edge.begin(), edge.end(), pll{x, y});
                    i64 dis = range.second - range.first;
                    chmax(ans, 2 * maxx - dis);
                }
            }
            cout << ans;
        }
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