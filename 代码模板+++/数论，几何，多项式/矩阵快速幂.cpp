#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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