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
// https://codeforces.com/gym/706139
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
    vector<int> a(n + 1, 0);
    vector<vector<int>> p(32, vector<int>(n + 1, 0));
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        for (int k = 0; k <= 31;k++)
            p[k][i] = p[k][i - 1] ^ (((1ll << k) & a[i]) >> k);
    }

    vector<vector<i64>> sum0(32, vector<i64>(n + 1, 0));
    vector<vector<i64>> sum1(32, vector<i64>(n + 1, 0));
    vector<vector<int>> cnt0(32, vector<int>(n + 1, 0));
    vector<vector<int>> cnt1(32, vector<int>(n + 1, 0));
    for (int i = 0; i <= 31; i++)
    {
        cnt0[i][0] = 1;
        for (int j = 1; j <= n;j++)
        {
            if(p[i][j] == 1)
            {
                sum1[i][j] = sum1[i][j - 1] + j;
                sum0[i][j] = sum0[i][j - 1];
                cnt0[i][j] = cnt0[i][j - 1];
                cnt1[i][j] = cnt1[i][j - 1] + 1;
            }
            else
            {
                sum1[i][j] = sum1[i][j - 1];
                sum0[i][j] = sum0[i][j - 1] + j;
                cnt0[i][j] = cnt0[i][j - 1] + 1;
                cnt1[i][j] = cnt1[i][j - 1];
            }
        }
    }

    i64 ans = 0;
    for (int i = 0; i <= 31;i++)
    {
        for (i64 r = 1; r <= n;r++)
        {
            if(p[i][r] == 1)
                ans = (ans + ((r * cnt0[i][r] - sum0[i][r]) % MOD + MOD) % MOD * (i64)pow(2, i) % MOD) % MOD;
            else
                ans = (ans + ((r * cnt1[i][r] - sum1[i][r]) % MOD + MOD) % MOD * (i64)pow(2, i) % MOD) % MOD;
        }
    }
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