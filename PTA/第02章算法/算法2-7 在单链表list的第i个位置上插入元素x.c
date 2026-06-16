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


/* 算法2-7：在单链表list的第i个位置上插入元素x  Insert (list, i, x) */ 
void Insert (List list, int i, ElemSet x)
{
	Position prev, cur;
	if()
}

/* 算法2-7 结束 */ 

int main(void)
{
	int i, n, x;
	Position p;
	List list;
	
	list = (List)malloc(sizeof(struct HeadNode));
	list->head = NULL;
	list->length = 0;
	scanf("%d", &n);
	for (i=1; i<=n; i++) {
		scanf("%d", &x);
		Insert(list, i, x);
	}
	printf("%d:", list->length);
	p = list->head;
	while (p != NULL) {
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
	Insert(list, 0, x);
	Insert(list, n+2, x);
	return 0;
}

