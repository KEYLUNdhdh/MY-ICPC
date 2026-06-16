#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet;  /* 默认元素为整数*/
typedef struct RecordNode {
	ElemSet key; /* 关键字 */
	/* 其他属性由用户自定义 */
} Records;

typedef Records *TElemSet;
typedef struct BinaryTreeNode *Position; /* 树结点指针是元素的位置 */
typedef struct BinaryTreeNode *BinaryTree;
struct BinaryTreeNode {
    TElemSet data;      /* 数据元素 */
    BinaryTree left;    /* 左孩子指针 */
    BinaryTree right;   /* 右孩子指针 */
};
#define NIL NULL

/* 算法11-4 二叉查找树的查找 SearchBST(bstree, key) */
Position SearchBST(BinaryTree bstree, ElemSet key)
{
    if(!bstree)
	{
		return NULL;
	}
	int num = bstree->data->key;
	if(num == key)
		return bstree;
	else if(num < key)
		return SearchBST(bstree->right, key);
	else
		return SearchBST(bstree->left, key);
}

/* 算法11-4 结束 */ 

/* 算法11-5 二叉查找树的插入 InsertBST(bstree, x) */
BinaryTree InsertBST(BinaryTree bstree, TElemSet x)
{
    if(!bstree)
	{
		bstree = (BinaryTree)malloc(sizeof(struct BinaryTreeNode));
		bstree->data = x;
		bstree->left = NULL;
		bstree->right = NULL;
		return bstree;
	}

	if(x->key == bstree->data->key)
		return bstree;
	else if(x->key > bstree->data->key)
		bstree->right = InsertBST(bstree->right, x);
	else
		bstree->left = InsertBST(bstree->left, x);

	return bstree;
}

/* 算法11-5 结束 */ 

/* 算法11-6 二叉查找树的删除 DeleteBST(bstree, key) */
BinaryTree DeleteBST(BinaryTree bstree, ElemSet key)
{ 
    if (!bstree)
	{
		printf("错误：%d不在树中。\n", key);
		return NULL;
	}

    if (key < bstree->data->key) {
        bstree->left = DeleteBST(bstree->left, key);
        return bstree;
    } else if (key > bstree->data->key) {
        bstree->right = DeleteBST(bstree->right, key);
        return bstree;
    } else {
        // 找到要删除的节点
        // 叶子
        if (!bstree->left && !bstree->right) {
            free(bstree->data);
            free(bstree);
            return NIL;
        }
        // 只有右孩子
        else if (!bstree->left) {
            BinaryTree temp = bstree->right;
            free(bstree->data);
            free(bstree);
            return temp;
        }
        // 只有左孩子
        else if (!bstree->right) {
            BinaryTree temp = bstree->left;
            free(bstree->data);
            free(bstree);
            return temp;
        }
        // 有两个孩子：用右子树最小节点替代
        else {
            BinaryTree minNode = bstree->right;
            while (minNode->left) minNode = minNode->left;
            // 复制数据（注意：不能直接赋值指针，要复制内容）
            TElemSet tmpData = (TElemSet)malloc(sizeof(Records));
            tmpData->key = minNode->data->key;
            // 删除右子树中的最小节点
            bstree->right = DeleteBST(bstree->right, minNode->data->key);
            // 释放原节点数据，替换为新的数据
            free(bstree->data);
            bstree->data = tmpData;
            return bstree;
        }
    }
}

/* 算法11-6 结束 */ 

int main(void)
{
	TElemSet x;
	BinaryTree bstree;
	int n, i;
	ElemSet key;
	Position p;
	
	bstree = NIL;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		x = (TElemSet)malloc(sizeof(Records));
		scanf("%d", &x->key);
		bstree = InsertBST(bstree, x);
	}
	scanf("%d", &key);
	p = SearchBST(bstree, key);
	if (p!=NIL) {
		printf("Found key = %d\n", p->data->key);
	}
	else {
		printf("NotFound.\n");
	}
	bstree = DeleteBST(bstree, key);
	p = SearchBST(bstree, key);
	if (p!=NIL) {
		printf("Found key = %d\n", p->data->key);
	}
	else {
		printf("NotFound.\n");
	}	

	return 0;
}

