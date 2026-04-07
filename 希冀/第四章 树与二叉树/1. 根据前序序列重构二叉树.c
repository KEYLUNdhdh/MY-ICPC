#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int k = -1; // 全局索引

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

// 后序遍历
void PostOrder(Node* root) {
    if (root != NULL) {
        PostOrder(root->left);
        PostOrder(root->right);
        printf("%c ", root->data);
    }
}

// 本题要求实现
Node* PreOrderDeSerialize(char* preorder, int n)
{
    if(k >= n)
        return NULL;
    char c = preorder[++k];
    if(c == '#')
        return NULL;
    Node *root = (Node *)malloc(sizeof(Node));
    root->data = c;
    root->left = PreOrderDeSerialize(preorder, n);
    root->right = PreOrderDeSerialize(preorder, n);
    return root;
}

int main() {
    char preorder[1000];
    if (fgets(preorder, sizeof(preorder), stdin) == NULL) {
        // 输入为空
        return 0;
    }

    // 去掉换行符
    size_t len = strlen(preorder);
    if (len > 0 && preorder[len - 1] == '\n') preorder[len - 1] = '\0';

    if (strlen(preorder) == 0) {
        // 空输入直接退出
        return 0;
    }

    k = -1; // 重置全局索引
    Node* tree = PreOrderDeSerialize(preorder, strlen(preorder));
    PostOrder(tree);
    printf("\n");
    return 0;
}