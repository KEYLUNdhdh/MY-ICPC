#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

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

const i64 MOD = 998244353;

struct Gauss
{
    Gauss() {}
    
    // 传入一个 n*n 的矩阵，返回其行列式对 mod 取模的结果
    i64 calc(vector<vector<i64>> a)
    {
        int n = a.size();
        i64 det = 1;
        
        for (int i = 0; i < n;i++)
        {
            // 1. 找当前列的主元 (不需要找绝对值最大，只要非零即可)
            int pivot = i;
            for (int j = i;j < n;j++)
            {
                if(a[j][i] != 0)
                {
                    pivot = j;
                    break;
                }
            }

            // 2. 如果这一列全为 0，说明矩阵不满秩，行列式直接为 0
            if(a[pivot][i] == 0)
                return 0;

            // 3. 交换行。线性代数基本定理：交换两行，行列式乘 -1
            if(pivot != i)
            {
                swap(a[i], a[pivot]);
                det = (MOD - det) % MOD;
            }

            // 4. 将当前对角线元素乘入结果中
            det = det * a[i][i] % MOD;
            i64 in = inv(a[i][i], MOD);// 求对角线元素的逆元

            // 5. 仅向下消元，构造上三角矩阵
            for (int j = i + 1; j < n; j++)
            {
                if(a[j][i] == 0)
                    continue;

                // factor = 目标行首元素 / 对角线元素
                i64 factor = a[j][i] * in % MOD;// 必须用逆元来代替除法

                // 从第 i 列开始向右减，因为第 i 列前面的已经是 0 了
                for (int k = i; k < n;k++)
                {
                    // 第 j 行 = 第 j 行 - 第 i 行 * factor
                    a[j][k] = (a[j][k] - factor * a[i][k]) % MOD;
                    if(a[j][k] < 0)
                        a[j][k] += MOD;// 防负数取模
                }
            }
        }
        return (det % MOD + MOD) % MOD;
    }
};