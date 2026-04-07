#include <stdio.h>
#include <stdlib.h>

// 链表节点
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建链表
Node* CreateList(int n) {
    Node* head = NULL;
    Node* current = NULL;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->data = x;
        new_node->next = NULL;
        if (i == 0) {
            head = current = new_node;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }
    return head;
}

// 打印链表
void PrintList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// 本题要求实现
void Remove(Node** head, int i)
{
    if(i < 1)
    {
        printf("position error\n");
        return;
    }
    if(i == 1)
    {
        Node *del = *head;
        (*head) = (*head)->next;
        free(del);
        del->next = NULL;
    }
    else
    {
        Node *pre = *head;
        i -= 2;
        while(i-- && pre != NULL)
            pre = pre->next;
        if(pre == NULL || pre->next == NULL)
        {
            printf("position error\n");
            return;
        }
        else
        {
            Node *del = pre->next;
            if(pre->next->next != NULL)
            {
                pre->next = pre->next->next;
                free(del);
                del->next = NULL;
            }
            else
            {
                pre->next = NULL;
                free(del);
                del->next = NULL;
            }
        }
    }
}
int main() {
    int n;
    scanf("%d", &n);
    Node* lst = CreateList(n);

    int i;
    scanf("%d", &i);
    Remove(&lst, i);
    PrintList(lst);

    // 释放剩余链表内存
    Node* current = lst;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}