#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int finish;
    int weight;
} Activity;


// 带权活动选择 本题要求实现
int WeightedActivitySelection(Activity* a, int n)
{
    // 1. 在函数内部手写冒泡排序，按结束时间从小到大排序
    // 注意：题目给的 a 数组是从下标 1 开始存数据的，a[0] 是哨兵
    for (int i = 1; i <= n - 1;i++)
    {
        for (int j = 1; j <= n - i;j++)
        {
            if(a[j].finish > a[j + 1].finish)
            {
                Activity tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    // 2. 初始化 DP 数组
    int dp[105] = {0};
    // 3. 动态规划过程
    for (int i = 1; i <= n;i++)
    {
        int lst = 0;
        // 在内部直接向前寻找最近的兼容活动
        for (int j = i - 1; j >= 0;j--)
        {
            if(a[j].finish <= a[i].start)//找到了就退出
            {
                lst = j;
                break;
            }
        }
        int include = a[i].weight + dp[lst];//选当前a[i]
        int exclude = dp[i - 1];//不选
        if(include > exclude)
            dp[i] = include;
        else
            dp[i] = exclude;
    }

    return dp[n];
}

int main() {
    int n;
    scanf("%d", &n);
    Activity* a = (Activity*)malloc((n+1)*sizeof(Activity));
    a[0].start = a[0].finish = a[0].weight = 0; // 哨兵

    for(int i=1; i<=n; i++){
        scanf("%d %d %d", &a[i].start, &a[i].finish, &a[i].weight);
    }

    printf("%d\n", WeightedActivitySelection(a, n));
    free(a);
    return 0;
}