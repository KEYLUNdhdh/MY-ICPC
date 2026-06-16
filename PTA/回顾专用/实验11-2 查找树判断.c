#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005

int seq[MAXN];   // 存储前序序列
int post[MAXN];  // 存储后序结果
int postLen;     // 后序结果长度

/* 尝试构建BST：左子树 < 根，右子树 >= 根 */
int buildBST(int l, int r) {
    if (l > r) return 1;
    int root = seq[l];
    int p = r + 1; // 右子树起始位置，默认空
    // 在剩余部分找第一个 >= root 的位置
    for (int i = l + 1; i <= r; i++) {
        if (seq[i] >= root) {
            p = i;
            break;
        }
    }
    // 右子树必须全部 >= root
    for (int i = p; i <= r; i++) {
        if (seq[i] < root) return 0;
    }
    // 递归左、右子树
    if (!buildBST(l + 1, p - 1)) return 0;
    if (!buildBST(p, r)) return 0;
    // 后序：根在最后
    post[postLen++] = root;
    return 1;
}

/* 尝试构建镜像BST：左子树 >= 根，右子树 < 根 */
int buildMirrorBST(int l, int r) {
    if (l > r) return 1;
    int root = seq[l];
    int p = r + 1; // 右子树起始位置，默认空
    // 在剩余部分找第一个 < root 的位置
    for (int i = l + 1; i <= r; i++) {
        if (seq[i] < root) {
            p = i;
            break;
        }
    }
    // 左子树必须全部 >= root
    for (int i = l + 1; i < p; i++) {
        if (seq[i] < root) return 0;
    }
    // 右子树必须全部 < root
    for (int i = p; i <= r; i++) {
        if (seq[i] >= root) return 0;
    }
    if (!buildMirrorBST(l + 1, p - 1)) return 0;
    if (!buildMirrorBST(p, r)) return 0;
    post[postLen++] = root;
    return 1;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &seq[i]);
    }

    // 先尝试构造BST
    postLen = 0;
    if (buildBST(0, n - 1)) {
        printf("YES\n");
        for (int i = 0; i < postLen; i++) {
            if (i) printf(" ");
            printf("%d", post[i]);
        }
        printf("\n");
        return 0;
    }

    // 再尝试构造镜像BST
    postLen = 0;
    if (buildMirrorBST(0, n - 1)) {
        printf("YES\n");
        for (int i = 0; i < postLen; i++) {
            if (i) printf(" ");
            printf("%d", post[i]);
        }
        printf("\n");
        return 0;
    }

    printf("NO\n");
    return 0;
}