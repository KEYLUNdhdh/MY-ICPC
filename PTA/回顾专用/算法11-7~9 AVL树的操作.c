#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet;
typedef struct RecordNode *Records;
struct RecordNode {
    ElemSet key;
};

typedef Records TElemSet;
typedef struct AVLTreeNode *Position;
typedef struct AVLTreeNode *AVLTree;
struct AVLTreeNode {
    TElemSet data;
    int height;
    AVLTree left;
    AVLTree right;
};
#define NIL NULL

/* 获取结点高度，空树高度为0 */
int GetHeight(AVLTree tree)
{
    if (tree == NULL) return 0;
    return tree->height;
}

/* 返回两个整数中的较大值 */
int Max(int x, int y)
{
    return (x > y) ? x : y;
}

/* 左单旋转（RR型） */
AVLTree RRSingleRotation(AVLTree root)
{
    AVLTree newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    // 更新两者的高度
    root->height = 1 + Max(GetHeight(root->left), GetHeight(root->right));
    newRoot->height = 1 + Max(GetHeight(newRoot->left), GetHeight(newRoot->right));

    return newRoot;
}

/* 右单旋转（LL型） */
AVLTree LLSingleRotation(AVLTree root)
{
    AVLTree newRoot = root->left;// 左边的孩子翻身做主人
    root->left = newRoot->right;// 把新根的右子树还给旧根当左子树
    newRoot->right = root;// 旧根变成新根的右子树

    // 更新两者的高度
    //先更新 root， 再更新newroot，自底向上
    root->height = 1 + Max(GetHeight(root->left), GetHeight(root->right));
    newRoot->height = 1 + Max(GetHeight(newRoot->left), GetHeight(newRoot->right));

    return newRoot;
}

/* 先左后右双向旋转（LR型） */
AVLTree LRDoubleRotation(AVLTree root)
{
    root->left = RRSingleRotation(root->left);
    return LLSingleRotation(root);
}

/* 先右后左双向旋转（RL型） */
AVLTree RLDoubleRotation(AVLTree root)
{
    root->right = LLSingleRotation(root->right);
    return RRSingleRotation(root);
}

/* AVL树的插入 */
AVLTree InsertAVL(AVLTree tree, TElemSet x)
{
    if (tree == NULL) {
        tree = (AVLTree)malloc(sizeof(struct AVLTreeNode));
        tree->data = x;
        tree->left = tree->right = NULL;
        tree->height = 1;
        return tree;
    }

    if (x->key < tree->data->key) {
        tree->left = InsertAVL(tree->left, x);
        tree->height = 1 + Max(GetHeight(tree->left), GetHeight(tree->right));

        if (GetHeight(tree->left) - GetHeight(tree->right) > 1) {
            if (x->key < tree->left->data->key)
                return LLSingleRotation(tree);
            else
                return LRDoubleRotation(tree);
        }
    }
    else if (x->key > tree->data->key) {
        tree->right = InsertAVL(tree->right, x);
        tree->height = 1 + Max(GetHeight(tree->left), GetHeight(tree->right));

        if (GetHeight(tree->right) - GetHeight(tree->left) > 1) {
            if (x->key > tree->right->data->key)
                return RRSingleRotation(tree);
            else
                return RLDoubleRotation(tree);
        }
    }
    /* 若相等则不插入（题目保证不重复） */

    return tree;
}

/* 访问结点，输出键值 */
void Visit(AVLTree tree)
{
    printf("%d\n", tree->data->key);
}

/* 先序遍历 */
void PreOrder(AVLTree tree)
{
    if (tree == NULL) return;
    Visit(tree);
    PreOrder(tree->left);
    PreOrder(tree->right);
}

int main(void)
{
    TElemSet x;
    AVLTree tree;
    int n, i;

    tree = NIL;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        x = (TElemSet)malloc(sizeof(struct RecordNode));
        scanf("%d", &x->key);
        tree = InsertAVL(tree, x);
    }
    PreOrder(tree);

    return 0;
}