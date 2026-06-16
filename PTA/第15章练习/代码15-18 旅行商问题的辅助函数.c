/* 优先队列定义 */
typedef struct TreeNode *Tree;
struct TreeNode {
	Vertex idx; /* 顶点编号 */
	int lb; /* 下界函数值 */
	Tree parent; /* 指向该顶点在决策树中的父结点 */
	int cnt; /* 到达该顶点时，路径上的顶点数 */
};
typedef Tree HElemSet;
typedef int Position; /* 数组下标即为元素位置 */
typedef struct BinaryHeapNode *MinHeap;
struct BinaryHeapNode {
	HElemSet *data;  /* 数据元素数组 */
	int size;        /* 规模 */
	int capacity;    /* 容量 */
};

#define kMaxPQSize 362880 /* 预估算法需要的队列规模为(n-1)! */

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


bool IsEmpty(MinHeap h)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 优先队列定义 结束 */

int Min( int x, int y )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsLeaf(MGraph graph, Tree u)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int UpdateUB(MGraph graph, Tree u, int UB)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsNextV(MGraph graph, Tree u, Vertex v_idx)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int LB(MGraph graph, Tree u, Vertex v_idx)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


