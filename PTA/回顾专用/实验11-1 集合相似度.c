#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define MAXM 10005

int sets[MAXN][MAXM];   // 存每个集合去重后的元素
int sz[MAXN];           // 每个集合去重后的元素个数

// 排序用的比较函数
int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

// 二分查找，判断 x 是否在集合 s 中
int binary_search(int s[], int len, int x) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (s[mid] == x) return 1;
        else if (s[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int m;
        scanf("%d", &m);
        int *tmp = (int *)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) scanf("%d", &tmp[j]);
        // 排序去重
        qsort(tmp, m, sizeof(int), cmp_int);
        int len = 0;
        for (int j = 0; j < m; j++) {
            if (j == 0 || tmp[j] != tmp[j-1]) {
                sets[i][len++] = tmp[j];
            }
        }
        sz[i] = len;
        free(tmp);
    }

    int k;
    scanf("%d", &k);
    for (int q = 0; q < k; q++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--; // 转为0下标
        // 为了让二分效率更高，选择较短的集合作为遍历对象
        int *s1 = sets[a], len1 = sz[a];
        int *s2 = sets[b], len2 = sz[b];
        int intersect = 0;
        if (len1 < len2) {
            for (int i = 0; i < len1; i++) {
                if (binary_search(s2, len2, s1[i]))
                    intersect++;
            }
        } else {
            for (int i = 0; i < len2; i++) {
                if (binary_search(s1, len1, s2[i]))
                    intersect++;
            }
        }
        int union_size = len1 + len2 - intersect;
        double similarity = intersect * 100.0 / union_size;
        printf("%.2f%%\n", similarity);
    }

    return 0;
}