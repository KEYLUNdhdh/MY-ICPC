#include <stdio.h>
#include <stdlib.h>

#define NIL NULL
typedef int HashVal;  /* 默认散列值为int型 */
typedef HashVal Position; /* 数组下标是元素的位置 */
typedef int ElemSet;  /* 默认数据类型是整数 */
typedef enum {Empty, Active, Inactive} Status; /* 三种状态 */

typedef struct RecordNode *Records;
struct RecordNode {
	ElemSet key; /* 关键字 */
	/* 其他属性由用户自定义 */
};

typedef struct DataNode {
	Records data;  /* 数据 */
	Status status; /* 该数据的状态 */ 
}DataSet;

typedef struct HashNode *HashTable;
struct HashNode {
	DataSet *ht;    /* 散列表数据 */
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
 

Position SolveCollision(ElemSet key, int count)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法11-11：开放定址法散列查找 SearchHash(htable, key) */
Position SearchHash(HashTable htable, ElemSet key)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法11-11 结束 */ 

/* 算法11-12：开放定址法散列插入 InsertHash(htable, x) */
void InsertHash(HashTable htable, Records x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法11-12 结束 */ 

int main(void)
{
	HashTable htable;
	int table_size, n, i;
	Records x;
	
	scanf("%d", &table_size);
	htable = InitHashTable(table_size);
	scanf("%d", &n);
	for (i=0; i<n; i++) {
		x = (Records)malloc(sizeof(struct RecordNode));
		scanf("%d", &x->key);
		InsertHash(htable, x);
	}
	for (i=0; i<htable->table_size; i++) {
		if (htable->ht[i].status==Active) {
			printf("ht[%d] = %d\n", i, htable->ht[i].data->key);
		}
	}
	return 0;
}

