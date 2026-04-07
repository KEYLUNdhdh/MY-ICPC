#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
//矩阵不变量 黑白染色
void solve()
{
    int n;
    cin >> n;
    if(n == 1)
    {
        cout << "Yes";
        return;
    }
    vector<vector<i64>> a(n + 1, vector<i64>(n + 1, 0));
    i64 sumh = 0, sumb = 0;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            cin >> a[i][j];
            if((i + j) % 2 == 1)
                sumb += a[i][j];
            else
                sumh += a[i][j];
        }
    }
    // debug(sumh);
    // debug(sumb);
    i64 cnth = (n *n + 1) / 2;
    i64 cntb = 1ll * n * n - cnth;
    if((sumb + sumh) % (n * n) != 0)
    {
        cout << "No";
        return;
    }
    else if(sumb % cntb != 0 || sumh & cnth != 0)
    {
        cout << "No";
        return;
    }
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= n;j++)
        {
            a[i][j] = (a[i][j] % 2 + 2) % 2;
        }
    for (int i = 1; i <= n - 1;i++)
    {
        for (int j = 1; j <= n - 1; j++)
        {
            if(a[i][j] % 2)
            {
                a[i][j] ^= 1;
                a[i + 1][j] ^= 1;
                a[i][j + 1] ^= 1;
                a[i + 1][j + 1] ^= 1;
            }
        }
    }
    for (int i = 1; i <= n;i++)
    {
        if(a[i][n] % 2 == 1 || a[n][i] % 2 == 1)
        {
            cout << "No";
            return;
        }
    }
    cout << "Yes";
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