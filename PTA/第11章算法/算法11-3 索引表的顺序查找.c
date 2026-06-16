#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet;  /* 默认元素为整数*/
typedef int Position; /* 数组下标是元素的位置 */
typedef struct RecordNode {
	ElemSet key; /* 关键字 */
	/* 其他属性由用户自定义 */
} Records;
typedef struct IndexNode {
	ElemSet key;   /* 数据块中最大关键字值 */
	Position link; /* 数据块第1个记录在表中的位置 */
} Index;

/* 算法11-3 索引表的顺序查找 IndexSequentialSearch(record, idx, m, l, key) */
Position IndexSequentialSearch(Records record[], Index idx[], int m, int l, ElemSet key)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法11-3 结束 */ 

int main(void)
{
	Records *record;
	Index *idx;
	int n, m, l, key, i, j, k, max_rec;
	
	scanf("%d %d", &m, &l);
	idx = (Index *)malloc(sizeof(Index) * (m+1)); /* 注意：元素下标从1开始 */
	record = (Records *)malloc(sizeof(Records) * (m*l+1));
	for (k=1, i=1; i<=m; i++) { /* 注意：元素下标从1开始 */
		max_rec = -1;
		idx[i].link = k;
		for (j=0; j<l; j++) {
			scanf("%d", &record[k]);
			if (record[k].key>max_rec) {
				max_rec = record[k].key;
			} 
			k++;
		}
		idx[i].key = max_rec;
	}
	scanf("%d", &key);
	while (key != -1) {
		printf("%d ", IndexSequentialSearch(record, idx, m, l, key));
		scanf("%d", &key);
	}

	return 0;
}

