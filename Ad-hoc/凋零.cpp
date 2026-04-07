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
const int MOD = 998244353;

void solve()
{
    // vector<int> dx = {-1, 1, 0, 0};
    // vector<int> dy = {0, 0, -1, 1};
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> U(n + 1, vector(n + 1, 0));
    vector<vector<int>> D(n + 1, vector(n + 1, 0));
    vector<vector<int>> L(n + 1, vector(n + 1, 0));
    vector<vector<int>> R(n + 1, vector(n + 1, 0));
    for (int i = 0; i < m;i++)
    {
        int x, y;
        char c;
        cin >> x >> y >> c;
        if(c == 'U')
            U[x][y] += 1;
        else if(c == 'D')
            D[x][y] += 1;
        else if(c == 'L')
            L[x][y] += 1;
        else
            R[x][y] += 1;
    }
    while(q--)
    {
        int cnt = 0;
        int t, x, y;
        cin >> t >> x >> y;
        if(y - t >= 1 && R[x][y - t])
            cnt += R[x][y - t];
        if(y + t <= n && L[x][y + t])
            cnt += L[x][y + t];
        if(x - t >= 1 && D[x - t][y])
            cnt += D[x - t][y];
        if(x + t <= n && U[x + t][y])
            cnt += U[x + t][y];
        cout << cnt << "\n";
    }
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