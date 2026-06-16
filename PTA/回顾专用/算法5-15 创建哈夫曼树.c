#include <stdio.h>
#include <stdlib.h>

/* 哈夫曼树的定义 */
typedef int TElemSet;
typedef struct BinaryTreeNode *HuffmanTree;
struct BinaryTreeNode {
    TElemSet weight;     /* 权重 */
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

void InitTreeSet(TreeSet *tree_set)
{
    *tree_set = (TreeSet)malloc(sizeof(struct HeadNode));
    (*tree_set)->head = NULL;
    (*tree_set)->length = 0;
}


void Insert(TreeSet tree_set, SetType tree)
{
    int len = tree_set->length;
    Position tmp = (Position)malloc(sizeof(struct SetNode));
    tmp->data = tree;
    tmp->next = NULL;
    tmp->next = tree_set->head;
    tree_set->head = tmp;
    tree_set->length++;
}


SetType ExtractMin(TreeSet tree_set)
{
    Position pre = NULL, cur = tree_set->head, minpre, mincur;
    int min = 1000000;
    while(cur)
    {
        int num = cur->data->weight;
        if(num < min)
        {
            min = num;
            minpre = pre;
            mincur = cur;
        }
        pre = cur;
        cur = cur->next;
    }

    tree_set->length--;
    if(minpre)
    {
        minpre->next = mincur->next;
    }
    else
    {
        tree_set->head = tree_set->head->next;
    }

    return mincur->data;
}

/* 树的集合的定义结束 */

/* 权重集合的定义，即权重的数组 */
#define kMaxSize 10000
#define NIL -1
typedef TElemSet ElemSet;
typedef struct ListNode *List;
struct ListNode {
    ElemSet data[kMaxSize]; /* 存储数据的数组 */
    int last; /* 线性表中最后一个元素在数组中的位置 */
};


void InitList( List list )
{
    list->last = -1;
    return;
}


int Length( List list )
{
    return (list->last + 1);
}

/* 权重集合的定义结束 */ 

/* 算法5-15：创建哈夫曼树 CreateHuffmanTree(w) */ 
HuffmanTree CreateHuffmanTree(List w)   
{
    TreeSet treeset;
    InitTreeSet(&treeset);

    for (int i = 0; i <= w->last;i++)
    {
        HuffmanTree node = (HuffmanTree)malloc(sizeof(struct BinaryTreeNode));
        node->weight = w->data[i];
        node->left = NULL;
        node->right = NULL;
        Insert(treeset, node);
    }

    while(treeset->length != 1)
    {
        HuffmanTree min1 = ExtractMin(treeset);
        HuffmanTree min2 = ExtractMin(treeset);

        HuffmanTree pa = (HuffmanTree)malloc(sizeof(struct BinaryTreeNode));
        pa->weight = min1->weight + min2->weight;
        pa->left = min1;
        pa->right = min2;

        Insert(treeset, pa);
    }

    HuffmanTree head = ExtractMin(treeset);
    free(treeset);
    return head;
}

/* 算法5-15 结束 */ 

int WPL( HuffmanTree tree, int depth )
{
    // 空结点，贡献0
    if (tree == NULL)
        return 0;
    // 叶子结点，贡献 权重 * 深度
    if (tree->left == NULL && tree->right == NULL)
        return tree->weight * depth;
    // 非叶子结点，递归累加左右子树的WPL
    return WPL(tree->left, depth + 1) + WPL(tree->right, depth + 1);
}


int main(void)
{
	int n, i;
	List w;
	HuffmanTree tree;
	
	scanf("%d", &n);
	w = (List)malloc(sizeof(struct ListNode));
	InitList(w);
	for (i=0; i<n; i++) {
		scanf("%d", &w->data[i]);
		w->last++;
	}
	tree = CreateHuffmanTree(w);
	printf("%d\n", WPL(tree, 0));
	
	return 0;
}

