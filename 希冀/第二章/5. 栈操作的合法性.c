#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 栈结构体
typedef struct {
    int capacity;
    int top;
    int *data;
} Stack;

// 初始化栈
void init_stack(Stack *stack, int size) {
    stack->capacity = size;
    stack->top = -1;
    stack->data = (int*)malloc(size * sizeof(int));
}

// 判断是否满
int is_full(Stack *stack) {
    return stack->top + 1 == stack->capacity;
}

// 判断是否空
int is_empty(Stack *stack) {
    return stack->top == -1;
}

// 入栈
int push(Stack *stack, int x) {
    if (is_full(stack)) return 0;
    stack->data[++stack->top] = x;
    return 1;
}

// 出栈
int pop(Stack *stack) {
    if (is_empty(stack)) return 0;
    stack->top--;
    return 1;
}

// 清空栈
void clear(Stack *stack) {
    stack->top = -1;
}

// 销毁栈
void destroy_stack(Stack *stack) {
    free(stack->data);
    stack->data = NULL;
}

// 本题要求实现
int is_valid_stack_sequence(const char *sequence, int max_capacity)
{
    Stack *st = (Stack *)malloc(sizeof(Stack));
    init_stack(st, max_capacity);
    int i = 0;
    for (int i = 0; sequence[i] != '\0';i++)
    {
        char ch = sequence[i];
        if(ch == 'S')
        {
            int res = push(st, ch);
            if(!res)
                return 0;
        }
        else
        {
            if(is_empty(st))
                return 0;
            pop(st);
        }
    }
    if(is_empty(st))
        return 1;
    else
        return 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        char sequence[1005]; 
        scanf("%s", sequence);
        if (is_valid_stack_sequence(sequence, m)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}