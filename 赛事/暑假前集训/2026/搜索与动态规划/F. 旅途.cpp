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
constexpr i64 MOD = 998244353, INF = 2e18;

template <typename F1, typename F2>
struct SlopeOpt
{
    int head = 0, tail = -1;
    vector<int> q; 
    F1 X; 
    F2 Y;

    SlopeOpt(int max_nodes, F1 xFn, F2 yFn) : X(xFn), Y(yFn) 
    {
        q.resize(max_nodes + 1);
    }

    bool bad(int j1, int j2, int j3) 
    {
        i128 y1 = Y(j1), y2 = Y(j2), y3 = Y(j3);
        i128 x1 = X(j1), x2 = X(j2), x3 = X(j3);
        return (y2 - y1) * (x3 - x2) >= (y3 - y2) * (x2 - x1);
    }

    int query(i128 k) 
    {
        while (head < tail) 
        {
            i128 y0 = Y(q[head]), y1 = Y(q[head + 1]);
            i128 x0 = X(q[head]), x1 = X(q[head + 1]);
            if (y1 - y0 <= k * (x1 - x0)) 
                head++;
            else 
                break;
        }
        return q[head];
    }

    void add(int i) 
    {
        while (head < tail && bad(q[tail - 1], q[tail], i))
            tail--;

        q[++tail] = i;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<i64> a(n + 1, 0), prefix(n + 1 ,0);
    i64 sum = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        sum += a[i];
        prefix[i] = a[i] + prefix[i - 1];
    }

    vector<vector<i64>> dp(n + 1, vector<i64>(m + 1, INF));
    dp[0][0] = 0;

    for (int j = 1; j <= m;j++)
    {
        auto Y = [&](int k) -> i128
        {
            return (i128)dp[k][j - 1] + prefix[k] * prefix[k];
        };

        auto X = [&](int k) -> i128
        {
            return prefix[k];
        };

        SlopeOpt opt(n, X, Y);

        opt.add(j - 1);
        for (int i = j; i <= n;i++)
        {
            int k = opt.query(2 * prefix[i]);
            dp[i][j] = dp[k][j - 1] + (prefix[i] - prefix[k]) * (prefix[i] - prefix[k]);

            // if(dp[i][j - 1] != INF)
            opt.add(i);
        }
    }
    cout << dp[n][m] * m - sum * sum;
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