#include <stdio.h>

#define MAXN 15
// 存储树结点
typedef struct {
    char val;
    int left;
    int right;
} Node;

Node t1[MAXN], t2[MAXN];

// 找根节点：根节点不会出现在任何结点的孩子中，因此标记出现过的编号即可
int findRoot(int n, Node t[]) {
    int check[15] = {0};
    for (int i = 0; i < n; i++) {
        if (t[i].left != -1) check[t[i].left] = 1;
        if (t[i].right != -1) check[t[i].right] = 1;
    }
    for (int i = 0; i < n; i++)
        if (!check[i]) return i;
    return -1;
}

int isIsomorphic(int r1, int r2) {
    // 两个都是空：匹配
    if (r1 == -1 && r2 == -1) return 1;
    // 一个空一个非空：不匹配
    if ((r1 == -1 && r2 != -1) || (r1 != -1 && r2 == -1)) return 0;
    // 结点值不相等：不匹配
    if (t1[r1].val != t2[r2].val) return 0;
    
    // 两种匹配方式：不交换 or 交换左右孩子
    return (isIsomorphic(t1[r1].left, t2[r2].left) && isIsomorphic(t1[r1].right, t2[r2].right)) ||
           (isIsomorphic(t1[r1].left, t2[r2].right) && isIsomorphic(t1[r1].right, t2[r2].left));
}

int main() {
    int n1, n2;
    char cl, cr;
    
    // 读第一棵树
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        scanf(" %c %c %c", &t1[i].val, &cl, &cr);
        t1[i].left = (cl == '-') ? -1 : (cl - '0');
        t1[i].right = (cr == '-') ? -1 : (cr - '0');
    }
    // 读第二棵树
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        scanf(" %c %c %c", &t2[i].val, &cl, &cr);
        t2[i].left = (cl == '-') ? -1 : (cl - '0');
        t2[i].right = (cr == '-') ? -1 : (cr - '0');
    }
    
    // 结点数不同直接输出No
    if (n1 != n2) {
        printf("No\n");
        return 0;
    }
    if (n1 == 0) { // 两棵树都是空，也算同构
        printf("Yes\n");
        return 0;
    }
    
    int r1 = findRoot(n1, t1);
    int r2 = findRoot(n2, t2);
    
    if (isIsomorphic(r1, r2)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}
