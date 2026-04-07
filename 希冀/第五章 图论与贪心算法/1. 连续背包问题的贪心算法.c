#include <stdio.h>
#include <stdlib.h>
const int MAXLEN = 1000;

typedef struct {
    int idx;      // 序号
    double w;     // 重量
    double v;     // 价值
} Object;

// 比较函数，用于按价值/重量比排序（降序）
int cmp(const void *a, const void *b) {
    Object *obj1 = (Object *)a;
    Object *obj2 = (Object *)b;
    double r1 = obj1->v / obj1->w;
    double r2 = obj2->v / obj2->w;
    if (r1 < r2) return 1;
    else if (r1 > r2) return -1;
    else return 0;
}

// 本题要求实现
double Knapsack(double W, Object s[], double x[], int n)
{
    qsort(s, n, sizeof(Object), cmp);
    double totalValue = 0.0;
    double remainW = W;
    for (int i = 0; i < n;i++)
    {
        if(s[i].w < remainW)
        {
            x[s[i].idx] = 1;
            remainW -= s[i].w;
            totalValue += s[i].v;
        }
        else
        {
            x[s[i].idx] = remainW / s[i].w;
            totalValue += x[s[i].idx] * s[i].v;
            break;
        }
    }
    return totalValue;
}
int main() {
    int n;
    double W;
    scanf("%d", &n);    // 输入物品个数
    scanf("%lf", &W);   // 输入背包容量

    double weightList[MAXLEN], valueList[MAXLEN];
    for (int i = 0; i < n; i++) {
        scanf("%lf", &weightList[i]);  // 输入重量
    }
    for (int i = 0; i < n; i++) {
        scanf("%lf", &valueList[i]);   // 输入价值
    }

    Object s[MAXLEN];
    double x[MAXLEN];
    for (int i = 0; i < n; i++) {
        s[i].idx = i;
        s[i].w = weightList[i];
        s[i].v = valueList[i];
        x[i] = 0;
    }

    double result = Knapsack(W, s, x, n);
    printf("%.2f\n", result);
    for (int i = 0; i < n; i++) {
        printf("%.2f ", x[i]);
    }

    return 0;
}
