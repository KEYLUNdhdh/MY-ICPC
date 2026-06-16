#include <stdio.h>
#include <stdlib.h>

#define kMaxStr 101 /* 输入序列最大长度+1 */
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
bool Push (Stack stack, SElemSet x); /* 增加返回操作成功与否的标识 */
bool Pop (Stack stack);              /* 增加返回操作成功与否的标识 */
void Clear(Stack stack);             /* 清空栈中所有元素 */ 
void DestroyStack(Stack stack);

int main(void)
{
	int n, m, i, j;
	char str[kMaxStr];
	Stack stack;
	
	stack = (Stack)malloc(sizeof(struct StackNode));
	scanf("%d %d\n", &n, &m);
	InitStack(stack, m);
    for (i=0; i<n; i++) {
    	scanf("%s", str);
        Clear(stack);
        for ( j=0; str[j]!='\0'; j++ ) {
			if ((str[j]=='S') && (Push(stack, 1)==false)) {
        		break; /* 如果应该入栈但入栈不成功，则跳出循环 */
			}
			if ((str[j]=='X') && (Pop(stack)==false)) {
				break; /* 如果应该出栈但出栈不成功，则跳出循环 */
			}
		}
        if ((str[j]=='\0') && (IsEmpty(stack)==true)) {
        	printf("YES\n"); /* 若输入序列正常处理完，且栈为空，则序列合法 */
		}
        else {
        	printf("NO\n");
		}
    }
	DestroyStack(stack);
	
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


bool Push (Stack stack, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool Pop (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Clear(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void DestroyStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


