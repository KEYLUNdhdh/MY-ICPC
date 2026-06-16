#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
typedef int QElemSet;
#define NIL -1

typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct QueueNode *Queue;
struct QueueNode {
    int capacity;     /* 顺序队列的容量 */
    Position front;   /* 顺序队列的队首指针，初始化为0 */
    Position rear;    /* 顺序队列的队尾指针，初始化为0 */
    QElemSet *data;   /* 存储数据的数组 */
};

void InitQueue(Queue queue, int kMaxSize);
bool IsFull(Queue queue);
bool IsEmpty(Queue queue);
void EnQueue(Queue queue, QElemSet x);
QElemSet GetFront(Queue queue);
void DeQueue(Queue queue);
void DestroyQueue(Queue queue);

int main(void)
{
	int i, n, x;
	Queue queue;
	
	queue = (Queue)malloc(sizeof(struct QueueNode));
	scanf("%d", &n);
	InitQueue(queue, n);
	for (i=0; i<=n; i++) { /*最后一个输入用于测试队列满报错*/
		scanf("%d", &x);
		EnQueue(queue, x);
	}
	for (i=0; i<=n; i++) { /*最后一个操作用于测试队列空报错*/
		printf("%d\n", GetFront(queue));
		DeQueue(queue);
	}
	DestroyQueue(queue);
	
	return 0;
}

void InitQueue(Queue queue, int kMaxSize)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsFull(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsEmpty(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void DestroyQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法3-7：顺序队列的入队操作 EnQueue(queue, x) */ 
void EnQueue(Queue queue, QElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法3-7 结束 */ 

/* 算法3-8：顺序队列的查看队首操作 GetFront(queue) */ 
QElemSet GetFront(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法3-8 结束 */ 

/* 算法3-9：顺序队列的出队操作 DeQueue(queue) */ 
void DeQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法3-9 结束 */ 

