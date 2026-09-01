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
    i64 n, k;
    cin >> n >> k;

    vector<i64> lim(k + 1, 0);
    vector<i64> ans(k + 1, 0);

    vector<pii> pos;
    for (int i = 1; i <= k;i++)
    {
        cin >> lim[i];
        pos.push_back({lim[i], i});
    }
    sort(pos.begin(), pos.end());
    i64 cur = n;
    for (int i = 1; i <= k;i++)
    {
        i64 curlim = pos[i - 1].first;
        i64 curpos = pos[i - 1].second;
        i64 left = k - i + 1;
        i64 best = cur / left;
        if(best > curlim)
            best = curlim;
        ans[curpos] = best;
        cur -= best;
    }

    for (int i = 1; i <= k;i++)
        cout << ans[i] << " ";
    cout << "\n";
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