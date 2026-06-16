#include <stdio.h>
#include <stdlib.h>

/* 顺序栈的定义及操作 */
typedef enum {false, true} bool;
typedef int SElemSet;
#define NIL -1
typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct StackNode *Stack;
struct StackNode {
    int capacity;     /* 顺序栈的容量 */
    Position top;     /* 顺序栈的栈顶指针，初始化为-1 */
    SElemSet *data;    /* 存储数据的数组 */
};
void InitStack(Stack stack, int kMaxSize);
bool IsFull(Stack stack);
bool IsEmpty(Stack stack);
void Push (Stack stack, SElemSet x);
SElemSet Top (Stack stack);
void Pop (Stack stack);
void DestroyStack(Stack stack);
/* 顺序栈的定义及操作 结束 */

/* 两个栈组成队列的定义及操作 */
typedef struct QNode *Queue;
struct QNode { /* 队列由两个栈组成 */
	Stack s1, s2;
};
typedef struct DeQNode *DeQElem;
struct DeQNode { /* DeQueue返回值 */
	SElemSet x;  /* 出队元素的值 */
	int time;    /* 出队耗费的时间 */
};
void InitQueue(Queue queue, int kMaxSize);
void EnQueue(Queue queue, SElemSet x);
bool IsQEmpty(Queue queue);
void DeQueue(Queue queue, DeQElem elem);
void DestroyQueue(Queue queue);
/* 两个栈组成队列的定义及操作 结束 */

int main(void)
{
	int i, n;
	SElemSet x;
	char cmd;
	DeQElem elem;
	Queue queue;
	
	scanf("%d\n", &n);
	queue = (Queue)malloc(sizeof(struct QNode));
	InitQueue(queue, n); /* 队列初始化 */
	elem = (DeQElem)malloc(sizeof(struct DeQNode));
	for (i=0; i<n; i++) {
		scanf("%c ", &cmd);
		if (cmd=='I') { /* 如果是入队操作 */
			scanf("%d\n", &x);
			EnQueue(queue, x);
		}
		else { /* 如果是出队操作 */
			if (IsQEmpty(queue)) printf("ERROR\n");
			else {
				DeQueue(queue, elem);
				printf("%d %d\n", elem->x, elem->time);
			}
		}
	}
	DestroyQueue(queue);
	free(elem);
	
	return 0;
}

void InitStack(Stack stack, int kMaxSize)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsFull(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsEmpty(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Push (Stack stack, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


SElemSet Top (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Pop (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void DestroyStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void InitQueue(Queue queue, int kMaxSize)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void EnQueue(Queue queue, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsQEmpty(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void DeQueue(Queue queue, DeQElem elem)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void DestroyQueue(Queue queue)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


