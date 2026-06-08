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

const int MOD = 1e9 + 7;

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
                v = v * a;
            a = a * a;
            k >>= 1;
        }
        return v;
    }
};

void solve()
{
    i64 n, m;
    cin >> n >> m;

    int k;
    cin >> k;

    map<i64, int> mp;
    for (int i = 0;i < k;i++)
    {
        i64 x, y;
        cin >> x >> y;

        mp[x] |= (1 << (y - 1));
    }

    vector<int> val;
    for (int i = 0; i < (1 << m);i++)
    {
        if((i & (i << 1)) == 0)
            val.push_back(i);
    }
    int len = val.size();

    Matrix t(len, len);
    for (int i = 0; i < len;i++)
        for (int j = 0; j < len;j++)
            if((val[i] & val[j]) == 0)
                t[i][j] = 1;

    vector<Matrix> pre;
    pre.reserve(61);
    pre.push_back(t);
    for (int i = 1; i < 61; i++)
        pre.push_back(pre[i - 1] * pre[i - 1]);

    Matrix v(1, len);
    v[0][0] = 1;
    i64 lst = 0;

    for(auto &[x, mask] : mp)
    {
        i64 up = x - lst;
        // v = Matrix::qpow(t, up, v);
        for(int i = 0;i < 61;i++)
        {
            if((up >> i) & 1)
                v = v * pre[i];
        }
        for (int i = 0; i < len;i++)
        {
            if((val[i] & mask) != mask)
                v[0][i] = 0;
        }

        lst = x;
    }

    if(lst < n)
    {
        i64 up = n - lst;
        // v = Matrix::qpow(t, up, v);
        for(int i = 0;i < 61;i++)
        {
            if((up >> i) & 1)
                v = v * pre[i];
        }
    }

    i64 ans = 0;
    for (int i = 0; i < len;i++)
        ans = (ans + v[0][i]) % MOD;

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