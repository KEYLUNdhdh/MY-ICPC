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

const int MOD = 1e9 + 6;

struct Matrix
{
    int n, m;
    vector<i64> mat;

    Matrix () : n(0), m(0) {}
    Matrix(int _n, int _m) : n(_n), m(_m)
    {
        mat.assign(1ll * n * m, 0);
    }
    i64* operator[](int i)
    {
        return mat.data() + 1ll * i * m;
    }

    const i64* operator[](int i) const
    {
        return mat.data() + 1ll * i * m;
    }

    i64& at(int i, int j)
    {
        return mat[1ll * i * m + j];
    }

    const i64& at(int i, int j) const
    {
        return mat[1ll * i * m + j];
    }

    Matrix operator*(const Matrix &other) const
    {
        assert(m == other.n);

        Matrix res(n, other.m);
        for (int i = 0; i < n;i++)
        {
            for (int k = 0; k < m;k++)
            {
                i64 r = (*this)[i][k];
                if(r == 0)
                    continue;
                for (int j = 0; j < other.m;j++)
                {
                    res[i][j] = (res[i][j] + r * other[k][j]) % MOD;
                    if(res[i][j] < 0)
                        res[i][j] += MOD;
                }
            }
        }
        return res;
    }

    static Matrix identity(int n)
    {
        Matrix I(n, n);
        for (int i = 0; i < n;i++)
            I[i][i] = 1;
        return I;
    }

    static Matrix qpow(Matrix a, i64 k, Matrix v)
    {
        while (k > 0)
        {
            if (k & 1)
                v = a * v;
            a = a * a;
            k >>= 1;
        }
        return v;
    }
};

template<class T>
constexpr T qpow(T a,T b,T MOD)
{
    T res = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

void solve()
{
    i64 n, c;
    vector<i64> f(3);
    cin >> n >> f[0] >> f[1] >> f[2] >> c;

    if(n <= 3)
    {
        cout << f[n - 1] % (MOD + 1);
        return;
    }

    Matrix t(3, 3);
    t[0][0] = 1, t[0][1] = 1, t[0][2] = 1, t[1][0] = 1, t[2][1] = 1;

    vector<i64> pow(3);
    for (int i = 0; i < 3;i++)
    {
        int cur = f[i];
        Matrix v(3, 1);
        v[2 - i][0] = 1;

        i64 up = n - 3;
        v = Matrix::qpow(t, up, v);
        pow[i] = v[0][0];
    }

    Matrix tc(5, 5);
    tc[0][0] = tc[0][1] = tc[0][2] = tc[1][0] = tc[2][1] = tc[4][4] = tc[3][3] = tc[3][4] = 1;
    tc[0][3] = 2;
    tc[0][4] = -6;
    Matrix vc(5, 1);
    vc[3][0] = 4;
    vc[4][0] = 1;
    i64 up = n - 3;
    vc = Matrix::qpow(tc, up, vc);

    i64 powc = vc[0][0];
    i64 mod = 1e9 + 7;

    i64 ans = 1;
    for (int i = 0; i < 3;i++)
        ans = (ans * qpow(f[i], pow[i], mod)) % mod;

    ans = (ans * qpow(c, powc, mod)) % mod;

    cout << ans;
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