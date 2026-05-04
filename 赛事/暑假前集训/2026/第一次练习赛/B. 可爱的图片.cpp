#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------\n";}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937 rnd(time(0));

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
constexpr int MOD = 998244353, INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    for (int i = 1; i <= n;i++)
        cin >> b[i];
    vector<i64> prefix(n + 1, 0);
    for (int i = 1; i <= n;i++)
        prefix[i] = prefix[i - 1] + b[i];
    sort(a.begin(), a.end());
    i64 x = 0;
    i64 sum = 0;
    i64 pos = lower_bound(prefix.begin(), prefix.end(), n) - prefix.begin();
    if(pos == n + 1)
        pos--;
    debugarr(prefix)
    i64 maxx = -INF;
    i64 ans = -INF;
    while(pos >= 1)
    {
        i64 now = prefix[pos];
        i64 apos = n - now + 1;
        i64 xmax = a[apos];
        chmax(maxx, xmax * pos);
        chmax(ans, maxx);
        pos--;
    }
    cout << ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}