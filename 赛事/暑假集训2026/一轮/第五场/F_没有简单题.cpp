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

constexpr int MAXN = 2005;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    int tot = n - k + 1;
    vector<vector<int>> da(n + 1, vector<int>(n + 2, 0));
    vector<vector<int>> db(n + 1, vector<int>(n + 2, 0));
    
    auto add = [&](int x, int l, int r, int a, int b) -> void
    {
        l = max(l, 1);
        r = min(r, tot);

        if(l > r)
            return;

        da[x][l] += a;
        da[x][r + 1] -= a;

        db[x][l] += b;
        db[x][r + 1] -= b;
    };

    for (int id = 1; id <= m; id++)
    {
        int l, r;
        cin >> l >> r;

        int len = r - l + 1;
        int q = min(k, len);

        for (int x = 1; x <= tot; x++)
        {
            int L = max(l, x);
            int R = min(r, x + k - 1);

            int c = max(0, R - L + 1);

            
            add(x, 1, tot, 0, c);

            if(c == q)
                continue;

            int A = l - k + c;
            int B = r + 1 - c;
            int Q = q - c;

            
            add(x, A + 1, A + Q - 1, 1, -A);
            add(x, A + Q, B - Q, 0, Q);
            add(x, B - Q + 1, B - 1, -1, B);
        }
    }

    i64 ans = 0;

    for (int x = 1; x <= tot; x++)
    {
        i64 a = 0;
        i64 b = 0;

        for (int y = 1; y <= tot; y++)
        {
            a += da[x][y];
            b += db[x][y];

            chmax(ans, a * y + b);
        }
    }

    cout << ans << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}