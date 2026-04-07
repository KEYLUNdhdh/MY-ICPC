#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int k = -1; // 当前处理的序列下标

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// 创建新结点
Node* CreateBinaryTree(char data) {
    Node* tree = (Node*)malloc(sizeof(Node));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

// 根据先序序列创建二叉树
Node* PreOrderDeSerialize(char* preorder, int n) {
    k++;
    Node* tree = NULL;
    if (k < n) {
        char data = preorder[k];
        if (data != '#') {
            tree = CreateBinaryTree(data);
            tree->left = PreOrderDeSerialize(preorder, n);
            tree->right = PreOrderDeSerialize(preorder, n);
        }
    }
    return tree;
}

// 本题要求实现
int Height(Node* tree)
{
    if(tree == NULL)
        return 0;
    int l = Height(tree->left);
    int r = Height(tree->right);
    return (l > r ? l : r) + 1;
}

int main() {
    char preorder[1000];

    if (fgets(preorder, sizeof(preorder), stdin) == NULL) {
        // 空输入
        printf("0\n");
        return 0;
    }

    // 去掉换行符
    size_t len = strlen(preorder);
    if (len > 0 && preorder[len - 1] == '\n') preorder[len - 1] = '\0';

    if (strlen(preorder) == 0) {
        printf("0\n");
        return 0;
    }

    k = -1; // 重置全局索引
    Node* tree = PreOrderDeSerialize(preorder, strlen(preorder));
    printf("%d\n", Height(tree));

    return 0;
}
