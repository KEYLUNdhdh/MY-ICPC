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
    int n, m;
    cin >> n >> m;
    vector<int> cnt(3, 0);
    vector<vector<char>> mat(n + 1, vector<char>(m + 1, '\0'));
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= m;j++)
        {
            cin >> mat[i][j];
            if(mat[i][j] == 'R')
                cnt[0]++;
            else if(mat[i][j] == 'G')
                cnt[1]++;
            else
                cnt[2]++;
        }
    }

    if(cnt[0] != cnt[1] || cnt[1] != cnt[2] || cnt[0] != cnt[2])
    {
        debug(n)
        cout << "NO";
        return;
    }

    // list
    int fl = 1, fr = 1;
    int pre = mat[1][1];
    int len = -1;
    for (int i = 1; i <= m;i++)
    {
        if(mat[1][i] != pre)
        {
            fl = 0;
            if(len == -1)
            {
                len = i - 1;
            }
        }
    }

    for (int i = 1; i <= n;i++)
    {
        if(mat[i][1] != pre)
        {
            fr = 0;
            if(len == -1)
            {
                len = i - 1;
            }
        }
    }
    if ((!fr && !fl) || (fr && fl))
    {
        debug(fr)debug(fl)debug(len)
        cout << "NO";
        return;
    }
    debug(fl)debug(len)debug(fr)
    if(!fl)
    {
        char ck = mat[1][1];
        debug(ck)
        for (int i = 1; i <= n;i++)
        {
            for (int j = 1; j <= len;j++)
            {
                if(mat[i][j] != ck)
                {
                    cout << "NO";
                    return;
                }
            }
        }

        ck = mat[1][len + 1];
        debug(ck)
        for (int i = 1; i <= n;i++)
        {
            for (int j = len + 1; j <= 2 * len;j++)
            {
                if(mat[i][j] != ck)
                {
                    cout << "NO";
                    return;
                }
            }
        }

        ck = mat[1][1 + 2 * len];
        debug(ck)
        for (int i = 1; i <= n;i++)
        {
            for (int j = 2 * len + 1; j <= m;j++)
            {
                if(mat[i][j] != ck)
                {
                    cout << "NO";
                    return;
                }
            }
        }
    }
    else
    {
        char ck = mat[1][1];
        debug(ck)
        for (int i = 1; i <= len;i++)
        {
            for (int j = 1; j <= m;j++)
            {
                // debug(mat[i][j])
                if(mat[i][j] != ck)
                {
                    cout << "NO";
                    return;
                }
            }
        }
        debug(ck)
        ck = mat[len + 1][1];
        for (int i = len + 1; i <= 2 * len;i++)
        {
            for (int j = 1; j <= m;j++)
            {
                if(mat[i][j] != ck)
                {
                    cout << "NO";
                    return;
                }
            }
        }
        debug(ck)
        ck = mat[2 * len + 1][1];
        for (int i = 2 * len + 1; i <= n;i++)
        {
            for (int j = 1; j <= m;j++)
            {
                if(mat[i][j] != ck)
                {
                    cout << "NO";
                    return;
                }
            }
        }
    }
    cout << "YES";
    return;
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
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}