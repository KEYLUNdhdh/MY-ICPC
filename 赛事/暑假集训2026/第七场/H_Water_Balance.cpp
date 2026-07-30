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
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    vector<pair<i64, int>> stk;
    for (int i = 1; i <= n;i++)
    {
        if(stk.empty())
        {
            stk.push_back({a[i], 1});
            continue;
        }

        i64 ave = a[i];
        stk.push_back({a[i], 1});
        while(stk.size() >= 2)
        {
            auto [sum1, cnt1] = stk.back();
            stk.pop_back();
            auto [sum2, cnt2] = stk.back();
            stk.pop_back();
            if(sum1 * cnt2 <= sum2 * cnt1)
                stk.push_back({sum1 + sum2, cnt1 + cnt2});
            else
            {
                stk.push_back({sum2, cnt2});
                stk.push_back({sum1, cnt1});
                break;
            }
        }
    }

    for(auto [sum, cnt] : stk)
    {
        ld ave = (ld)sum / (ld)cnt;
        for (int i = 0; i < cnt;i++)
            cout << fixed << setprecision(12) << ave << "\n";
    }

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
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}