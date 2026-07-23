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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

// 一个数组划分为两个集合，让两个集合各自内部和的乘积最大化
// 子区间乘积最大问题就用 0/1 背包去搞
// 这题本质上是在枚举每个点 u 作为 lca 的贡献，并且每个点的情况是独立的
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> pa(n + 1, 0);

    for (int i = 2; i <= n;i++)
    {
        int p;
        cin >> p;
        pa[i] = p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    vector<int> sz(n + 1, 0);
    i64 ans = 0;
    auto dfs = [&](auto self, int u) -> void
    {
        sz[u] = 1;
        i64 sum = 0;
        vector<i64> tmp;
        for(int v : adj[u])
        {
            if(v == pa[u])
                continue;
            self(self, v);
            sz[u] += sz[v];
            tmp.push_back(sz[v]);
            sum += sz[v];
        }
        // sort(tmp.begin(), tmp.end());
        // if(tmp.size() <= 1)
        //     return;
        vector<int> dp(sum + 1, 0);
        dp[0] = 1, dp[sum] = 1;
        for(i64 k : tmp)
        {
            for (i64 w = sum - k;w >= 0;w--)
                if(dp[w])
                    dp[w + k] = 1;
        }        
        // debugarr(dp)
        // debugarr(tmp)
        i64 res = 0;
        for (int i = 1;i <= sum;i++)
        {
            if(dp[i] && dp[sum - i])
                chmax(res, i * (sum - i));
        }
        ans += res;
    };

    dfs(dfs, 1);
    cout << ans;
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
    // cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    // cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}