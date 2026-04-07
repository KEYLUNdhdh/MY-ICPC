#include <bits/stdc++.h>
using namespace std;
using db = double;
struct Gauss
{
    static constexpr db EPS = 1e-8;// 精度容差
    //a n * (n + 1)
    // 传入增广矩阵 a，大小为 n * (n + 1)
    // 返回解向量。如果矩阵不满秩（无唯一解/无解），返回空的 vector
    static int solve(vector<vector<db>> &a,vector<db> &res)
    {
        int n = a.size();
        int r = 0;// r 记录当前主元要放的行数，也代表矩阵的秩
        // 遍历每一列，进行主元消去
        for (int i = 0; i < n;i++)
        {
            // 1. 列主元消去法：寻找当前列绝对值最大的元素作为主元 (Pivot)
            // 这样可以最大程度减小浮点数除法带来的精度误差
            int maxrow = r;
            for (int j = r + 1; j < n;j++)
            {
                if(abs(a[j][i]) > abs(a[maxrow][i]))
                    maxrow = j;
            }
            // 如果这一列的最大值都是 0，说明这个未知量是自由变量
            if(abs(a[maxrow][i]) < EPS)
                continue;// 注意：这里跳过这一列，r 不增加！

            // 3. 将主元所在的行交换到当前处理的第 i 行
            swap(a[r], a[maxrow]);
            
            // 4. 将主元化为 1：把第 i 行的所有元素除以主元 a[i][i]
            //相当于对该行所有元素做一个除以pivot的操作
            db pivot = a[i][i];
            for (int j = i; j <= n;j++)
                a[i][j] /= pivot;
            // 5. 消去其他行在第 i 列的系数 (Gauss-Jordan 消元)
            // 不仅消去下面的，连上面的也一起消去，最后直接得到对角矩阵
            for (int j = 0; j < n;j++)
            {
                if(i != j)
                {
                    db factor = a[j][i];
                    for (int k = i; k <= n;k++)
                        a[j][k] -= factor * a[i][k];

                }
            }
            r++;
        }
        // 消元结束，判断解的情况
        if(r < n)// 不满秩，说明有自由变量或者矛盾
        {
            // 检查第 r 行到第 n-1 行（这些行的系数部分已经被消成全 0 了）
            for (int i = r; i < n;i++)
            {
                // 如果常数项不为 0，说明出现了 0 = 非零数，矛盾！
                if(abs(a[i][n]) > EPS)
                    return -1;// 无解
            }
            return 0;// 0 = 0，无穷多解
        }

        // 满秩，有唯一解
        res.resize(n);
        for (int i = 0; i < n;i++)
            res[i] = a[i][n];
        return 1;
    }
};
