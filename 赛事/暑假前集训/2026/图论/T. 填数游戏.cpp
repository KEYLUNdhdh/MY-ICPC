#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 998244353, INF = 1e9;

struct DiffConstraint
{
    int n;

    vector<vector<pll>> adj;
    vector<i64> dist;
    vector<int> count;
    vector<int> inQueue;

    DiffConstraint(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<pll>());
        dist.assign(n + 1, 0);
        count.assign(n + 1, 0);
        inQueue.assign(n + 1, 0);
    }

    void addEdge(int u, int v, i64 w) 
    {
        adj[u].push_back({v, w});
    }

    bool sol()
    {
        queue<int> q;

        for (int i = 1; i <= n;i++)
        {
            dist[i] = 0;
            inQueue[i] = 1;
            count[i] = 1;
            q.push(i);
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            inQueue[u] = 0;

            for(const auto &[v, w] : adj[u])
            {
                if(dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;

                    if(!inQueue[v])
                    {
                        q.push(v);
                        inQueue[v] = 1;
                        count[v]++;

                        if(count[v] >= n)
                            return false;
                    }
                }
            }
        }
        return true;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    DiffConstraint diff(n + m);

    vector<vector<i64>> f(n + 1, vector<i64>(m + 1, 0));
    vector<vector<i64>> s(n, vector<i64>(m, 0));

    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= m;j++)
            cin >> f[i][j];

    for (int i = 1; i < n;i++)
        for (int j = 1; j < m;j++)
            cin >> s[i][j];

    vector<vector<i64>> ans(n + 1, vector<i64>(m + 1, 0));
    for (int i = 2; i <= n;i++)
        for (int j = 2; j <= m;j++)
            ans[i][j] = s[i - 1][j - 1] - ans[i - 1][j] - ans[i][j - 1] - ans[i - 1][j - 1];

    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= m;j++)
        {
            int flag = ((i + j) % 2 == 0) ? 1 : -1;
            if(flag == 1)
            {
                diff.addEdge(i, n + j, f[i][j] - ans[i][j]);
                diff.addEdge(n + j, i, ans[i][j]);
            }
            else
            {
                diff.addEdge(n + j, i, f[i][j] - ans[i][j]);
                diff.addEdge(i, n + j, ans[i][j]);
            }
        }

    if(diff.sol())
    {
        cout << "Yes\n";
        for (int i = 1; i <= n;i++)
        {
            for (int j = 1; j <= m;j++)
            {
                int flag = ((i + j) % 2 == 0) ? 1 : -1;
                if(flag == 1)
                    cout << ans[i][j] + diff.dist[n + j] - diff.dist[i] << " ";
                else
                    cout << ans[i][j] - diff.dist[n + j] + diff.dist[i] << " ";
            }
            cout << "\n";
        }
    }
    else
        cout << "No\n";
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