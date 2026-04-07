#include <stdio.h>

// 本题要求实现
void ShellSort(int a[], int l, int r)
{
    int n = r - l + 1;// 元素个数
    // n：区间内的元素总数。
    // gap：当前排序的间隔（增量），希尔排序的核心。
    // i：用于遍历数组的索引。
    // j：用于在子序列内进行插入排序的游标。
    // tmp：暂存当前要插入的元素。
    // 外层循环：控制增量
    int gap, i, j, tmp;
    for (gap = n / 2; gap > 0; gap /= 2)// 初始增量为 n/2，每次减半，直到 0
    {
        // 对每个子序列进行直接插入排序
        // 从 gap 开始到 n-1，它并不直接对应原始数组的索引，而是表示当前要处理的元素在整个区间内的位置（相对于区间起点 l 的偏移）。
        for (i = gap; i < n;i++)
        {
            //将 a[i] 暂存到 tmp。
            // 从当前位置 i 开始，向前比较间隔为 gap 的元素：如果前一个元素（a[j - gap]）比 tmp 大，就将它后移到当前位置 a[j]。
            // 然后 j 减少 gap，继续向前比较，直到遇到比 tmp 小的元素，或者到达子序列的开头（j < gap）。
            // 最后将 tmp 放到正确的位置 a[j]。
            tmp = a[i];
            for (j = i; j >= gap && a[j - gap] > tmp;j -= gap)
            {
                a[j] = a[j - gap];
            }
            a[j] = tmp;
        }
    }
    return;
}
const int MAXLEN = 5000 + 10;
int main() {
    int n;
    scanf("%d", &n);
    int a[MAXLEN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    ShellSort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}