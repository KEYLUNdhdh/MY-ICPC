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
    vector<vector<char>> mat(n + 1, vector<char>(n + 1, '\0'));
    for (int i = 1; i <= n;i++)
        for (int j = 1; j <= n;j++)
            cin >> mat[i][j];

    auto check = [&](int i, int j) -> bool
    {
        if(mat[i][j - 1] == mat[i - 1][j])
            return true;
        return false;
    };

    int f = 0;
    int pos = -1;
    for (int i = 2; i <= n;i++)
    {
        if(check(i, i))
        {
            f = 1;
            pos = i;
            break;
        }
    }

    // if(pos != -1)
    // {
        // cout << "YES\n";
        // int l = pos - 1, r = pos;
        // for (int i = 1; i <= m + 1;i++)
        //     if(i & 1)
        //         cout << l << " ";
        //     else
        //         cout << r << " ";
        // cout << "\n";
    // }

    // for (int i = 1; i <= n;i++)
    // {
    //     for (int j = 1; j <= n;j++)
    //         cerr << mat[i][j];
    //     cerr << "\n";
    // }
    int l = -1, r = -1;
    for (int i = 1; i <= n;i++)
        for (int j = i + 1; j <= n;j++)
        {
            // debug(i)debug(j)
            if(mat[i][j] == mat[j][i])
            {
                l = i, r = j;
                // debug(l)debug(r)
                break;
            }
        }

    if(l != -1 && r != -1)
    {
        cout << "YES\n";
        for (int i = 1; i <= m + 1;i++)
            if(i & 1)
                cout << l << " ";
            else
                cout << r << " ";
        cout << "\n";
    }
    else
    {
        if(m % 2)
        {
            l = 1, r = 2;
            cout << "YES\n";
            for (int i = 1; i <= m + 1;i++)
                if(i & 1)
                    cout << l << " ";
                else
                    cout << r << " ";
            cout << "\n";
        }
        else
        {
            if(n == 2)
            {
                cout << "NO\n";
                return;
            }
            vector<int> p = {1, 2, 3};
            do
            {
                int a = p[0], b = p[1], c = p[2];
                if(mat[a][b] == mat[b][c])
                {
                    cout << "YES\n";
                    int mid = m / 2;
                    for (int i = 0; i <= mid; i++)
                    {
                        if ((mid - i) % 2 == 0)
                            cout << b << " ";
                        else
                            cout << a << " ";
                    }

                    for (int i = mid + 1; i <= m; i++)
                    {
                        if ((i - mid) % 2 == 0)
                            cout << b << " ";
                        else
                            cout << c << " ";
                    }
                    cout << "\n";
                    return;
                }
            } while (next_permutation(p.begin(), p.end()));
        }
    }

}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}
// * b b
// a * a
// a b *
// * 
//abababa