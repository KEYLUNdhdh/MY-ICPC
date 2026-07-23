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
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
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
constexpr i64 MOD = 1e9 + 7, INF = 1e9;

vector<i64> inv;
void invarr(int n,i64 p)
{
    inv.assign(n + 5, 0);
    inv[1] = 1;
    for (int i = 2; i <= n;i++)
        inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    return;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> ind(n + 1, 0);
    vector<vector<int>> adj(n + 1);
    vector<int> vis(n + 1, 0);

    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        ind[v]++;
    }

    queue<int> q;
    i64 c = 0;
    for (int i = 1; i <= n;i++)
        if(ind[i] == 0)
        {
            // debug(i)
            c++;
            q.push(i);
            while(!q.empty())
            {
                int u = q.front();
                q.pop();
                vis[u] = 1;
                for(int v : adj[u])
                    q.push(v);
            }
        }
    // debug(c)
    // debugarr(vis)
    invarr(c, MOD);
    i64 ans = 0;
    for (int i = 1; i <= c;i++)
        ans = (ans + 1ll * inv[i]) % MOD;

    i64 cnt = 0;
    for (int i = 1; i <= n;i++)
    {
        if(!vis[i])
        {
            cnt++;
            q.push(i);
            while(!q.empty())
            {
                int u = q.front();
                q.pop();
                if(vis[u])
                    break;
                vis[u] = 1;
                for(int v : adj[u])
                    q.push(v);
            }
        }
    }

    ans = (ans + cnt) % MOD;
    cout << ans;
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