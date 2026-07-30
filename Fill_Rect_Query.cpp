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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int h, w, q;
    cin >> h >> w >> q;

    vector<vector<pii>> op(h + 1);
    vector<char> letter(q + 1, 'A');
    for (int i = 1; i <= q;i++)
    {
        int r, c;
        char x;
        cin >> r >> c >> x;
        op[r].push_back({c, i});
        letter[i] = x;
    }

    vector<int> best(w + 1, '\0');
    vector<vector<char>> mat(h + 1, vector<char>(w + 1, 'A'));

    for (int i = h; i >= 1;i--)
    {
        for(auto [c, id] : op[i])
            chmax(best[c], id);
        int maxid = 0;
        for (int j = w; j >= 1;j--)
        {
            chmax(maxid, best[j]);
            mat[i][j] = letter[maxid];
        }
    }

    for (int i = 1; i <= h;i++)
    {
        for (int j = 1; j <= w;j++)
            cout << mat[i][j];

        cout << "\n";
    }
}



bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}