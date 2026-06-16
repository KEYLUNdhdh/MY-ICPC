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

struct Manacher
{
    string t;
    vector<int> p;
    int maxlen;

    Manacher(const string &s)
    {
        int n = s.length();
        t.assign(2 * n + 3, '#');
        t[0] = '^';
        for (int i = 0; i < n;i++)
            t[i * 2 + 2] = s[i];

        t[n * 2 + 2] = '$';

        int m = t.length();
        p.assign(m, 0);
        int mid = 0, r = 0;
        maxlen = 0;

        for (int i = 1; i < m - 1;i++)
        {
            if(i < r)
                p[i] = min(r - i, p[2 * mid - i]);
            else
                p[i] = 1;
        
            while(t[i - p[i]] == t[i + p[i]])
                p[i]++;

            if(i + p[i] > r)
            {
                mid = i;
                r = i + p[i];
            }

            maxlen = max(maxlen, p[i] - 1);
        }
    }

    int specific(int idx)
    {
        return p[idx * 2 + 2] - 1;
    }
};

void solve()
{
    string s;
    cin >> s;

    Manacher ma(s);

    cout << ma.maxlen;
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