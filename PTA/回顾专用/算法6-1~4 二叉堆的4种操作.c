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

void InitPQueue(MinHeap pq, int capacity);
void SiftUp(MinHeap h, Position i);
void SiftDown(MinHeap h, Position i);
void Insert(MinHeap h, HElemSet x);
HElemSet ExtractMin(MinHeap h);

int main(void)
{
	MinHeap h;
	int capacity, n, i;
	HElemSet x;
	
	h = (MinHeap)malloc(sizeof(struct BinaryHeapNode));
	scanf("%d", &capacity);
	InitPQueue(h, capacity);
	scanf("%d", &n);
	h->size = n;
	for (i=1; i<=n; i++) {
		scanf("%d", &h->data[i]); /* 读入一个最小堆 */
	}
	scanf("%d", &x);
	Insert(h, x);
	printf("min = %d\n", ExtractMin(h));
	for (i=1; i<=h->size; i++) { /* 输出插入、删除后的堆元素 */
		printf("%d\n", h->data[i]);
	}
	return 0;
}

void InitPQueue(MinHeap pq, int capacity)
{
	pq->capacity = capacity;
	pq->size = 0;
	pq->data = (int *)malloc(sizeof(int) * (capacity + 1));
}


/* 算法6-1：二叉堆的上调操作 SiftUp(h, i) */ 
void SiftUp(MinHeap h, Position i)
{
	int val = h->data[i];
	while(i > 1 && val < h->data[i / 2])
	{
		h->data[i] = h->data[i / 2];
		i /= 2;
	}

	h->data[i] = val;
}

/* 算法6-1 结束 */ 

/* 算法6-2：二叉堆的下调操作 SiftDown(h, i) */ 
void SiftDown(MinHeap h, Position i)
{
	int val = h->data[i];
	int child;

	while(2 * i <= h->size)
	{
		child = 2 * i;

		if(child + 1 <= h->size && h->data[child + 1] < h->data[child])
			child++;

		if(val <= h->data[child])
			break;

		h->data[i] = h->data[child];
		i = child;
	}

	h->data[i] = val;
}

/* 算法6-2 结束 */ 

/* 算法6-3：二叉堆的插入操作 Insert(h, x) */ 
void Insert(MinHeap h, HElemSet x)
{
    if(h->size >= h->capacity)
		return;

	// 放到堆的最后，然后向上调整
	h->size++;
	h->data[h->size] = x;
	SiftUp(h, h->size);
}

/* 算法6-3 结束 */ 

/* 算法6-4：二叉堆的删顶操作 ExtractMin(h) */ 
HElemSet ExtractMin(MinHeap h)
{
	int min = h->data[1];// 堆顶就是最小值
	// 把最后一个元素放到堆顶，然后向下调整
	h->data[1] = h->data[h->size];
	h->size--;
	SiftDown(h, 1);
	return min;
}

/* 算法6-4 结束 */ 

// 快速建堆的核心逻辑：从最后一个非叶子节点开始倒序下沉
// 我们先全部读入，然后根据这个快速建立堆
void BuildHeap(MinHeap h)
{
	// 最后一个非叶子节点的下标 = 总节点数 / 2
	for (int i = h->size / 2; i >= 1; i--) {
		SiftDown(h, i);
	}
}