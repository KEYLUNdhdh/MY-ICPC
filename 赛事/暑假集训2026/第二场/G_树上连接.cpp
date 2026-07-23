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

bool ST;
void solve()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    vector<int> cnt(1e6 + 1, 0);
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    for (int i = 1; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto dfs = [&](auto self, int u, int p) -> void 
    {
        if(p != 0)
        {
            cnt[a[p]]++;
            int g = gcd(a[p], a[u]);
            cnt[g]--;
        }
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            self(self, v, u);
        }
    };

    dfs(dfs, 1, 0);
    vector<i64> ans(k + 1, 0);
    for (int i = 1; i <= k;i++)
    {
        if(a[1] % i)
            ans[i]++;   
        for (int j = 1; i * j <= 1e6;j++)
            ans[i] += cnt[i * j];
    }

    for (int i = 1; i <= k;i++)
        cout << ans[i] << " ";
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}