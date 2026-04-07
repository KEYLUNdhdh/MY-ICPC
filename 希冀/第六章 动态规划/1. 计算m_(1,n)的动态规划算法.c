#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100

int m[MAXN][MAXN]; // 存储最少乘法次数
int p[MAXN][MAXN]; // 存储划分点

void PrintOrder(int i, int j)
{
    // 利用静态变量来标记是否是最外层调用
    //只会被初始化一次你知道吗
    static int is_root = 1;
    //判断当前是否为首次调用
    int cur = is_root;
    is_root = 0;
    if(i == j)
    {
        // 如果是单个矩阵，只有最外层才不加括号（应对 n=1 的样例）
        if(cur)
            printf("M%d", i);
        else
            printf("(M%d)", i);
    }
    else
    {
        // 如果是复合表达式，非最外层需要被括号包裹
        if(!cur)
            printf("(");
        PrintOrder(i, p[i][j]);// 递归打印左半部分
        printf("x");
        PrintOrder(p[i][j] + 1, j);// 递归打印右半部分
        if(!cur)
            printf(")");
    }
}

// 本题要求实现
void OptimalMatrixOrdering(int n, int* r)
{   
    for (int i = 0; i < n;i++)
        m[i][i] = 0;
    for (int l = 2; l <= n;l++)
    {
        for (int i = 0; i < n - l + 1;i++)
        {
            int j = i + l - 1;
            m[i][j] = 1e9;//初始化最大值
            // 3. 尝试在区间 [i, j) 内寻找最优的划分点 k
            for (int k = i; k < j;k++)
            {
                //现在左右两块都分别融合成了一个大矩阵。
                // 左边融合完的矩阵尺寸是：r[i] * r[k+1]
                // 右边融合完的矩阵尺寸是：r[k+1] * r[j+1]
                // 把这两个大矩阵乘起来，还需要进行 r[i] * r[k+1] * r[j+1] 次乘法。
                int cost = m[i][k] + m[k + 1][j] + r[i] * r[k + 1] * r[j + 1];
                if(cost < m[i][j])
                {
                    m[i][j] = cost;
                    p[i][j] = k;// 记录最优划分点
                }
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int r[MAXN];
    for(int i=0;i<=n;i++)
        scanf("%d", &r[i]);

    OptimalMatrixOrdering(n, r);
    PrintOrder(0, n-1);
    printf("\n");
    return 0;
}