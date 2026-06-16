#include <stdio.h>
#include <stdlib.h>

typedef int HElemSet;
typedef struct SkewHeapNode *SkewHeap;
struct SkewHeapNode {
	HElemSet key;      /* 数据元素 */
	SkewHeap left;  /* 左子树 */
	SkewHeap right; /* 右子树 */
};

/* 算法6-10：斜堆的合并操作 SkewMerge(h1, h2) */
SkewHeap SkewMerge(SkewHeap h1, SkewHeap h2)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法6-10 结束 */ 

SkewHeap CreateNode()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


SkewHeap CreateHeap()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Visit(SkewHeap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void PreOrder(SkewHeap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void InOrder(SkewHeap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	SkewHeap h1, h2;
	
	h1 = CreateHeap();
	h2 = CreateHeap();
	h1 = SkewMerge(h1, h2);
	PreOrder(h1);
	InOrder(h1);
	
	return 0;
}

