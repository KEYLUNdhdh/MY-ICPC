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

/* 算法2-2：在顺序表list的第i个位置上插入元素x  Insert(list, i, x) */ 
void Insert(List list, Position i, ElemSet x)
{
	if(i <= 0 || i > list->last + 2)
	{
		printf("错误：插入位置不合法。\n");
		return;
	}
	else if(list->last + 1 == 10000)
	{
		printf("错误：表满不能插入。\n");
		return;
	}

	list->last++;
	for (int pos = list->last; pos >= 0;pos--)
	{	
		if(pos == i - 1)
		{
			list->data[pos] = x;
			break;
		}
		else
			list->data[pos] = list->data[pos - 1];
	}
	
	return;
}

/* 算法2-2 结束 */ 

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
	scanf("%d %d", &i, &x);
	Insert(list, i, x);
	for (i=0; i<=list->last; i++) {
		printf("%d ", list->data[i]);
	}
	return 0;
}

