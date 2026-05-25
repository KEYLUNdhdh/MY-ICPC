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
const u64 MASK = rnd();

struct TreeHasher
{
    static u64 shift(u64 x)
    {
        x ^= MASK;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        x ^= MASK;
        return x;
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<u64> hash(n + 1, 0);
    map<u64, i64> mp;
    auto dfs = [&](auto self, int u, int p) -> u64
    {
        hash[u] = 1;
        for(int v : adj[u])
        {
            if(v == p)
                continue;

            hash[u] += TreeHasher::shift(self(self, v, u));
        }
        return hash[u];
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i <= n;i++)
        mp[hash[i]]++;
    cout << mp.size();
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