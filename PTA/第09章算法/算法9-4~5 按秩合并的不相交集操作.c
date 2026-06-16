#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 1000             /* 集合最大元素个数 */
typedef int SElemSet;             /* 默认元素用非负整数表示 */
typedef SElemSet SetName;         /* 默认用根结点的下标作为集合名称 */
typedef struct SetNode {
	SElemSet parent;  /* 父结点 */
	int rank;         /* 秩 */ 
} Set[kMaxSize+1];    /* 假设集合元素下标从1开始 */

/* 算法9-4：初始化采用按秩合并策略的不相交集 InitSet(set, n) */
void InitSet(Set set, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法9-4 结束 */ 

SetName Find(Set set, SElemSet x)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法9-5：利用按秩合并策略合并两个元素所在的集合 Union(set, x, y) */
void Union(Set set, SElemSet x, SElemSet y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法9-5 结束 */ 

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
	for (i=1; i<=n; i++) {
		printf("set[%d].parent = %d, rank = %d\n", i, set[i].parent, set[i].rank);
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
	return 0;
}

