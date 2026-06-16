#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef int ElemSet;  /* 默认元素为整型 */
#define kMaxSize 100  /* 多路归并的最大顺串数量 */
#define EndCode 1e9   /* 当键值小为胜者时，用超大数表示文件结束 */
typedef struct LoserTreeNode *LoserTree;
struct LoserTreeNode {
	int n;      /* 当前选手数 */
	int n_L;    /* 最底层外部结点数 */
	int n_B;    /* 最底层外部结点之上的结点总数 */
	int *B;     /* 存放下标的胜者树数组 */
	ElemSet *L; /* 元素数组 */
};

int Winner(LoserTree tree, int x, int y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int Loser(LoserTree tree, int x, int y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int FinalWinner(LoserTree tree)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法13-2：从内部结点到树根的路径上进行比赛 Play(tree, p, left, right) */
void Play(LoserTree tree, int p, int left, int right)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法13-2 结束 */ 

/* 算法13-1：初始化败者树 InitLoserTree(tree, array, size) */
void InitLoserTree(LoserTree tree, ElemSet array[], int size)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法13-1 结束 */ 

/* 算法13-3：重构时从外部结点到树根的路径上重新进行比赛 RePlay(tree, i) */
void RePlay(LoserTree tree, int i)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法13-3 结束 */ 

/* 缓冲区定义及操作 */
#define kMaxBuff 10   /* 缓冲区最大容量 */
typedef int Position; /* 数组下标为数据位置 */
typedef struct BufferNode *Buffers;
struct BufferNode {
	ElemSet b[kMaxBuff]; /* 缓冲区数据数组 */
	Position front;      /* 前端位置 */
	Position rear;       /* 后端位置 */
	int capacity;        /* 总容量 */
};

Buffers InitBuffer()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Flush(Buffers buff, FILE *f)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


bool FillBuffer(Buffers buff, FILE *f)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsEmpty(Buffers buff)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool IsFull(Buffers buff)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Write(Buffers buff, ElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


ElemSet Read(Buffers buff)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 缓冲区定义及操作结束 */

/* 算法 13-4：利用败者树的多路归并排序算法 MultiMerge(tree, racer, buffer_pool, f, size) */ 
void MultiMerge(LoserTree tree, ElemSet racer[], Buffers buffer_pool[], FILE *f[], int size)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法13-4 结束 */ 

#define kMaxStrLen 10

int main(void)
{
	FILE *f[kMaxSize+1]; /* f[0]为输出文件，f[1]~f[kMaxSize]为输入文件 */
	char fname[kMaxSize+1][kMaxStrLen]; /* 文件名，不超过(kMaxStrLen-1)个字符 */
	Buffers buffer_pool[kMaxSize+1]; /* 对应的输出、输入缓冲区 */
	ElemSet racer[kMaxSize+1]; /* 比赛者数组，即败者树外部结点数组 */
	LoserTree tree; /* 败者树 */
	int n, i, j;
	
	scanf("%d\n", &n);
	scanf("%s\n", fname[0]); /* 读输出文件名 */
	f[0] = fopen(fname[0], "w"); /* 打开输出文件，待写 */
	for (i=1; i<=n; i++) {
		scanf("%s\n", fname[i]);     /* 读输入文件名 */
		f[i] = fopen(fname[i], "r"); /* 打开输入文件，待读 */
	}
	tree = (LoserTree)malloc(sizeof(struct LoserTreeNode)); /* 创建败者树结点 */
	buffer_pool[0] = InitBuffer(); /* 初始化空的输出缓冲区 */
	for (i=1; i<=n; i++) {
		fscanf(f[i], "%d", &racer[i]); /* 每个顺串的第一个数据进入败者树准备比赛 */
		buffer_pool[i] = InitBuffer();
		FillBuffer(buffer_pool[i], f[i]); /* 从每个文件中读入一块数据到输入缓冲区 */
	}
	MultiMerge(tree, racer, buffer_pool, f, n); /* 归并排序，结果在输出文件里 */
	for (i=0; i<n; i++) {
		fclose(f[i]);
	}
	
	return 0;
}

