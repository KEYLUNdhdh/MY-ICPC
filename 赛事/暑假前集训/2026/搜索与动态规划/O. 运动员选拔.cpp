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


void solve()
{
    int n, k;
    cin >> n >> k;

    i64 ans = 0;
    i64 tmp = 0;
    i64 all = 0;
    vector<i64> a(n + 1, 0);
    vector<int> vis(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        all ^= a[i];
    }
    int dir = min(k, n - k);
    int rev = (dir == n - k) ? 1 : 0;
    auto dfs = [&](auto self, int cnt) -> void
    {
        if(rev && cnt == n - k)
        {
            chmax(ans, all ^ tmp);
            return;
        }
        else if(!rev && cnt == k)
        {
            chmax(ans, tmp);
            return;
        }
        for (int i = 1; i <= n;i++)
        {
            if (vis[i])
                continue;

            vis[i] = 1;
            tmp ^= a[i];
            self(self, cnt + 1);
            vis[i] = 0;
            tmp ^= a[i];
        }
    };

    dfs(dfs, 0);

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