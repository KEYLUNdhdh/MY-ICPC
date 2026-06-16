#include <stdio.h>
#include <stdlib.h>

typedef int HElemSet;
typedef struct LeftistHeapNode *LeftistHeap;
struct LeftistHeapNode {
	HElemSet key;      /* 数据元素 */
	int npl;           /* 左堆的npl值 */
	LeftistHeap left;  /* 左子树 */
	LeftistHeap right; /* 右子树 */
};

/* 算法6-9：左堆的合并操作 LeftistMerge(h1, h2) */
LeftistHeap LeftistMerge(LeftistHeap h1, LeftistHeap h2)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法6-9 结束 */ 

LeftistHeap CreateNode()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


LeftistHeap CreateHeap()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Visit(LeftistHeap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void PreOrder(LeftistHeap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void InOrder(LeftistHeap tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	LeftistHeap h1, h2;
	
	h1 = CreateHeap();
	h2 = CreateHeap();
	h1 = LeftistMerge(h1, h2);
	PreOrder(h1);
	InOrder(h1);
	
	return 0;
}


