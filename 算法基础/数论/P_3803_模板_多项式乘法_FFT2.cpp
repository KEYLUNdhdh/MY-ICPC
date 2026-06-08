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
const int G = 3;

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

struct NTT
{
    vector<i64> rev;

    void transform(vector<i64> &a, int flag)
    {
        int n = a.size();
        for (int i = 0; i < n;i++)  
            if(i < rev[i])
                swap(a[i], a[rev[i]]);

        for (int mid = 1; mid < n;mid <<= 1)
        {
            i64 wn = qpow(G, (MOD - 1) / (mid << 1));
            if(flag == -1)
                wn = qpow(wn, MOD - 2);

            for (int i = 0; i < n;i += (mid << 1))
            {
                i64 w = 1;
                for (int j = 0; j < mid;j++, w = w * wn % MOD)
                {
                    i64 x = a[i + j];
                    i64 y = w * a[i + j + mid] % MOD;
                    a[i + j] = (x + y) % MOD;
                    a[i + j + mid] = (x - y + MOD) % MOD;
                }
            }
        }

        if(flag == -1)
        {
            i64 invN = qpow(n, MOD - 2);
            for (int i = 0; i < n;i++)
                a[i] = a[i] * invN % MOD;
        }
    }

    vector<i64> polyMul(const vector<i64> &A, const vector<i64> &B)
    {
        int n = A.size(), m = B.size();
        int limit = 1, l = 0;

        while(limit < n + m - 1)
        {
            limit <<= 1;
            l++;
        }

        rev.assign(limit, 0);
        for (int i = 0; i < limit;i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (l - 1));

        vector<i64> a(limit, 0), b(limit, 0);
        for (int i = 0; i < n;i++)
            a[i] = A[i];

        for (int i = 0; i < m;i++)
            b[i] = B[i];

        transform(a, 1);
        transform(b, 1);
        for (int i = 0; i < limit;i++)
            a[i] = a[i] * b[i] % MOD;

        transform(a, -1);
        a.resize(n + m - 1);
        return a;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1, 0), b(m + 1, 0);
    for (int i = 0; i <= n;i++)
        cin >> a[i];

    for (int i = 0; i <= m;i++)
        cin >> b[i];

    NTT ntt;
    vector<i64> res = ntt.polyMul(a, b);
    for (int i = 0; i <= n + m;i++)
        cout << res[i] << " ";

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