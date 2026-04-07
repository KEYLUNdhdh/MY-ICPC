#include <stdio.h>
#include <stdlib.h>

// 链表节点
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// 本题要求实现
int Find(ListNode* head, int m, int* err)
{
    int len = 0;
    ListNode *tmp = head;
    if(tmp == NULL)
    {
        *err = 1;
        return -1;
    }
    while(tmp != NULL)
    {
        tmp = tmp->next;
        len++;
    }
    // printf("%d\n", len);
    int pos = len + 1 - m;
    // printf("%d\n", pos);
    tmp = head;
    pos--;
    while(pos-- && tmp != NULL)
        tmp = tmp->next;
    if(tmp == NULL)
    {
        *err = 1;
        return -1;
    }
    else
    {
        *err = 0;
        return tmp->data;
    }
}
// 释放链表
void FreeList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int m, n;
    scanf("%d", &m);

    // 先读取链表数据长度
    int data[1000]; 
    n = 0;
    while (scanf("%d", &data[n]) == 1) {
        n++;
        if (getchar() == '\n') break; // 读到行尾停止
    }

    // 创建链表
    ListNode* head = NULL;
    ListNode* current = NULL;
    for (int i = 0; i < n; i++) {
        ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
        new_node->data = data[i];
        new_node->next = NULL;
        if (!head) {
            head = current = new_node;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }

    int err;
    int result = Find(head, m, &err);
    if (err) {
        printf("ERROR\n");
    } else {
        printf("%d\n", result);
    }

    FreeList(head);
    return 0;
}