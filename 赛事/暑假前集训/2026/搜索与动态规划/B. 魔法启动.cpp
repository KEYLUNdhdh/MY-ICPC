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
    i64 n, m;
    cin >> n >> m;

    m <<= 1;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        a[i] <<= 1;
    }

    vector<pll> pre;
    int up = n / 2;
    auto dfs = [&](auto self, int idx, i64 cur, int cnt) -> void
    {
        if(cur > m)
            return;
        if(idx > up)
        {
            pre.push_back({cur, cnt});
            return;
        }
        self(self, idx + 1, cur + a[idx] / 2, cnt + 1);
        self(self, idx + 1, cur + a[idx], cnt);
        self(self, idx + 1, cur, cnt);

        return;
    };

    dfs(dfs, 1, 0, 0);

    sort(pre.begin(), pre.end());
    int idx = 0;
    for(int i = 0;i < pre.size();)
    {
        int sum = pre[i].first;
        pre[idx++] = pre[i];
        while(i < pre.size() && pre[i].first == sum)
            i++;
    }
    pre.resize(idx);
    i64 ans = INF;
    auto dfs2 = [&](auto self, int idx, i64 cur, int cnt) -> void
    {
        if(cur > m || cnt >= ans)
            return;

        if(idx > n)
        {
            i64 re = m - cur;
            if(re < 0 || re > m)
                return;

            auto it = lower_bound(pre.begin(), pre.end(), pll{re, -1});
            if(it != pre.end() && it->first == re)
                chmin(ans, it->second + cnt);
            return;
        }
        self(self, idx + 1, cur + a[idx] / 2, cnt + 1);
        self(self, idx + 1, cur + a[idx], cnt);
        self(self, idx + 1, cur, cnt);
        return;
    };

    dfs2(dfs2, up + 1, 0, 0);

    if(ans != INF)
        cout << ans;
    else
        cout << -1;
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