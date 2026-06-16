#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 100000
typedef int ElemSet;
 
typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct ListNode *List;
struct ListNode {
    ElemSet data[kMaxSize]; /* 存储数据的数组 */
    Position last; /* 线性表中最后一个元素在数组中的位置 */
};

List ReadInput();
Position LongestCIS(List list);
void PrintResult(List list, Position left);

int main(void)
{
	List list;
	Position left;
	
	list = ReadInput(); /* 读入整个序列 */
	left = LongestCIS(list); /* 获得最长连续递增子序列最左端点 */
	PrintResult(list, left); /* 输出从left开始的连续递增子序列 */
	
	return 0;
}


List ReadInput()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


Position LongestCIS(List list)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void PrintResult(List list, Position left)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


