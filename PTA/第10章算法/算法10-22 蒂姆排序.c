#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 默认元素为整数*/
#define kMinRun 4
#define Swap(x, y) { ElemSet t = x; x = y; y = t; }

typedef struct RunNode *Runs;
struct RunNode {
	int start; /* 有序段在a中的起始下标 */
	int len;   /* 有序段长度 */
};

/* 堆栈定义及操作 */
typedef enum {false, true} bool;
typedef Runs SElemSet;
#define NIL NULL
typedef struct StackNode *Position; /* 指针即结点位置 */
struct StackNode {
    SElemSet data;   /* 存储数据 */
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
SElemSet Peek(Stack stack, int k);
void Pop (Stack stack);
void DestroyStack(Stack stack);
/* 堆栈定义及操作结束 */

void Reverse(ElemSet *a, int l, int r);
Runs GetRun(ElemSet *a, int l, int r);
void TwoWayMerge(ElemSet *a, int l, int m, int r);
void Merge(ElemSet *a, Stack stack);

/* 算法10-22：蒂姆排序 TimSort(a,l,r) */
void TimSort(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法10-22 结束 */ 

int main(void)
{
	ElemSet *a; /* 数组a的下标从0开始 */
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	TimSort(a, 0, n-1);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

/* 堆栈操作 */
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


SElemSet Peek(Stack stack, int k)
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

/* 堆栈操作结束 */

void Reverse(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


Runs GetRun(ElemSet *a, int l, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void TwoWayMerge(ElemSet *a, int l, int m, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void Merge(ElemSet *a, Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


