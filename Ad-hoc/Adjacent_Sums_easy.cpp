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
constexpr i64 MOD = 998244353, INF = 1e9;

// 非常好的从端点思考的方式，因为对于这题，如果端点已经确定了，整个的贡献就确定了。
// 所以考虑枚举端点情况。
// 这题比较特殊，我们要考虑 flip 的突变情况。
void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(n - 1);
    for (int i = 0;i < n;i++)
        cin >> a[i];
    for (int i = 0; i < n - 1;i++)
        cin >> b[i];

    vector<int> c(n - 1);
    for (int i = 0; i < n - 1;i++)
        c[i] = (a[i] + a[i + 1]) % 2, c[i] ^= b[i];

    // debugarr(b)
    //     debugarr(c)

    int pre = 0;
    int cnt1 = 0, cnt2 = 1;
    for (int i = n - 2; i >= 0;i--)
    {
        int nxt = pre ^ c[i];
        pre = nxt;
        if(nxt == 1)
            cnt1++;
    }

    pre = 1;
    for (int i = n - 2; i >= 0;i--)
    {
        int nxt = pre ^ c[i];
        pre = nxt;
        if(nxt == 1)
            cnt2++;
    }

    cout << min(cnt1, cnt2);
    // int cnt = 0;
    // for (int i = n - 2; i >= 0;i--)
    // {
    //     if(c[i] != b[i])
    //     {
    //         c[i] ^= 1, cnt++;
    //         if(i >= 1)
    //             c[i - 1] ^= 1;
    //     }
    // }

    // for (int i = n - 2; i >= 0;i--)
    // {
    //     if(c[i] != b[i])
    //     {
    //         c[i] ^= 1, cnt++;
    //         if(i >= 1)
    //             c[i - 1] ^= 1;
    //     }
    // }
    // cout << cnt;
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