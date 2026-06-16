#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* 链式队列及其操作 */
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
QElemSet GetRear(Queue queue); /* 查看队尾 */
void DestroyQueue(Queue queue);
/* 链式队列及其操作 结束 */

bool TrainCarriageScheduling(QElemSet in_track[], Queue out_track, int n, int k);

int main(void)
{
	int i, n, k;
	QElemSet *in_track;
	Queue out_track;
	
	scanf("%d %d", &n, &k);
	in_track = (QElemSet *)malloc(sizeof(QElemSet)*n);
	out_track = (Queue)malloc(sizeof(struct QueueHeadNode));
    InitQueue(out_track);
    for (i=0; i<n; i++) {
		scanf("%d", &in_track[i]);
	}
	if (TrainCarriageScheduling(in_track, out_track, n, k) == true) {
		for (i=0; i<n; i++) {
			printf("%d\n", GetFront(out_track));
			DeQueue(out_track);
		}
	}
    else
        printf("错误：任务不可能完成。");
    DestroyQueue(out_track);
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


QElemSet GetRear(Queue queue)
{
    if(IsEmpty(queue))
    {
        printf("错误：队列为空。\n");
        return -1;
    }
    return queue->rear->data;
}


/* 算法3-15：车厢重排 TrainCarriageScheduling(in_track, out_track, n, k) */
bool TrainCarriageScheduling(QElemSet in_track[], Queue out_track, int n, int k)
{
    Queue *tmp = (Queue*)malloc(n * (sizeof(Queue)));
    int cnt = 0;
    int need = 1;
    for (int i = 0; i < n;i++)
    {
        int num = in_track[i];
        if(num == need)
        {
            need++;
            if(need > n)
            {
                goto qqq;
            }
            continue;
        }
        else
        {
            int maxx = 0, pos = -1;
            for (int i = 0; i < cnt;i++)
            {
                if(num > GetRear(tmp[i]))
                {
                    if(maxx < GetRear(tmp[i]))
                    {
                        maxx = GetRear(tmp[i]);
                        pos = i;
                    }
                }
            }

            if(pos == -1)
            {
                if(cnt >= k)
                    return 0;
                tmp[cnt] = (Queue)malloc(sizeof(struct QueueHeadNode));
                InitQueue(tmp[cnt]);
                EnQueue(tmp[cnt], num);
                cnt++;
            }
            else
                EnQueue(tmp[pos], num);
        }
    }

qqq:
    int *pos = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n;i++)
    {
        pos[in_track[i]] = i;
    }
    for (int i = 1; i <= n;i++)
        EnQueue(out_track, pos[i]);
    return 1;
}

/* 算法3-15 结束 */ 

