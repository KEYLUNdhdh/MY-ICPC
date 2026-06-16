/* 链式队列定义 */
typedef Vertex QElemSet;
#define NIL -1 /* 顶点不存在时的返回值 */

typedef struct QueueNode *QPosition; /* 指针即结点位置 */
struct QueueNode {
    QElemSet data;    /* 存储数据 */
    QPosition next;   /* 链接队列中下一个元素的位置 */
};
typedef struct QueueHeadNode *Queue;
struct QueueHeadNode {
    int size;        /* 链接队列中当前元素个数 */
    QPosition front;  /* 链接队列的队首指针，初始化为NULL */
    QPosition rear;   /* 链接队列的队尾指针，初始化为NULL */
};


void InitQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsEmpty(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void EnQueue(Queue queue, QElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


QElemSet GetFront(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void DeQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void DestroyQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 链式队列定义结束 */

bool ExistPath( LGraph graph, Vertex u, Vertex v )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


