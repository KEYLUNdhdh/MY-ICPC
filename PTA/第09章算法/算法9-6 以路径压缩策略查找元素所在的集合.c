#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 1000             /* 集合最大元素个数 */
typedef int SElemSet;             /* 默认元素用非负整数表示 */
typedef SElemSet SetName;         /* 默认用根结点的下标作为集合名称 */
typedef struct SetNode {
	SElemSet parent;  /* 父结点 */
	int rank;         /* 秩 */ 
} Set[kMaxSize+1];    /* 假设集合元素下标从1开始 */

void InitSet(Set set, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 

/* 算法9-6：以路径压缩策略查找元素所在的集合Find(set, x) */
SetName Find(Set set, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法9-6 结束 */ 

void Union(Set set, SElemSet x, SElemSet y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	int n, m, x, y, i;
	Set set;
	
	scanf("%d %d", &n, &m);
	InitSet(set, n);
	for (i=0; i<m; i++) {
		scanf("%d %d", &x, &y);
		if (Find(set,x) != Find(set, y)) {
			Union(set, x, y);
		}
	}
	scanf("%d", &m);
	for (i=0; i<m; i++) {
		scanf("%d %d", &x, &y);
		if (Find(set, x) == Find(set, y)) {
			printf("yes\n");
		}
		else {
			printf("no\n");
		}
	}
	for (i=1; i<=n; i++) {
		printf("set[%d].parent = %d, rank = %d\n", i, set[i].parent, set[i].rank);
	} 
	return 0;
}

