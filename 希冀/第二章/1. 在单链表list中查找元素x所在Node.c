#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
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


// 本题要求实现
Node* Search(Node* head, int x)
{
    Node *tmp = head;
    while(tmp != NULL && tmp->data != x)
        tmp = tmp->next;
    return tmp;
}

// 释放链表内存
void FreeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Node* lst = CreateList(n);

    int x;
    scanf("%d", &x);
    Node* p = Search(lst, x);
    if (p != NULL) {
        printf("%d\n", p->data);
    } else {
        printf("%d is not found!\n", x);
    }

    FreeList(lst); // 释放内存
    return 0;
}