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
    int n, l;
    cin >> n >> l;

    vector<i64> c(n + 1, 0), s(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> c[i];
        s[i] = s[i - 1] + c[i];
    }

    auto A = [&](int i) -> i128
    {
        return i + s[i];
    };

    auto B = [&](int j) -> i128
    {
        return j + 1 + l + s[j];
    };

    vector<i64> dp(n + 1, 0);
    auto Y = [&](int j) -> i128
    {
        return (i128)dp[j] + B(j) * B(j);
    };

    auto X = [&](int j) -> i128
    {
        return B(j);
    };

    SlopeOpt opt(n, X, Y);
    opt.add(0);

    for (int i = 1; i <= n;i++)
    {
        int j = opt.query(2 * A(i));
        i128 val = A(i) - B(j);
        dp[i] = dp[j] + val * val;

        opt.add(i);
    }

    cout << dp[n];
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