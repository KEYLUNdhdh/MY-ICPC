#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define kMaxStrLen 10        /* 最大字符串长度 */
#define kMinStrLen 3         /* 最小字符串长度 */
#define kCharBit 5           /* 每个字符占的位数 */
#define kMaxTableSize 500009 /* 散列表最大规模 */

typedef enum { false, true } bool;

/* 文件的词汇索引表 */
typedef struct WordNode *WordList;
struct WordNode {
	int word_pos;  /* 单词在散列表中的位置 */
	WordList next; /* 文件中的下一个单词 */
};

WordList InitFileWordList( int n_file )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 倒排索引表 */
typedef struct FileNode *PostingList;
struct FileNode {
	int file_no;
	PostingList next;
};

/* 散列表相关定义与操作 */
typedef long long HashVal;  /* 默认散列值为int型 */
typedef HashVal Position; /* 数组下标是元素的位置 */
typedef char ElemSet[kMaxStrLen+1];  /* 默认数据类型是字符串 */

typedef struct RecordNode *Records;
struct RecordNode {
	ElemSet key;    /* 关键字，即单词 */
	int last_file;  /* 最后插入的单词所属的文件编号 */ 
	PostingList pl; /* 倒排索引表 */
};

typedef struct HashNode *HashTable;
struct HashNode {
	Records *ht;    /* 散列表数据 */
	int size;       /* 散列表当前数据元素个数 */
	int table_size; /* 散列表表长 */
};

HashTable InitHashTable( int table_size )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


HashVal Hash(ElemSet key, int table_size)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

Position SearchHash(HashTable htable, ElemSet key)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


#define NIL -1 /* 插入不成功的标识 */
Position InsertHash(HashTable htable, ElemSet key, int file_no)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 散列表相关定义与操作 结束 */

bool GetWord( ElemSet word )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void InsertWordToFile( WordList file, int file_no, int word_pos )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


#define Swap(x, y) { int t = x; x = y; y = t; }
double Similarity( WordList file, int f1, int f2, HashTable htable )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int main()
{
	ElemSet word;
	HashTable htable;
	WordList file;
	int n, m, f1, f2, i;

	scanf("%d\n", &n);
	file = InitFileWordList(n); /* 初始化文件的词汇表 */
	htable = InitHashTable(kMaxTableSize); /* 创建一个散列表 */
	for (i=0; i<n; i++) { /* 读入并索引每个文件 */
		while (GetWord(word) == true) { /* 从第(i+1)号文件中分词 */
			/* 将单词插入散列表，更新倒排索引表，更新词汇表 */
			InsertWordToFile(file, i+1, InsertHash(htable, word, i+1));
		}
	}
	scanf("%d", &m);
	for (i=0; i<m; i++) { /* 处理每条查询 */
		scanf("%d %d", &f1, &f2);
		printf("%.1f%%\n", Similarity(file, f1, f2, htable));
	}

	return 0;
}

