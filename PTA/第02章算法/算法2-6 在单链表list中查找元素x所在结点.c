#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet;
 
typedef struct ListNode *Position; /* 指针即结点位置 */
struct ListNode {
    ElemSet data; /* 存储数据*/
    Position next; /* 线性表中下一个元素的位置 */
};
typedef struct HeadNode *List;
struct HeadNode {
    Position head; /* 单链表头指针 */
    int length;    /* 表长 */
};


/* 算法2-6：在单链表list中查找元素x所在结点  Search(list, x) */ 
Position Search( List list, ElemSet x )
{
	int pos = -1;
	Position head = list->head;
	int cur = 1;
	Position tmp = NULL;
	while(head)
	{
		if(head->data == x)
		{
			tmp = head;
			break;
		}
		cur++;
		head = head->next;
	}
		return tmp;
}


/* 算法2-6 结束 */ 

int main(void)
{
	int i, n, x;
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
	scanf("%d", &x);
	tmp = Search(list, x);
	if (tmp == NULL) printf("%d 未找到。\n", x);
	else printf("%d\n", tmp->data);
	return 0;
}

