#include <stdio.h>
#include <stdlib.h>

typedef int HElemSet;
typedef int Position; /* 数组下标即为元素位置 */
typedef struct BinaryHeapNode *MaxHeap;
typedef struct BinaryHeapNode *MinHeap;
struct BinaryHeapNode {
	HElemSet *data;  /* 数据元素数组 */
	int size;        /* 规模 */
	int capacity;    /* 容量 */
};

/* 线性表定义 */
#define kMaxSize 10000
#define NIL -1
typedef HElemSet ElemSet;
 
typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct ListNode *List;
struct ListNode {
    ElemSet data[kMaxSize]; /* 存储数据的数组 */
    Position last; /* 线性表中最后一个元素在数组中的位置 */
};

void InitList( List list )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 线性表定义结束 */

void InitPQueue(MinHeap pq, int capacity)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void SiftUp(MinHeap h, Position i)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法6-5：二叉堆的朴素建堆操作 MakeHeapUp(h) */
void MakeHeapUp(MinHeap h)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法6-5 结束 */ 

void MakePQueue(MinHeap h, List list)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	MinHeap h;
	List list;
	int capacity, n, i;
	HElemSet x;
	
	h = (MinHeap)malloc(sizeof(struct BinaryHeapNode));
	scanf("%d", &capacity);
	InitPQueue(h, capacity);
	list = (List)malloc(sizeof(struct ListNode));
	InitList(list);
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		scanf("%d", &list->data[i]); /* 读入一个线性表 */
		list->last++; 
	}
	MakePQueue(h, list);
	for (i=1; i<=h->size; i++) { /* 输出调整后的堆元素 */
		printf("%d\n", h->data[i]);
	}
	return 0;
}

