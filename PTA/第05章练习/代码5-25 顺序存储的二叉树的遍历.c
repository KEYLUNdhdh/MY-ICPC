/* 链式堆栈定义 */
typedef enum {false, true} bool;
typedef int SElemSet; /* 栈元素为数组下标 */
#define NILElem 0     /* 0下标表示空元素 */

typedef struct StackNode *Position; /* 指针即结点位置 */
struct StackNode {
    SElemSet data;   /* 存储数据 */
    Position next;  /* 链接栈中下一个元素的位置 */
};
typedef struct StackHeadNode *Stack;
struct StackHeadNode {
    int size;       /* 链接栈中当前元素个数 */
    Position top;   /* 链接栈的栈顶指针，初始化为NULL */
};

void InitStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool IsEmpty(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Push (Stack stack, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


SElemSet Top (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Pop (Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void DestroyStack(Stack stack)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 堆栈定义结束*/ 

void Visit(BinaryTree tree, int idx)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool NotNIL(BinaryTree tree, int idx)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void PreOrder(BinaryTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void InOrder(BinaryTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void PostOrder(BinaryTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


