#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int k = -1; // 当前处理的序列下标

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// 创建新结点
Node* CreateBinaryTree(char data) {
    Node* tree = (Node*)malloc(sizeof(Node));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

// 根据先序序列创建二叉树
Node* PreOrderDeSerialize(char* preorder, int n) {
    k++;
    Node* tree = NULL;
    if (k < n) {
        char data = preorder[k];
        if (data != '#') {
            tree = CreateBinaryTree(data);
            tree->left = PreOrderDeSerialize(preorder, n);
            tree->right = PreOrderDeSerialize(preorder, n);
        }
    }
    return tree;
}

// 栈定义
typedef struct {
    Node* data[1000];
    int top;
} Stack;

void InitStack(Stack* s) { s->top = -1; }
int IsEmpty(Stack* s) { return s->top == -1; }
void Push(Stack* s, Node* node) { s->data[++s->top] = node; }
Node* Pop(Stack* s) { if (!IsEmpty(s)) return s->data[s->top--]; else return NULL; }
Node* Top(Stack* s) { if (!IsEmpty(s)) return s->data[s->top]; else return NULL; }

// 非递归中序遍历
// 本题要求实现
void InOrder(Node* tree)
{
    Node *cur = tree;
    Stack *s = (Stack*)malloc(sizeof(Stack));
    InitStack(s);
    while(cur || !IsEmpty(s))
    {
        while(cur)
        {
            Push(s, cur);
            cur = cur->left;
        }
        cur = Top(s);
        Pop(s);
        printf("%c ", cur->data);
        cur = cur->right;
    }
    return;
}

int main() {
    char preorder[1000];
    if (fgets(preorder, sizeof(preorder), stdin) == NULL) return 0;

    // 去掉换行符
    size_t len = strlen(preorder);
    if (len > 0 && preorder[len - 1] == '\n') preorder[len - 1] = '\0';

    k = -1;
    Node* tree = PreOrderDeSerialize(preorder, strlen(preorder));
    InOrder(tree);
    printf("\n");
    return 0;
}