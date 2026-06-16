#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
#define infinity (1e9)
#define kSize 3  /* 棋盘规模为 kSize x kSize */
#define kMaxStates 362880 /* 共有 9! 种状态 */
typedef struct StateNode *States;
struct StateNode {
	long long s;    /* 用64位长整型存储棋盘 */
	int g;          /* 从初始状态到此状态的步数 */
	int f;          /* 从初始状态到此状态再到目标状态的步数 */
	States parent;  /* 记录到达此状态的前一个状态 */
};

/* 关于OPEN和CLOSED表的定义与操作 */
typedef struct TableNode *Tables;
struct TableNode {
	States t[kMaxStates];
	int size;
};

bool IsEmpty(Tables table)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsIn(Tables table, States state)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Insert(Tables table, States state)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void Remove(Tables table, States state)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


States ExtractMin(Tables table)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 关于OPEN和CLOSED表的定义与操作结束 */

/* 棋盘相关操作 */
long long MatrixToNumber (int m[][kSize])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void NumberToMatrix ( long long x, int m[][kSize])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void ReadConfig( States state )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


States NextConfig( States state, int direction )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 棋盘相关操作结束 */

int h(States X, States T)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Update(States Y, int new_cost, States X, States T)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法16-4：A算法 A ( h, init_state, goal_state) */
States A( int (*h)(States X, States T), States init_state, States goal_state)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法16-4 结束 */

void PrintSolution( States state )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	States init_state, goal_state;
	
	init_state = (States)malloc(sizeof(struct StateNode));
	ReadConfig(init_state);
	init_state->parent = NULL;
	goal_state = (States)malloc(sizeof(struct StateNode));
	ReadConfig(goal_state);
	goal_state = A(h, init_state, goal_state);
	if (goal_state != NULL) {
		PrintSolution(goal_state);
	}
	else {
		printf("No Solution.\n");
	}
	
	return 0;
}

