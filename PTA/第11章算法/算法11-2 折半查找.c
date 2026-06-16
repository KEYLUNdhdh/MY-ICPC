#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet;  /* 默认元素为整数*/
typedef int Position; /* 数组下标是元素的位置 */
typedef struct RecordNode {
	ElemSet key; /* 关键字 */
	/* 其他属性由用户自定义 */
} Records;

/* 算法11-2 折半查找 BinarySearch(record, low, high, key) */
Position BinarySearch(Records record[], int low, int high, ElemSet key)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法11-2 结束 */ 

int main(void)
{
	Records *record;
	int n, key, i;
	
	scanf("%d", &n);
	record = (Records *)malloc(sizeof(Records) * (n+1));
	for (i=1; i<=n; i++) { /* 注意：元素下标从1开始 */
		scanf("%d", &record[i].key);
	}
	scanf("%d", &key);
	while (key != -1) {
		printf("%d ", BinarySearch(record, 1, n, key));
		scanf("%d", &key);
	}

	return 0;
}

