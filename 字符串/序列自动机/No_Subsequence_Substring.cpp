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
    string s;
    cin >> s;

    int n = s.size();
    s = "*" + s;
    string p;
    cin >> p;
    vector<vector<int>> f(n + 1, vector<int>(26, -1));
    vector<int> lst(26, -1);
    for (int i = n; i >= 0;i--)
    {
        f[i] = lst;
        int idx = s[i] - 'a';
        if(idx < 26 && idx >= 0)
            lst[idx] = i;
    }
    // debug(n)
    i64 ans = 1ll * (n + 1) * n / 2;
    for (int i = 1; i <= n;i++)
    {
        int j = 0;
        int pos = i - 1;

        while(j < p.size())
        {
            int idx = p[j] - 'a';

            if(f[pos][idx] != -1)
            {
                pos = f[pos][idx];
                j++;
            }
            else
                break;
        }

        if(j == p.size())
            ans -= n - pos + 1;
    }

    cout << ans;
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