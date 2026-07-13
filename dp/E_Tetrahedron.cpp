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
constexpr i64 MOD = 1e9 + 7, INF = 1e9 + 7;

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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

    static Matrix qpow(Matrix a, i64 k)
    {
        Matrix res = Matrix::identity(a.n);
        while (k > 0)
        {
            if (k & 1)
                res = res * a;
            a = a * a;
            k >>= 1;
        }
        return res;
    }
};

// 矩阵快速幂优化.
void solve()
{
    int n;
    cin >> n;

    Matrix mat(4, 4);
    mat[0][1] = 1, mat[0][2] = 1, mat[0][3] = 1, mat[1][0] = 1, mat[1][2] = 1, mat[1][3] = 1, mat[2][0] = 1, mat[2][1] = 1, mat[2][3] = 1, mat[3][0] = 1, mat[3][1] = 1, mat[3][2] = 1;
    Matrix res = Matrix::qpow(mat, n);
    i64 ans = 0;

    cout << res[3][3];
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