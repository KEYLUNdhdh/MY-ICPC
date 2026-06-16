#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 哈夫曼树的定义 */
typedef int TElemSet;
typedef struct BinaryTreeNode *HuffmanTree;
struct BinaryTreeNode {
    TElemSet weight;     /* 权重 */
    char data;           /* 字符 */
    HuffmanTree left;    /* 左孩子指针 */
    HuffmanTree right;   /* 右孩子指针 */
};
/* 哈夫曼树的定义结束 */

/* 树的集合的定义，即树结点的单链表 */
typedef HuffmanTree SetType;
typedef struct SetNode *Position; /* 指针即结点位置 */
struct SetNode {
    SetType data;  /* 存储数据*/
    Position next; /* 线性表中下一个元素的位置 */
};
typedef struct HeadNode *TreeSet;
struct HeadNode {
    Position head; /* 单链表头指针 */
    int length;    /* 表长 */
};

//传入实参，因为我们要对tree_set本省进行修改
void InitTreeSet(TreeSet *tree_set)
{
    *tree_set = (TreeSet)malloc(sizeof(struct HeadNode));
    (*tree_set)->head = NULL;
    (*tree_set)->length = 0;
}

void Insert(TreeSet tree_set, SetType tree)
{
    // 按题目要求，新结点插入表头
    Position tmp = (Position)malloc(sizeof(struct SetNode));
    tmp->data = tree;
    tmp->next = tree_set->head;
    tree_set->head = tmp;
    tree_set->length++;
}

SetType ExtractMin(TreeSet tree_set)
{
    Position pre = NULL, cur = tree_set->head;
    Position minpre = NULL, mincur = NULL;
    int min_weight = 1000000;

    // 遍历找最小权值，权重相同取先遇到的（靠近表头的）
    while (cur)
    {
        int current_weight = cur->data->weight;
        if (current_weight < min_weight)
        {
            min_weight = current_weight;
            minpre = pre;
            mincur = cur;
        }
        pre = cur;
        cur = cur->next;
    }

    // 从链表中删除该结点
    tree_set->length--;
    if (minpre == NULL) {
        // 最小结点就是表头
        tree_set->head = tree_set->head->next;
    } else {
        minpre->next = mincur->next;
    }

    return mincur->data;
}

/* 树的集合的定义结束 */

/* 权重集合的定义，即权重的数组 */
#define kMaxSize 10000
typedef TElemSet ElemSet;
typedef struct ListNode *List;
struct ListNode {
    ElemSet data[kMaxSize]; /* 存储数据的数组 */
    char c[kMaxSize];       /* 存储字符的数组 */
    int last; /* 线性表中最后一个元素在数组中的位置 */
};

void InitList( List list )
{
    list->last = -1;
}

int Length( List list )
{
    return (list->last + 1);
}

/* 权重集合的定义结束 */

HuffmanTree CreateHuffmanTree(List w)
{
    TreeSet treeset;
    InitTreeSet(&treeset);

    // 把所有叶子结点加入森林
    for (int i = 0; i <= w->last; i++)
    {
        HuffmanTree node = (HuffmanTree)malloc(sizeof(struct BinaryTreeNode));
        node->weight = w->data[i];
        node->data = w->c[i];
        node->left = NULL;
        node->right = NULL;
        Insert(treeset, node);
    }

    // 合并直到只剩一棵树
    while(treeset->length != 1)
    {
        // 第一个最小为左，第二个为右
        HuffmanTree min1 = ExtractMin(treeset);
        HuffmanTree min2 = ExtractMin(treeset);

        HuffmanTree parent = (HuffmanTree)malloc(sizeof(struct BinaryTreeNode));
        parent->weight = min1->weight + min2->weight;
        parent->data = '\0'; // 非叶子结点存空字符
        parent->left = min1;
        parent->right = min2;

        Insert(treeset, parent);
    }

    HuffmanTree root = ExtractMin(treeset);
    free(treeset);
    return root;
}

/* 算法5-16：对二进制字符串解码 Decoding */
void Decoding(HuffmanTree tree, char binary_code[])
{
    HuffmanTree cur = tree; // 从根结点开始
    int len = strlen(binary_code);

    for (int i = 0; i < len; i++)
    {
        // 0走左，1走右
        if (binary_code[i] == '0') {
            cur = cur->left;
        } else {
            cur = cur->right;
        }

        // 遇到叶子结点：输出字符，回到根结点开始下一个字符
        if (cur->left == NULL && cur->right == NULL)
        {
            putchar(cur->data);
            cur = tree;
        }
    }
    putchar('\n');
}

int main(void)
{
	int n, i;
	List w;
	HuffmanTree tree;
	char binary_code[kMaxSize];

	scanf("%d\n", &n);
	w = (List)malloc(sizeof(struct ListNode));
	InitList(w);
	for (i=0; i<n; i++) {
		scanf("%c %d\n", &w->c[i], &w->data[i]);
		w->last++;
	}
	tree = CreateHuffmanTree(w);
	scanf("%s\n", binary_code);
	Decoding(tree, binary_code);

	return 0;
}
