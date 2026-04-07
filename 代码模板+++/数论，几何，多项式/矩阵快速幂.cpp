#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int MOD = 1e9 + 7;

struct Matrix
{
    int n;
    vector<vector<i64>> mat;
    Matrix(int _n) : n(_n)
    {
        mat.assign(n, vector<i64>(n, 0));
    }

    void init()
    {
        for (int i = 0; i < n;i++)
            mat[i][i] = 1;
    }

    Matrix operator*(const Matrix &other) const
    {
        Matrix res(n);
        for (int i = 0; i < n;i++)
        {
            for (int k = 0; k < n;k++)
            {
                i64 r = mat[i][k];
                if(r == 0)
                    continue;
                for (int j = 0; j < n;j++)
                {
                    res.mat[i][j] = (res.mat[i][j] + r * other.mat[k][j]) % MOD;
                }
            }
        }
        return res;
    }
    static Matrix qpow(Matrix a, i64 k)
    {
        Matrix res(a.n);
        res.init();
        while(k > 0)
        {
            if(k & 1)
                res = res * a;
            a = a * a;
            k >>= 1;
        }
        return res;
    }
};



