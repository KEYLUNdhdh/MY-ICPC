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


/* 算法2-8：从单链表list中删除第i个元素 Remove (list, i) */ 
void Remove ( List list, int i )
{
    if(i < 1 || i > list->length)
	{
		printf("错误：删除位置不合法。\n");
		return;
	}

	list->length--;
	Position pre = NULL, cur = list->head;
	int pos = 1;
	while(pos != i)
	{
		pre = cur;
		cur = cur->next;
		pos++;
	}

	if(pre == NULL)
	{
		list->head = list->head->next;
	}
	else
	{
		pre->next = cur->next;
	}

	return;
}

/* 算法2-8 结束 */ 

int main(void)
{
	int i, n;
	Position tmp;
	List list;
	
	list = (List)malloc(sizeof(struct HeadNode));
	list->head = NULL;
	list->length = 0;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		tmp = (Position)malloc(sizeof(struct ListNode));
		scanf("%d", &tmp->data); /* 读入一个结点的数据 */
		tmp->next = list->head;  /* 将新结点插入链表头 */
		list->head = tmp;
		list->length++;
	}
	scanf("%d", &i);
	Remove(list, i);
	tmp = list->head;
	printf("%d:", list->length);
	while (tmp != NULL) {
		printf(" %d", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	return 0;
}

