#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 1005

typedef struct {
    int k1, k2;
    int left, right;
} Node;

Node nodes[MAXN];
int n;
bool hasParent[MAXN];
int inorder[MAXN], idx; // 中序遍历记录k1

// 中序遍历，顺便检查BST性质（严格递增）
// BST的中序遍历严格递增
bool inorderTraversal(int root) {
    if (root == -1) return true;
    if (!inorderTraversal(nodes[root].left)) return false;
    inorder[idx++] = nodes[root].k1;
    if (!inorderTraversal(nodes[root].right)) return false;
    return true;
}

// 检查堆性质（最小堆，每个节点k2小于其孩子）
bool checkHeap(int root) {
    if (root == -1) return true;
    int left = nodes[root].left;
    int right = nodes[root].right;
    // 检查左孩子
    if (left != -1) {
        if (nodes[left].k2 <= nodes[root].k2) return false;
        if (!checkHeap(left)) return false;
    }
    if (right != -1) {
        if (nodes[right].k2 <= nodes[root].k2) return false;
        if (!checkHeap(right)) return false;
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &nodes[i].k1, &nodes[i].k2, &nodes[i].left, &nodes[i].right);
        if (nodes[i].left != -1) hasParent[nodes[i].left] = true;
        if (nodes[i].right != -1) hasParent[nodes[i].right] = true;
    }

    // 找根节点（没有父节点的节点）
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (!hasParent[i]) {
            root = i;
            break;
        }
    }
    // 如果n>0但未找到根（环或错误输入），按题目保证不会发生

    // 检查BST：中序遍历是否严格递增
    idx = 0;
    if (!inorderTraversal(root)) {
        printf("NO\n");
        return 0;
    }
    for (int i = 1; i < idx; i++) {
        if (inorder[i] <= inorder[i-1]) {
            printf("NO\n");
            return 0;
        }
    }

    // 检查最小堆
    if (!checkHeap(root)) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    return 0;
}