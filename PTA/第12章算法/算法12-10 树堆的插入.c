#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet;  /* 默认元素为整型 */
typedef struct RecordNode *Records;
struct RecordNode {
	ElemSet key; /* 关键字 */
	/* 其他属性由用户自定义 */
};

typedef Records TElemSet;
typedef struct TreapNode *Position; /* 树结点指针是元素的位置 */
typedef struct TreapNode *Treap;
struct TreapNode {
    TElemSet data; /* 数据元素 */
    int priority;  /* 优先级 */
    Treap left;   /* 左孩子指针 */
    Treap right;  /* 右孩子指针 */
};
#define NIL NULL

void Visit(Treap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void PreOrder(Treap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


Position RRotate(Position x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


Position LRotate(Position x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法12-10 树堆的插入 InsertTreap(treap, x) */
Treap InsertTreap(Treap treap, Records x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法12-10 结束 */ 

int main(void)
{
	Treap treap;
	Records x;
	int n, i;
	
	treap = NULL;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		x = (Records)malloc(sizeof(struct RecordNode));
		scanf("%d", &x->key);
		treap = InsertTreap(treap, x);
	}
	PreOrder(treap);

	return 0;
}

