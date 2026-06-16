#include <stdio.h>
#include <stdlib.h>

#define MAXM 100

int N, M;                      // 全局变量，供比较函数使用
int (*arr)[MAXM];              // 动态二维数组，存储所有模块的输出序列

/* 比较两个序列，字典序升序 */
int cmp_seq(const void *a, const void *b) {
    int *pa = (int *)a;
    int *pb = (int *)b;
    for (int i = 0; i < M; i++) {
        if (pa[i] != pb[i])
            return pa[i] - pb[i];
    }
    return 0;
}

/* 统计结果的结构体：出现次数 + 序列内容 */
typedef struct {
    int cnt;
    int seq[MAXM];
} Result;

/* 比较两个统计结果：先按次数降序，再按序列升序 */
int cmp_result(const void *a, const void *b) {
    Result *ra = (Result *)a;
    Result *rb = (Result *)b;
    if (ra->cnt != rb->cnt)
        return rb->cnt - ra->cnt;   // 降序
    for (int i = 0; i < M; i++) {
        if (ra->seq[i] != rb->seq[i])
            return ra->seq[i] - rb->seq[i];
    }
    return 0;
}

int main() {
    scanf("%d %d", &N, &M);
    // 分配 N 行，每行 M 个整数
    arr = (int (*)[MAXM])malloc(N * sizeof(*arr));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    // 1. 按字典序排序所有模块
    qsort(arr, N, sizeof(arr[0]), cmp_seq);

    // 2. 统计不同序列的出现次数
    Result *res = (Result *)malloc(N * sizeof(Result));
    int K = 0;
    int i = 0;
    while (i < N) {
        int j = i;
        while (j < N && cmp_seq(&arr[i], &arr[j]) == 0)
            j++;
        res[K].cnt = j - i;
        for (int k = 0; k < M; k++)
            res[K].seq[k] = arr[i][k];
        K++;
        i = j;
    }

    // 3. 对统计结果排序
    qsort(res, K, sizeof(Result), cmp_result);

    // 4. 输出
    printf("%d\n", K);
    for (int i = 0; i < K; i++) {
        printf("%d", res[i].cnt);
        for (int j = 0; j < M; j++) {
            printf(" %d", res[i].seq[j]);
        }
        printf("\n");
    }

    free(arr);
    free(res);
    return 0;
}