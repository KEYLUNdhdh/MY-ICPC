#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 默认元素为整数*/
#define Swap(x, y) { ElemSet t = x; x = y; y = t; }

/* 堆的定义与操作 */
typedef ElemSet HElemSet;
typedef int Position; /* 数组下标即为元素位置 */
typedef struct BinaryHeapNode *MaxHeap;
struct BinaryHeapNode {
	HElemSet *data;  /* 数据元素数组 */
	int size;        /* 规模 */
	int capacity;    /* 容量 */
};

void SiftDown(MaxHeap h, Position i)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void MakeHeapDown(MaxHeap h)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 堆的定义与操作结束 */

/* 算法10-4：堆排序 HeapSort(a,l,r) */
void HeapSort(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-4 结束 */ 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	HeapSort(a, 0, n-1);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

