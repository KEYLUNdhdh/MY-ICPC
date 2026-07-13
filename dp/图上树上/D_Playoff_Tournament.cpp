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
    int k;
    cin >> k;
    string s;
    cin >> s;
    int n = s.length();
    reverse(s.begin(), s.end());
    s = "*" + s;

    vector<int> vals(n + 1, 0);
    auto build = [&](auto self, int cur) -> void
    {
        if(cur * 2 > n)
        {
            vals[cur] = (s[cur] == '?') ? 2 : 1;
            return;
        }

        self(self, cur << 1);
        self(self, cur << 1 | 1);

        if(s[cur] == '?')
            vals[cur] = vals[cur << 1] + vals[cur << 1 | 1];
        else if(s[cur] == '0')
            vals[cur] = vals[cur << 1 | 1];
        else
            vals[cur] = vals[cur << 1];
        return;
    };

    build(build, 1);
    int q;
    cin >> q;

    while(q--)
    {
        int p;
        char c;
        cin >> p >> c;
        p = n - p + 1;
        s[p] = c;
        int cur = p;
        while(cur > 0)
        {
            if(cur * 2 > n)
            {
                vals[cur] = (s[cur] == '?') ? 2 : 1;
                cur /= 2;
                continue;
            }
            if(s[cur] == '?')
                vals[cur] = vals[cur << 1] + vals[cur << 1 | 1];
            else if(s[cur] == '0')
                vals[cur] = vals[cur << 1 | 1];
            else
                vals[cur] = vals[cur << 1];
            cur /= 2;
        }
        cout << vals[1] << "\n";
    }
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