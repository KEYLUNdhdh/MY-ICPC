#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";   \
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
    int n, k;
    cin >> n >> k;
    vector<i64> v(n + 1, 0);
    vector<i64> prefix(n + 1, 0);
    i64 sum = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> v[i];
        prefix[i] = prefix[i - 1] + v[i];
    }
    if(n == 1)
    {
        cout << v[1] + k - 1 << "\n";
        return;
    }
    if(k < n)
    {
        for (int i = k; i <= n;i++)
            chmax(sum, prefix[i] - prefix[i - k]);
        debug(sum)
        cout << sum + 1ll * k * (k - 1) / 2 << "\n";
    }
    else
    {
        sum = prefix[n] - prefix[0];
        // debug(sum)
        sum += 1ll * n * (n - 1) / 2;
        k -= n;
        sum += 1ll * k * n;
        cout << sum << "\n";
    }

}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}