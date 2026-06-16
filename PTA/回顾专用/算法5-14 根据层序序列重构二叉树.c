#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define kMaxSize 10
#define NILL -1 /* 假设数据为非负整数，NIL定义为非法数据，表示空 */
typedef int TElemSet;

typedef struct BinaryTreeNode *BinaryTree;
struct BinaryTreeNode {
    TElemSet data;      /* 数据元素 */
    BinaryTree left;    /* 左孩子指针 */
    BinaryTree right;   /* 右孩子指针 */
};

/* 链式队列定义 */
typedef BinaryTree QElemSet;
#define NIL NULL

typedef struct QueueNode *Position; /* 指针即结点位置 */
struct QueueNode {
    QElemSet data;   /* 存储数据 */
    Position next;   /* 链接队列中下一个元素的位置 */
};
typedef struct QueueHeadNode *Queue;
struct QueueHeadNode {
    int size;        /* 链接队列中当前元素个数 */
    Position front;  /* 链接队列的队首指针，初始化为NULL */
    Position rear;   /* 链接队列的队尾指针，初始化为NULL */
};


void InitQueue(Queue queue)
{
    queue->size = 0;
    queue->front = NULL;
    queue->rear = NULL;
}


bool IsEmpty(Queue queue)
{
    if(queue->size == 0)
        return 1;
    else
        return 0;
}


void DestroyQueue(Queue queue)
{
    if(IsEmpty(queue))
        return;
    Position head = queue->front;
    while(head != queue->rear)
    {
        Position tmp = head;
        head = head->next;
        free(tmp);
    }
    free(head);

    return;
}


/* 算法3-10：链式队列的入队操作 EnQueue(queue, x) */ 
void EnQueue(Queue queue, QElemSet x)
{
    Position new = (Position)malloc(sizeof(struct QueueNode));
    new->data = x;
    if(IsEmpty(queue))
    {
        queue->front = queue->rear = new;
        queue->size++;
    }
    else
    {
        queue->rear->next = new;
        queue->rear = queue->rear->next;
        queue->size++;
    }

    return;
}

/* 算法3-10 结束 */ 

/* 算法3-11：链式队列的查看队首操作 GetFront(queue) */ 
QElemSet GetFront(Queue queue)
{
    if(IsEmpty(queue))
    {
        printf("错误：队列为空。\n");
        return NULL;
    }

    return queue->front->data;
}

/* 算法3-11 结束 */ 

/* 算法3-12：链式队列的出队操作 DeQueue(queue) */ 
void DeQueue(Queue queue)
{
    if(IsEmpty(queue))
    {
        printf("错误：队列为空。\n");
        return;
    }
    else if(queue->size == 1)
    {
        queue->size = 0;
        Position tmp = queue->front;
        queue->front = NULL;
        queue->rear = NULL;
        free(tmp);
    }
    else
    {
        queue->size--;
        Position tmp = queue->front;
        queue->front = queue->front->next;
        free(tmp);
    }
    return;
}

/* 算法3-12 结束 */ 

/* 队列定义结束*/ 

BinaryTree CreateBinaryTree(TElemSet value, BinaryTree left_tree, BinaryTree right_tree )
{
    BinaryTree node = (BinaryTree)malloc(sizeof(struct BinaryTreeNode));
    node->data = value;
    node->left = left_tree;
    node->right = right_tree;
    return node;
}


void Visit(BinaryTree tree)
{
	printf("%d\n", tree->data);
}



void LevelOrder(BinaryTree tree)
{
    Queue queue = (Queue)malloc(sizeof(struct QueueNode));
    InitQueue(queue);

    if(tree == NULL)
        return;

    EnQueue(queue, tree);
    while(!IsEmpty(queue))
    {
        int len = queue->size;
        while(len--)
        {
            BinaryTree tmp = GetFront(queue);
            printf("%d\n", tmp->data);
            DeQueue(queue);
            if(tmp->left)
                EnQueue(queue, tmp->left);
            if (tmp->right)
                EnQueue(queue, tmp->right);
        }
    }

    return;
}


/* 算法5-14：根据层序序列重构二叉树 LevelOrderDeSerialize(levelorder, n) */
BinaryTree LevelOrderDeSerialize(TElemSet levelorder[], int n)
{
    // 空树处理
    if(n == 0 || levelorder[0] == NILL)
        return NULL;

    Queue queue = (Queue)malloc(sizeof(struct QueueNode));
    InitQueue(queue);
    
    BinaryTree tree = CreateBinaryTree(levelorder[0], NULL, NULL);
    int idx = 1;

    EnQueue(queue, tree);
    while(idx < n && !IsEmpty(queue))
    {
        BinaryTree pa = GetFront(queue);
        DeQueue(queue);

        // 处理左孩子
        if(levelorder[idx] != NILL){
            pa->left = CreateBinaryTree(levelorder[idx], NULL, NULL);
            EnQueue(queue, pa->left);
        } else {
            pa->left = NULL;
        }
        idx++;
        if(idx >= n) break;

        // 处理右孩子
        if(levelorder[idx] != NILL){
            pa->right = CreateBinaryTree(levelorder[idx], NULL, NULL);
            EnQueue(queue, pa->right);
        } else {
            pa->right = NULL;
        }
        idx++;
    }
    DestroyQueue(queue);
    free(queue);
    return tree;
}

/* 算法5-14 结束 */ 

int main(void)
{
	BinaryTree tree;
	TElemSet *levelorder;
	char s[kMaxSize];
	int n, i;
	
	scanf("%d\n", &n);
	levelorder = (TElemSet *)malloc(sizeof(TElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%s ", s);
		if (s[0] == '#') {
			levelorder[i] = NILL;
		}
		else {
			levelorder[i] = atoi(s);
		}
	}
	tree = LevelOrderDeSerialize(levelorder, n);
	LevelOrder(tree);
	 
	return 0;
}

