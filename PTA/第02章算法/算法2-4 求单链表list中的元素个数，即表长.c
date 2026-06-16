#include <stdio.h>
#include <stdlib.h>

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


/* 算法2-4：求单链表list中的元素个数，即表长  Length (list) */ 
int Length( List list )
{
	int cnt = 0;
	Position head = list->head;
	while(head)
	{
		cnt++;
		head = head->next;
	}
	return cnt;
}

/* 算法2-4 结束 */ 

int main(void)
{
	int i, n;
	Position tmp;
	List list;
	
	list = (List)malloc(sizeof(struct HeadNode));
	list->head = NULL;
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		tmp = (Position)malloc(sizeof(struct ListNode));
		if (tmp == NULL) {
			printf("错误：内存空间不足。\n");
			break;
		} 
		scanf("%d", &tmp->data); /* 读入一个结点的数据 */
		tmp->next = list->head;  /* 将新结点插入链表头 */
		list->head = tmp;
	}
	list->length = Length(list); /* 获取表长 */
	printf("%d\n", list->length);
	return 0;
}

