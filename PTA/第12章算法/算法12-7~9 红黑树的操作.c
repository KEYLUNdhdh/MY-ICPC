#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef int ElemSet;  /* 默认元素为整型 */
typedef enum { Red, Black } Color;
typedef struct RecordNode *Records;
struct RecordNode {
	ElemSet key; /* 关键字 */
	/* 其他属性由用户自定义 */
};

typedef Records TElemSet;
typedef struct RBTreeNode *Position; /* 树结点指针是元素的位置 */
typedef struct RBTreeNode *RBTree;
struct RBTreeNode {
    TElemSet data; /* 数据元素 */
    RBTree left;   /* 左孩子指针 */
    RBTree right;  /* 右孩子指针 */
    Color color;   /* 颜色 */ 
    RBTree parent; /* 父指针 */
};
#define NIL NULL

void Visit(RBTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void PreOrder(RBTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法12-7：红黑树中的右旋 RRotate(rbtree, x) */
RBTree RRotate(RBTree rbtree, Position x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法12-7 结束 */ 

RBTree LRotate(RBTree rbtree, Position x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

/* 算法12-8：红黑树中插入结点后的调整 InsertAdjust(rbtree, x) */
RBTree InsertAdjust(RBTree rbtree, Position x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法12-8 结束 */ 

bool IsBlack( Position x )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsRed( Position x )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法12-9：删除黑结点及颜色调整 DeleteAdjust(rbtree, x) */
RBTree DeleteAdjust(RBTree rbtree, Position x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法12-9 结束 */ 

RBTree InsertRBT(RBTree rbtree, TElemSet record)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


RBTree DeleteRBT(RBTree rbtree, ElemSet key)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	RBTree rbtree;
	Records record;
	ElemSet key;
	int n, m, i;
	
	rbtree = NIL;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		record = (Records)malloc(sizeof(struct RecordNode));
		scanf("%d", &record->key);
		rbtree = InsertRBT(rbtree, record);
	}
	PreOrder(rbtree); printf("\n");
	scanf("%d", &m);
	for (i=0; i<m; i++) {
		scanf("%d", &key);
		rbtree = DeleteRBT(rbtree, key);
		PreOrder(rbtree); printf("\n");
	}

	return 0;
}

