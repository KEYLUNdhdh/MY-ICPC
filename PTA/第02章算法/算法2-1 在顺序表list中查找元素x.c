#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 10000
#define NIL -1
typedef int ElemSet;
 
typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct ListNode *List;
struct ListNode {
    ElemSet data[kMaxSize]; /* 存储数据的数组 */
    Position last; /* 线性表中最后一个元素在数组中的位置 */
};


/* 算法2-1： 在顺序表list中查找元素x  Search(list, x) */ 
Position Search(List list, ElemSet x)
{
	Position pos = -1;
	for (int i = 0; i <= list->last;i++)
	{
		if(list->data[i] == x)
		{
			pos = i;
			break;
		}
	}
	return pos;
}

/* 算法2-1 结束 */ 

int main(void)
{
	int i, n, x;
	List list;
	
	list = (List)malloc(sizeof(struct ListNode));
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		scanf("%d", &list->data[i]);
	}
	list->last = n-1;
	scanf("%d", &x);
	printf("%d\n", Search(list, x));
	return 0;
}

