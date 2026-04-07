#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTreeNode {
    char data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

// 构建二叉树
BinaryTreeNode* BuildTree(char *preorder, char *inorder, int n)
{
    if(n <= 0)
        return NULL;
    char rootData = preorder[0];
    int i;
    for (i = 0; i < n;i++)
    {
        if(inorder[i] == rootData)
            break;
    }
    BinaryTreeNode *root = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    root->data = inorder[i];
    root->left = BuildTree(preorder + 1, inorder, i);
    root->right = BuildTree(preorder + 1 + i, inorder + 1 + i, n - i - 1);
    return root;
}

// 求树的高度
int Height(BinaryTreeNode *tree)
{
    if(tree == NULL)
        return 0;
    int l = Height(tree->left);
    int r = Height(tree->right);
    return (l > r ? l : r) + 1;
}
int main() {
    int n;
    scanf("%d", &n);

    char preorder[100], inorder[100];
    scanf("%s", preorder);
    scanf("%s", inorder);

    BinaryTreeNode *tree = BuildTree(preorder, inorder, n);
    printf("%d\n", Height(tree));

    return 0;
}
