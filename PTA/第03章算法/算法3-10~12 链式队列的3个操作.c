#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int QElemSet;
#define NIL -1

typedef struct QueueNode *Position; /* 指针即结点位置 */
struct QueueNode {
    QElemSet data;    /* 存储数据 */
    Position next;   /* 链式队列中下一个元素的位置 */
};
typedef struct QueueHeadNode *Queue;
struct QueueHeadNode {
    int size;        /* 链式队列中当前元素个数 */
    Position front;  /* 链式队列的队首指针，初始化为NULL */
    Position rear;   /* 链式队列的队尾指针，初始化为NULL */
};

void InitQueue(Queue queue);
bool IsEmpty(Queue queue);
void EnQueue(Queue queue, QElemSet x);
QElemSet GetFront(Queue queue);
void DeQueue(Queue queue);
void DestroyQueue(Queue queue);

int main(void)
{
	int i, n, x;
	Queue queue;
	
	queue = (Queue)malloc(sizeof(struct QueueHeadNode));
	scanf("%d", &n);
	InitQueue(queue);
	for (i=0; i<n; i++) {
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

void InitQueue(Queue queue)
{
    queue->size = 0;
    queue->front = NULL;
    queue->rear = NULL;
}


bool IsEmpty(Queue queue)
{
    if(queue->size == 0)
        return 1;
    else
        return 0;
}


void DestroyQueue(Queue queue)
{
    if(IsEmpty(queue))
        return;
    Position head = queue->front;
    while(head != queue->rear)
    {
        Position tmp = head;
        head = head->next;
        free(tmp);
    }
    free(head);

    return;
}


/* 算法3-10：链式队列的入队操作 EnQueue(queue, x) */ 
void EnQueue(Queue queue, QElemSet x)
{
    Position new = (Position)malloc(sizeof(struct QueueNode));
    new->data = x;
    if(IsEmpty(queue))
    {
        queue->front = queue->rear = new;
        queue->size++;
    }
    else
    {
        queue->rear->next = new;
        queue->rear = queue->rear->next;
        queue->size++;
    }

    return;
}

/* 算法3-10 结束 */ 

/* 算法3-11：链式队列的查看队首操作 GetFront(queue) */ 
QElemSet GetFront(Queue queue)
{
    if(IsEmpty(queue))
    {
        printf("错误：队列为空。\n");
        return -1;
    }

    return queue->front->data;
}

/* 算法3-11 结束 */ 

/* 算法3-12：链式队列的出队操作 DeQueue(queue) */ 
void DeQueue(Queue queue)
{
    if(IsEmpty(queue))
    {
        printf("错误：队列为空。\n");
        return;
    }
    else if(queue->size == 1)
    {
        queue->size = 0;
        Position tmp = queue->front;
        queue->front = NULL;
        queue->rear = NULL;
        free(tmp);
    }
    else
    {
        queue->size--;
        Position tmp = queue->front;
        queue->front = queue->front->next;
        free(tmp);
    }
    return;
}

/* 算法3-12 结束 */ 

