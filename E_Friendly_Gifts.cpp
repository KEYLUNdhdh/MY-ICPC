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

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    vector<vector<int>> ava(n + 1, vector<int>(n + 1, 0));
    vector<int> vis;
    for (int i = 1; i <= n;i++)
    {
        int maxx = a[i], minn = a[i];
        vis.assign(n + 1, 0);
        for (int j = i; j <= n;j++)
        {
            if(vis[a[j]])
                break;
            vis[a[j]] = 1;
            chmax(maxx, a[j]);
            chmin(minn, a[j]);
            if(j - i == maxx - minn)
                ava[minn][maxx] = 1;
        }
    }

    for (int ans = n / 2; ans >= 1;ans--)
    {
        for (int l = 1;;l++)
        {
            int r = l + ans - 1;
            int ll = l + ans;
            int rr = l + 2 * ans - 1;
            if(rr > n)
                break;

            if(ava[l][r] && ava[ll][rr])
            {
                cout << ans << "\n";
                return;
            }
        }
    }
    cout << 0 << "\n";
}

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