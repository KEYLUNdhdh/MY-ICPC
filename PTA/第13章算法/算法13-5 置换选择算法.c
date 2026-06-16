#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;
typedef int ElemSet;  /* 默认元素键值为整型 */
#define kMaxSize 3    /* RAM中数据数组的最大规模 */
typedef struct RecordNode *Records;
struct RecordNode {
	ElemSet key; /* 关键字 */
	/* 其他属性由用户自定义 */
};

void CopyRecord( Records source, Records destination )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 二叉堆定义及操作 */
typedef Records HElemSet;
typedef int Position; /* 数组下标即为元素位置 */
typedef struct BinaryHeapNode *MinHeap;
struct BinaryHeapNode {
	HElemSet *data;  /* 数据元素数组 */
	int size;        /* 规模 */
	int capacity;    /* 容量 */
};

void SiftDown(MinHeap h, Position i)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void MakeHeapDown(MinHeap h)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 二叉堆定义及操作结束 */

/* 缓冲区定义及操作 */
#define kMaxBuff 4    /* 缓冲区最大容量 */
#define EndCode (-1e9)  /* 表示空数据的键值，若按增序则定义为极小值 */
typedef int Position; /* 数组下标为数据位置 */
typedef struct BufferNode *Buffers;
struct BufferNode {
	Records b[kMaxBuff]; /* 缓冲区数据数组 */
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


bool FillBuffer(Buffers buff, FILE *f)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


Buffers InitInputBuffer(FILE *file_in)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


Buffers InitOutputBuffer()
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


void SendToOutputBuffer(Records rec, Buffers buff, FILE *f)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


Records Read(Buffers buff, FILE *f)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void EndUpOutputBuffer(MinHeap h, Buffers buff, FILE *f)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 缓冲区定义及操作结束 */

void ReadToRam(FILE *file_in, int m, Records ram_array[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


/* 算法 13-5：置换选择算法 ReplacementSelection(ram_array, m, file_in, file_out) */
void ReplacementSelection(Records ram_array[], int m, FILE *file_in, FILE *file_out)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法13-5 结束 */ 

int main(void)
{
	FILE *file_in, *file_out;
	Records ram_array[kMaxSize];

	file_in = fopen("in.txt", "r");
	file_out = fopen("out.txt", "w");
	ReplacementSelection(ram_array, kMaxSize, file_in, file_out);
	fclose(file_in);
	fclose(file_out);
		
	return 0;
}

