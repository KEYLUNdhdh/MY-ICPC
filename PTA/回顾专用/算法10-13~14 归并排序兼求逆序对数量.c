#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 默认元素为整数*/

/* 二路归并求逆序对减量：合并 a[l..m] 和 a[m+1..r]，
   返回跨左右子数组的逆序对数量，并完成合并排序 */
int TwoWayInversionCount(ElemSet *a, int l, int m, int r)
{
    int i = l, j = m + 1, k = 0;
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int count = 0;

    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            // 当 a[i] > a[j] 时，a[i..m] 都大于 a[j]
			// 其实只用关注这个就行，其他的归并排序可以集成到一个函数里面
            count += (m - i + 1);
            temp[k++] = a[j++];
        }
    }

    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    // 将有序序列复制回原数组
    for (int p = 0; p < k; p++) {
        a[l + p] = temp[p];
    }

    free(temp);
    return count;
}

/* 归并排序兼求逆序对数量：递归排序并累计逆序对总数 */
int InversionCount(ElemSet *a, int l, int r)
{
    if (l >= r) return 0;

    int mid = (l + r) / 2;
	// 先拆解
    int leftCount = InversionCount(a, l, mid);
    int rightCount = InversionCount(a, mid + 1, r);
	// 再归并排序
    int crossCount = TwoWayInversionCount(a, l, mid, r);

    return leftCount + rightCount + crossCount;
}

int main(void)
{
    ElemSet *a; /* 数组a的下标从0开始 */
    int n, i;

    scanf("%d", &n);
    a = (ElemSet *)malloc(sizeof(ElemSet) * n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("count = %d\n", InversionCount(a, 0, n - 1));

    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }

    free(a);
    return 0;
}