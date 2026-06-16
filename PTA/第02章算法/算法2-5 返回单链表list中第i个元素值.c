#include <stdio.h>
#include <stdlib.h>

#define ErrorCode -1 /* 假设正常元素值均不为 -1 */
typedef int ElemSet;
 
typedef struct ListNode *Position; /* 指针即结点位置 */
struct ListNode {
    ElemSet data;  /* 存储数据*/
    Position next;  /* 线性表中下一个元素的位置 */
};
typedef struct HeadNode *List;
struct HeadNode {
    Position head;  /* 单链表头指针 */
    int length;    /* 表长 */
};


/* 算法2-5：返回单链表list中第i个元素值  Get (list, i) */ 
ElemSet Get(List list, int i)
{
	if(i <= 0 || i > list->length)
	{
		return -1;
	}
	int cnt = 1;
	Position head = list->head;
	while(head)
	{
		// printf(":%d\n", head->data);
		if(cnt == i)
			return head->data;
		cnt++;
		head = head->next;
	}
	return -1;
}

/* 算法2-5 结束 */ 

int main(void)
{
	int i, n;
	Position tmp;
	List list;
	
	list = (List)malloc(sizeof(struct HeadNode));
	list->head = NULL;
	scanf("%d", &n);
	list->length = n;
	for (i=0; i<n; i++) {
		tmp = (Position)malloc(sizeof(struct ListNode));
		scanf("%d", &tmp->data); /* 读入一个结点的数据 */
		tmp->next = list->head;  /* 将新结点插入链表头 */
		list->head = tmp;
	}
	scanf("%d", &i);
	printf("%d\n", Get(list, i));
	return 0;
}

