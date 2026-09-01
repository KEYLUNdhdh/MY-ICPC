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
    map<char, int> mp;
    for (int i = 0;i < n;i++)
    {
        char c;
        cin >> c;
        mp[c]++;
    }

    if(mp.size() == 1)
    {
        cout << 0;
        return;
    }
    else if(mp.size() == 2)
    {
        int minn = INF;
        for(auto [c, cnt] : mp)
            chmin(minn, cnt);

        cout << minn * 3;
        return;
    }

    vector<int> tmp;
    for(auto [c, cnt] : mp)
        tmp.push_back(cnt);

    sort(tmp.begin(), tmp.end());
    int f = tmp[0], s = tmp[1], t = tmp[2];

    vector<i128> comb(f + 1, -1);
    comb[0] = comb[f] = 1;
    for (int i = 1; i < f;i++)
        comb[i] = comb[i - 1] * (f - i + 1) / i;

    ld lhs = 1.5 * f;
    ld rhs = 0;
    i64 pol = 1ll << f;
    for (int i = 0; i <= f; i++)
    {
        int up = 3 * min(s + i, t + f - i);
        rhs += (ld)comb[i] * up / pol;
    }
    debug(lhs)
    debug(rhs)
    cout << fixed << setprecision(10) <<  lhs + rhs;
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