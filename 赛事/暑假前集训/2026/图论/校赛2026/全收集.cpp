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
//发现合成出的物品代价不低于每个材料的代价，所以⽤优先队列每次取出当前已知最低代价的物品，将他的代价加⼊答案，再遍历他参与的合成⽅案，若所有原料的最低代价都确定则更新合成物品的代价，
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    vector<pll> len(m + 1, {0, 0});
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m;i++)
    {
        int y, l;
        cin >> y >> l;
        len[i].second = l;
        len[i].first = y;
        for (int j = 0; j < l;j++)
        {
            int x;
            cin >> x;
            adj[x].push_back(i);
        }
    }
    vector<i64> costpei(m + 1, 0);
    vector<int> cost(n + 1, 0);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for (int i = 1; i <= n;i++)
    {
        pq.push({a[i], i});
    }
    while(!pq.empty())
    {
        auto [x, y] = pq.top();
        pq.pop();
        if(cost[y] > 0)
            continue;
        cost[y] = x;
        for(int k : adj[y])
        {
            auto &[a, b] = len[k];
            costpei[k] += x;
            b--;
            if(b == 0)
            {
                pq.push({costpei[k], a});
            }
        }
    }
    i64 ans = 0;
    for (int i = 1; i <= n;i++)
        ans += cost[i];
    cout << ans << "\n";
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