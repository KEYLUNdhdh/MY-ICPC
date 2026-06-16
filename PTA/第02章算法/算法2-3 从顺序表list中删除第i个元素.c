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


/* 算法2-3：从顺序表list中删除第i个元素  Remove (list, i) */ 
void Remove( List list, Position i )
{
	i--;
	if(i < 0 || i >= list->last + 1)
	{
		printf("错误：不存在这个元素。\n");
		return;
	}
	list->last--;
	for (int pos = i; pos <= list->last;pos++)
	{
		list->data[pos] = list->data[pos + 1];
	}
	
}

/* 算法2-3 结束 */ 

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
	scanf("%d", &i);
	Remove (list, i);
	for (i=0; i<=list->last; i++) {
		printf("%d ", list->data[i]);
	}
	return 0;
}

