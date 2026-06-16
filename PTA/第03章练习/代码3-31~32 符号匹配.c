#include <stdio.h>
#include <stdlib.h>

#define kMaxStackSize 100 /* 栈的最大容量 */
/* 配对符号类型。依次对应： */
/* 程序结尾、左注释、右注释、{、}、[、]、(、)、其它符号 */
typedef enum{ end, lc, rc, lbrc, rbrc, lbrkt, rbrkt, lpr, rpr, others } Token;
typedef Token SElemSet; /* 栈中元素类型为Token */

/* 顺序栈的定义及操作参见代码3-1至3-5，此处略去 */
typedef enum {false, true} bool;
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
/* 顺序栈结束 */

/* 匹配结果类型，依次对应：匹配成功、左半符不匹配、右半符不匹配 */
typedef enum{ ok, left_no_match, right_no_match } ErrorCode;
typedef struct ResultNode *Result;
struct ResultNode { /* 符号匹配结果存储结点 */
	ErrorCode code; /* 匹配结果 */
	Token token;    /* 匹配不成功的符号类型 */
};

Token GetToken(char c);
bool IsMatched(Token left, Token right);
Result SymbolMatching();
void PrintSymbol(Token token);

int main(void)
{
	Result result;
	
	result = SymbolMatching(); /* 读入程序并执行匹配 */
	if (result->code == ok) {  /* 若匹配成功 */
		printf("YES\n");
	}
	else { /* 若匹配不成功 */
		printf("NO\n");
		if (result->code == left_no_match) { /* 左半符不匹配 */
			PrintSymbol(result->token);
			printf("-?\n");
		}
		else { /* 右半符不匹配 */
			printf("?-");
			PrintSymbol(result->token);
			printf("\n");
		}
	}
	return 0;
}

Token GetToken(char c)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


bool IsMatched(Token left, Token right)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void PrintSymbol(Token token)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


Result SymbolMatching()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
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


