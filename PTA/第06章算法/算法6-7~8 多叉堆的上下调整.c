#include <stdio.h>
#include <stdlib.h>

typedef int HElemSet;
typedef int Position; /* 数组下标即为元素位置 */
typedef struct DHeapNode *MaxHeap;
typedef struct DHeapNode *MinHeap;
struct DHeapNode {
	HElemSet *data;  /* 数据元素数组 */
	int size;        /* 规模 */
	int capacity;    /* 容量 */
};

void InitPQueue(MinHeap pq, int capacity);
void SiftUpD(MinHeap h, int d, Position i);
void SiftDownD(MinHeap h, int d, Position i);
void InsertD(MinHeap h, int d, HElemSet x);
HElemSet ExtractMinD(MinHeap h, int d);

int main(void)
{
	MinHeap h;
	int capacity, d, n, i;
	HElemSet x;
	
	h = (MinHeap)malloc(sizeof(struct DHeapNode));
	scanf("%d %d", &capacity, &d);
	InitPQueue(h, capacity);
	scanf("%d", &n);
	h->size = n;
	for (i=0; i<n; i++) { /* 注意：多叉堆下标从0开始 */
		scanf("%d", &h->data[i]); /* 读入一个最小堆 */
	}
	scanf("%d", &x);
	InsertD(h, d, x);
	printf("min = %d\n", ExtractMinD(h, d));
	for (i=0; i<h->size; i++) { /* 输出插入、删除后的堆元素 */
		printf("%d\n", h->data[i]);
	}
	return 0;
}

void InitPQueue(MinHeap pq, int capacity)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法6-7：多叉堆的上调操作 SiftUpD(h, d, i) */ 
void SiftUpD(MinHeap h, int d, Position i)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法6-7 结束 */ 

/* 算法6-8：多叉堆的下调操作 SiftDownD(h, d, i) */ 
void SiftDownD(MinHeap h, int d, Position i)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法6-8 结束 */ 

void InsertD(MinHeap h, int d, HElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


HElemSet ExtractMinD(MinHeap h, int d)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


