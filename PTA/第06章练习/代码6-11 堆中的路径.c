#include <stdio.h>
#include <stdlib.h>

typedef int HElemSet;
typedef int Position; /* 数组下标即为元素位置 */
typedef struct BinaryHeapNode *MinHeap;
struct BinaryHeapNode {
	HElemSet *data;  /* 数据元素数组 */
	int size;        /* 规模 */
	int capacity;    /* 容量 */
};

void InitPQueue(MinHeap pq, int capacity);
void SiftUp(MinHeap h, Position i);
void Insert(MinHeap h, HElemSet x);

void Solve( int n, int m )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	int n, m;
	
	scanf("%d %d", &n, &m);
	Solve(n, m);
	
	return 0;
}

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


void Insert(MinHeap h, HElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


