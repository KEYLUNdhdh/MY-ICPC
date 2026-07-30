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
// bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

struct q
{
    i64 a, b;
    int id;
};

void solve()
{
    int n;
    cin >> n;

    vector<i64> w(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> w[i];

    int lb = sqrt(n);
    int num;cin >> num;
    vector<i64> ans(num, 0);
    vector<q> query;
    for (int i = 0; i < num;i++)
    {
        i64 a, b;
        cin >> a >> b;
        if(b > lb)
        {
            i64 res = 0;
            for (int i = a; i <= n;i += b)
                res += w[i];
            ans[i] = res;
        }
        else
            query.push_back({a, b, i});
    }

    sort(query.begin(), query.end(), [](q p, q q){return p.b < q.b;});
    vector<i64> dp(n + 1, 0);
    i64 curb = 0;
    for (int i = 0; i < query.size();i++)
    {
        auto &[a, b, id] = query[i];
        if(b == curb)
            ans[id] = dp[a];
        else
        {
            curb = b;
            for (int i = n; i >= 1;i--)
                if(i + b > n)
                    dp[i] = w[i];
                else
                    dp[i] = w[i] + dp[i + b];
            ans[id] = dp[a];
        }
    }
    for(i64 k : ans)
        cout << k << "\n";
    

}

// bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}