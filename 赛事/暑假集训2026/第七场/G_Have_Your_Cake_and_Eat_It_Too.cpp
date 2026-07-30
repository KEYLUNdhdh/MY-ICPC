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

void solve()
{
    int n;
    cin >> n;
    i64 tot = 0;
    vector<i64> a(n + 1, 0), b(n + 1, 0), c(n + 1, 0);
    vector<vector<int>> nxt(3, vector<int>(n + 1, -1));
    vector<vector<i64>> p(3, vector<i64>(n + 1, 0));

    for (int i = 1; i <= n;i++)
        cin >> a[i], tot += a[i], p[0][i] = p[0][i - 1] + a[i];    
    for (int i = 1; i <= n;i++)
        cin >> b[i], p[1][i] = p[1][i - 1] + b[i];
    for (int i = 1; i <= n;i++)
        cin >> c[i], p[2][i] = p[2][i - 1] + c[i];

    i64 lb = (tot + 3 - 1) / 3ll;
    vector<pii> ans(3);
    for (int k = 0; k < 3;k++)
    {
        for (int i = 1; i <= n;i++)
        {
            auto it = lower_bound(p[k].begin(), p[k].end(), lb + p[k][i - 1]) - p[k].begin();
            if(it <= n)
                nxt[k][i] = it + 1;
        }
    }

    vector<int> order = {0, 1, 2};
    for (int pp = 1; pp <= 6;pp++)
    {
        int p1 = order[0], p2 = order[1], p3 = order[2];
        int s1 = 1;
        int s2 = nxt[p1][s1];
        int s3 = nxt[p2][s2];
        if(s2 != -1 && s3 != -1 && s3 <= n && s2 - 1 >= s1 && s3 - 1 >= s2 && n >= s3 && p[p3][n] - p[p3][s3 - 1] >= lb)
        {
            ans[p1].first = s1, ans[p1].second = s2 - 1, ans[p2].first = s2, ans[p2].second = s3 - 1, ans[p3].first = s3, ans[p3].second = n;
            for (int i = 0; i < 3;i++)
                cout << ans[i].first << " " << ans[i].second << " ";
            cout << "\n";
            return;
        }
        next_permutation(order.begin(), order.end());
    }
    cout << -1 << "\n";
}

bool ED;
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