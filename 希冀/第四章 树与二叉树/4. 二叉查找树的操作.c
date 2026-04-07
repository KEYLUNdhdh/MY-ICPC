#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 记录结构体
typedef struct Record {
    int key;
    // 其他属性可以自定义
} Record;

// 二叉树节点
typedef struct BinaryTree {
    Record data;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree;

// 创建新节点
BinaryTree* CreateNode(Record x) {
    BinaryTree* node = (BinaryTree*)malloc(sizeof(BinaryTree));
    node->data = x;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 查找
BinaryTree* SearchBST(BinaryTree* bstree, int key)
{
    if(bstree == NULL)
        return NULL;
    if(key == bstree->data.key)
        return bstree;
    else if(key < bstree->data.key)
        return SearchBST(bstree->left, key);
    else
        return SearchBST(bstree->right, key);
}

// 插入
BinaryTree* InsertBST(BinaryTree* bstree, Record x)
{
    if(bstree == NULL)
    {
        BinaryTree *tmp = CreateNode(x);
        return tmp;
    }
    if(x.key < bstree->data.key)
        bstree->left = InsertBST(bstree->left, x);
    else if(x.key > bstree->data.key)
        bstree->right = InsertBST(bstree->right, x);
    // 若 x.key == bstree.data.key，则不重复插入，直接返回原指针
    return bstree;
}

// 删除节点
BinaryTree* DeleteBST(BinaryTree* bstree, int key)
{
    if(bstree == NULL)
    {
        printf("错误：%d不在树中。\n", key);
        return NULL;
    }
    if(key < bstree->data.key)
        bstree->left = DeleteBST(bstree->left, key);
    else if(key > bstree->data.key)
        bstree->right = DeleteBST(bstree->right, key);
    else
    {
        if(bstree->left == NULL)
        {
            // 只有右子树或为叶子节点
            BinaryTree *tmp = bstree->right;
            free(bstree);
            return tmp;
        }
        else if(bstree->right == NULL)
        {
            // 只有左子树
            BinaryTree *tmp = bstree->left;
            free(bstree);
            return tmp;
        }
        else
        {
            // 左右子树都有：【题目要求：选择节点左子树中的最大节点代替】
            BinaryTree *tmp = bstree->left;
            while(tmp->right != NULL)
                tmp = tmp->right;
            // 替换数据
            bstree->data.key = tmp->data.key;
            // 递归地在左子树中把那个最大节点删掉
            bstree->left = DeleteBST(bstree->left, tmp->data.key);
        }
    }
    return bstree;
}
// 先序遍历
void PreOrder(BinaryTree* tree) {
    if (tree != NULL) {
        printf("%d ", tree->data.key);
        PreOrder(tree->left);
        PreOrder(tree->right);
    }
}

int main() {
    BinaryTree* bstree = NULL;
    Record r;
    int key;

    // 输入一行节点 key
    char line[2048];
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, " \t\n");
    while (token) {
        r.key = atoi(token);
        bstree = InsertBST(bstree, r);
        token = strtok(NULL, " \t\n");
    }

    // 输入查找/删除的 key
    scanf("%d", &key);

    // 插入后先序遍历
    PreOrder(bstree);
    printf("\n");
    

    BinaryTree* p = SearchBST(bstree, key);
    if (p != NULL)
        printf("Found key = %d\n", p->data.key);
    else
        printf("Not Found.\n");

    // 删除 key
    bstree = DeleteBST(bstree, key);

    // 删除后先序遍历
    PreOrder(bstree);
    printf("\n");

    p = SearchBST(bstree, key);
    if (p != NULL)
        printf("Found key = %d\n", p->data.key);
    else
        printf("Not Found.\n");

    return 0;
}