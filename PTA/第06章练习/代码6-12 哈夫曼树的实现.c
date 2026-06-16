#include <stdio.h>
#include <stdlib.h>

/* 哈夫曼树的定义 */
typedef int TElemSet;
typedef struct BinaryTreeNode *HuffmanTree;
struct BinaryTreeNode {
    TElemSet weight;     /* 权重 */
    HuffmanTree left;    /* 左孩子指针 */
    HuffmanTree right;   /* 右孩子指针 */
};
/* 哈夫曼树的定义结束 */

/* 单根树集合的定义，即树结点的指针数组 */
#define kMaxSize 10000
#define NIL -1
typedef HuffmanTree ElemSet;
typedef struct ListNode *List;
struct ListNode {
    ElemSet data[kMaxSize]; /* 存储数据的数组 */
    int last; /* 线性表中最后一个元素在数组中的位置 */
};
void InitList( List list );
int Length( List list );
/* 单根树集合的定义结束 */ 

/* 树的集合的定义，即树结点的最小堆 */
typedef HuffmanTree HElemSet;
typedef int Position; /* 数组下标即为元素位置 */
typedef struct BinaryHeapNode *MinHeap;
struct BinaryHeapNode {
	HElemSet *data;  /* 数据元素数组 */
	int size;        /* 规模 */
	int capacity;    /* 容量 */
};
typedef MinHeap TreeSet;

void InitPQueue(MinHeap pq, int capacity);
void SiftUp(MinHeap h, Position i);
void SiftDown(MinHeap h, Position i);
void Insert(MinHeap h, HElemSet x);
HElemSet ExtractMin(MinHeap h);
void MakeHeapDown(MinHeap h);
void MakePQueue(MinHeap h, List list);
/* 树的集合的定义结束 */

HuffmanTree NewNode( TElemSet weight )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


HuffmanTree CreateHuffmanTree(List w)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int WPL( HuffmanTree tree, int depth )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int main(void)
{
	int n, i;
	List nodes;
	TElemSet w;
	HuffmanTree tree;
	
	scanf("%d", &n);
	nodes = (List)malloc(sizeof(struct ListNode));
	InitList(nodes);
	for (i=0; i<n; i++) {
		scanf("%d", &w);
		nodes->data[i] = NewNode(w);
		nodes->last++;
	}
	tree = CreateHuffmanTree(nodes);
	printf("%d\n", WPL(tree, 0));
	
	return 0;
}

void InitList( List list )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int Length( List list )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
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


void SiftDown(MinHeap h, Position i)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void Insert(MinHeap h, HElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


HElemSet ExtractMin(MinHeap h)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void MakeHeapDown(MinHeap h)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void MakePQueue(MinHeap h, List list)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


