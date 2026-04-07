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

// 本题要求实现。
int Insert(Node** head, int i, int x)
{
    if(i < 1)
        return 0;
    if(i == 1)
    {
        Node *tmp = (Node*)malloc(sizeof(Node));
        tmp->data = x;
        tmp->next = (*head);
        (*head) = tmp;
        return 1;
    }
    else
    {
        Node *pre = (*head);
        i -= 2;
        while(i-- && pre != NULL)
            pre = pre->next;
        if(pre == NULL)
        {
            return 0;
        }
        else
        {
            Node *tmp = (Node*)malloc(sizeof(Node));
            tmp->data = x;
            tmp->next = pre->next;
            pre->next = tmp;
            return 1;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Node* lst = CreateList(n);

    int i, x;
    scanf("%d %d", &i, &x);
    if (Insert(&lst, i, x)) {
        PrintList(lst);
    } else {
        printf("position error\n");
    }

    // 释放链表内存
    Node* current = lst;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}