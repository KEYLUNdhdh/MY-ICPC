#include <stdio.h>
#include <stdlib.h>

/* 不相交集的定义与操作 */
#define kMaxSize 10000             /* 集合最大元素个数 */
typedef int SElemSet;             /* 默认元素用非负整数表示 */
typedef SElemSet SetName;         /* 默认用根结点的下标作为集合名称 */
typedef struct SetNode {
	SElemSet parent;  /* 父结点 */
	int rank;         /* 秩 */ 
} Set[kMaxSize+1];    /* 假设集合元素下标从1开始 */

void InitSet(Set set, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 

SetName Find(Set set, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Union(Set set, SElemSet x, SElemSet y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 不相交集的定义与操作 结束 */

void InputConnection( Set set );      /* 处理I操作*/
void CheckConnection( Set set );      /* 处理C操作*/
void CheckNetwork( Set set , int n ); /* 处理S操作*/

int main(void)
{
	int n;
	char cmd;
	Set set;
	
	scanf("%d\n", &n);
	InitSet(set, n);
    do {
        scanf("%c", &cmd);
        switch (cmd) {
     	   case 'I': InputConnection( set ); break;
     	   case 'C': CheckConnection( set ); break;
     	   case 'S': CheckNetwork( set, n ); break;
     	   default: break;
        }
    } while ( cmd != 'S');
    
	return 0;
}

void InputConnection( Set set )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void CheckConnection( Set set )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void CheckNetwork( Set set , int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

