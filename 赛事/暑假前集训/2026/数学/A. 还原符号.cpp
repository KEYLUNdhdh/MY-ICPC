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

template<class T>
T qpow(T a,T b,T MOD)
{
    T res = 1;
    a = (a % MOD + MOD) % MOD;

    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

template <class T>
T inv(T a,T p)
{
    return qpow(a, p - 2, p);
}

struct Gauss
{
    Gauss() {}
    
    i64 calc(vector<vector<i64>> a)
    {
        int n = a.size();
        i64 det = 1;

        for (int i = 0; i < n;i++)
        {
            int pivot = i;
            for (int j = i;j < n;j++)
            {
                if(a[j][i] != 0)
                {
                    pivot = j;
                    break;
                }
            }

            if(a[pivot][i] == 0)
                return 0;

            if(pivot != i)
            {
                swap(a[i], a[pivot]);
                det = (MOD - det) % MOD;
            }

            det = det * a[i][i] % MOD;
            i64 in = inv(a[i][i], MOD);

            for (int j = i + 1; j < n; j++)
            {
                if(a[j][i] == 0)
                    continue;

                i64 factor = a[j][i] * in % MOD;
                for (int k = i; k < n;k++)
                {
                    a[j][k] = (a[j][k] - factor * a[i][k]) % MOD;
                    if(a[j][k] < 0)
                        a[j][k] += MOD;
                }
            }
        }
        return (det % MOD + MOD) % MOD;
    }
};

void solve()
{
    int n;
    cin >> n;
    string tmp;
    cin >> tmp;
    i64 det = 0;
    for (int i = 0; i < tmp.size();i++)
        det = (det * 10 + tmp[i] - '0') % MOD;

    vector<vector<i64>> a(n, vector<i64>(n));
    for (int i = 0; i < n;i++)
        for (int j = 0; j < n;j++)
            cin >> a[i][j];

    Gauss gauss;

    i64 res = gauss.calc(a);

    if(res == det)
        cout << "+\n";
    else
        cout << "-\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}