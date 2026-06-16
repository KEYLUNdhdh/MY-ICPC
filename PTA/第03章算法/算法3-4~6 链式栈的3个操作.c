#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
typedef int SElemSet;  /* 栈元素类型为int型 */
#define NIL -1

typedef struct StackNode *Position; /* 指针即结点位置 */
struct StackNode {
    SElemSet data;  /* 存储数据 */
    Position next;  /* 链式栈中下一个元素的位置 */
};
typedef struct StackHeadNode *Stack;
struct StackHeadNode {
    int size;       /* 链式栈中当前元素个数 */
    Position top;   /* 链式栈的栈顶指针，初始化为NULL */
};

void InitStack(Stack stack);
bool IsEmpty(Stack stack);
void Push (Stack stack, SElemSet x);
SElemSet Top (Stack stack);
void Pop (Stack stack);
void DestroyStack(Stack stack);

int main(void)
{
	int i, n, x;
	Stack stack;
	
	stack = (Stack)malloc(sizeof(struct StackHeadNode));
	scanf("%d", &n);
	InitStack(stack);
	for (i=0; i<n; i++) {
		scanf("%d", &x);
		Push(stack, x);
	}
	for (i=0; i<=n; i++) { /*最后一个操作用于测试栈空报错*/
		printf("%d\n", Top(stack));
		Pop(stack);
	}
	DestroyStack(stack);
	
	return 0;
}

void InitStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsEmpty(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void DestroyStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法3-4：链式栈的入栈操作 Push (stack, x) */ 
void Push (Stack stack, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法3-4 结束 */ 

/* 算法3-5：链式栈的取顶操作 Top (stack) */ 
SElemSet Top (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法3-5 结束 */ 

/* 算法3-6：链式栈的出栈操作 Pop (stack) */ 
void Pop (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法3-6 结束 */ 

