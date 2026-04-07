#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

const int MOD = 1e9 + 7;

struct Matrix
{
    int n;
    vector<vector<i64>> mat;
    // 构造函数，初始化大小并全赋为 0
    Matrix(int _n) : n(_n)
    {
        mat.assign(n, vector<i64>(n, 0));
    }
    // 将当前矩阵化为单位矩阵 (相当于数字里的 1)
    void init()
    {
        for (int i = 0; i < n;i++)
            mat[i][i] = 1;
    }
    // 运算符重载：定义两个矩阵相乘
    //仅限n * n
    Matrix operator*(const Matrix &other) const
    {
        Matrix res(n);
        for (int i = 0; i < n;i++)
        {
            for (int k = 0; k < n;k++)
            {
                i64 r = mat[i][k];
                if(r == 0)
                    continue;// 剪枝：如果是 0 就没必要去乘这一整行了
                for (int j = 0; j < n;j++)
                {
                    // 注意取模防溢出
                    res.mat[i][j] = (res.mat[i][j] + r * other.mat[k][j]) % MOD;
                }
            }
        }
        return res;
    }
    static Matrix qpow(Matrix a, i64 k)
    {
        Matrix res(a.n);
        res.init();// 结果矩阵初始化为单位矩阵 I
        //快速幂模板
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



