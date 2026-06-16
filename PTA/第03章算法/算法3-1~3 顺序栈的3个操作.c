#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int SElemSet; /* 栈元素类型为int型 */
#define NIL -1

typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct StackNode *Stack;
struct StackNode {
    int capacity;     /* 顺序栈的容量 */
    Position top;     /* 顺序栈的栈顶指针，初始化为-1 */
    SElemSet *data;   /* 存储数据的数组 */
};

void InitStack(Stack stack, int kMaxSize);
bool IsFull(Stack stack);
bool IsEmpty(Stack stack);
void Push (Stack stack, SElemSet x);
SElemSet Top (Stack stack);
void Pop (Stack stack);
void DestroyStack(Stack stack);

int main(void)
{
	int i, n, x;
	Stack stack;
	
	stack = (Stack)malloc(sizeof(struct StackNode));
	scanf("%d", &n);
	InitStack(stack, n);
	for (i=0; i<=n; i++) { /*最后一个输入用于测试栈满报错*/
		scanf("%d", &x);
		Push(stack, x);
	}
	for (i=0; i<=n; i++) { /*最后一个操作用于测试栈空报错*/
		printf("%d\n", Top(stack));
		Pop(stack);
	}
	// DestroyStack(stack);
	
	return 0;
}

void InitStack(Stack stack, int kMaxSize)
{
    stack->top = -1;
    stack->capacity = kMaxSize;
    stack->data = (int *)malloc(sizeof(int) * kMaxSize);
}


bool IsFull(Stack stack)
{
    if(stack->top == stack->capacity - 1)
        return 1;
    else
        return 0;
}


bool IsEmpty(Stack stack)
{
    if(stack->top == -1)
        return 1;
    else
        return 0;
}


/* 算法3-1：顺序栈的入栈操作 Push (stack, x) */ 
void Push (Stack stack, SElemSet x)
{
    if(IsFull(stack))
    {
        printf("错误：栈已满。\n");
        return;
    }
    stack->top++;
    stack->data[stack->top] = x;
}

/* 算法3-1 结束 */ 

/* 算法3-2：顺序栈的取顶操作 Top (stack) */ 
SElemSet Top (Stack stack)
{
    if(IsEmpty(stack))
    {
        printf("错误：栈为空。\n");
        return -1;
    }
    return stack->data[stack->top];
}

/* 算法3-2 结束 */ 

/* 算法3-3：顺序栈的出栈操作 Pop (stack) */ 
void Pop (Stack stack)
{
    if(IsEmpty(stack))
    {
        printf("错误：栈为空。\n");
        return;
    }

    stack->top--;
}

/* 算法3-3 结束 */ 

void DestroyStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


