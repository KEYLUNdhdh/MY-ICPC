#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005

int A[MAXN], B[MAXN];
int leftIdx[MAXN], rightIdx[MAXN];
int best[MAXN], maxMin[MAXN];
int stack[MAXN];

int max(int a, int b) { return a > b ? a : b; }
// 暑假前集训的原题，配合两个单调栈解决.
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &B[i]);

    // 1. 计算左边第一个小于 A[i] 的位置
    int top = 0;
    for (int i = 1; i <= n; i++) {
        while (top > 0 && A[stack[top - 1]] >= A[i]) top--;
        leftIdx[i] = (top == 0) ? 0 : stack[top - 1];
        stack[top++] = i;
    }

    // 2. 计算右边第一个小于等于 A[i] 的位置
    top = 0;
    for (int i = n; i >= 1; i--) {
        while (top > 0 && A[stack[top - 1]] > A[i]) top--;
        rightIdx[i] = (top == 0) ? n + 1 : stack[top - 1];
        stack[top++] = i;
    }

    // 3. 统计每个长度对应的最大可能最小值
    for (int i = 1; i <= n; i++) best[i] = 0;
    for (int i = 1; i <= n; i++) {
        int len = rightIdx[i] - leftIdx[i] - 1;
        if (A[i] > best[len]) best[len] = A[i];
    }

    // 4. 从大到小做前缀最大值，得到 maxMin[k]
    maxMin[n + 1] = 0;
    for (int k = n; k >= 1; k--) {
        maxMin[k] = max(maxMin[k + 1], best[k]);
    }

    // 5. 构造答案字符串
    char *ans = (char *)malloc((n + 1) * sizeof(char));
    ans[n] = '\0';
    for (int k = 1; k <= n; k++) {
        ans[k - 1] = (maxMin[k] >= B[k]) ? '1' : '0';
    }
    printf("%s\n", ans);

    free(ans);
    return 0;
}