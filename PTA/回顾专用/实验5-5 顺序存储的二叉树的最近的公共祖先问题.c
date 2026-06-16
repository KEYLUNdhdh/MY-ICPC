#include <stdio.h>

#define MAXN 1005
int tree[MAXN];

int main() {
    int n, i, j;
    scanf("%d", &n);
    // 编号从1开始存储，和题目一致
    for (int k = 1; k <= n; k++) {
        scanf("%d", &tree[k]);
    }
    scanf("%d %d", &i, &j);

    // 按顺序检查空结点
    if (tree[i] == 0) {
        printf("ERROR: T[%d] is NULL", i);
        return 0;
    }
    if (tree[j] == 0) {
        printf("ERROR: T[%d] is NULL", j);
        return 0;
    }

    // 暴力向上找，直到两个结点相遇
    while (i != j) {
        if (i > j) {
            i = i / 2;
        } else {
            j = j / 2;
        }
    }

    // 输出结果
    printf("%d %d\n", i, tree[i]);
    return 0;
}

// 顺序存储的完全二叉树有一个固定性质：对于编号为k的结点，它的父结点编号是 k / 2（整数向下取整）。
// 我们只需要让更深（编号更大）的结点不断向上跳，直到两个结点相遇，第一个相遇的结点就是最近公共祖先。