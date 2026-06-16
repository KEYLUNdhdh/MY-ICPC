#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum { false, true } bool;
typedef struct DistNode *Dist;
struct DistNode {
	int *dist;     /* 距离值数组 */
	bool *deleted; /* 删除标识的数组 */
	int capacity;  /* 距离总数量 */
	int size;      /* 当前剩余元素数量 */
};

int FindMax(Dist D)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


bool Check( int x_value, int *x, int n, Dist D )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void Delete(int v, Dist D)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void Insert(int v, Dist D)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int CmpDist(const void *a, const void *b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法15-6：点集重构问题回溯算法的伪代码 PointSetReconstruction(x, D, n, left, right) */
bool PointSetReconstruction(int *x, Dist D, int n, int left, int right)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}
 
/* 算法15-6 结束 */ 

int main(void)
{
	int m, n, i;
	Dist D; /* 距离集合 */
	int *x;  /* 坐标集合 */
	
	/* 读入m个距离值，创建距离集合 */
	scanf("%d", &m);
	D = (Dist)malloc(sizeof(struct DistNode));
	D->capacity = m;
	D->size = m;
	D->dist = (int *)malloc(sizeof(int) * m);
	D->deleted = (bool *)malloc(sizeof(bool) * m);
	for (i=0; i<m; i++) {
		scanf("%d", &D->dist[i]);
		D->deleted[i] = false;
	}
	qsort(D->dist, m, sizeof(int), CmpDist); /* 将距离值从大到小排序 */
	n = ((int)sqrt((m<<3)+1)+1)>>1; /* 由距离数量反推坐标点的数量 */
	x = (int *)malloc(sizeof(int) * n);
	for (i=0; i<n; i++) {
		x[i] = -1; /* 初始化坐标值为任何不可能是正确坐标的值 */
	}
	x[0] = 0;
	x[n-1] = D->dist[0];  /* 最后一个点的坐标确定为最大距离值 */
	D->deleted[0] = true; /* 删除最大距离 */
	D->size--;
	if (PointSetReconstruction(x, D, n, 1, n-2)==true) { /* 求解并输出结果 */
		printf("%d", x[0]);
		for (i=1; i<n; i++) {
			printf(" %d", x[i]);
		}
		printf("\n");
	}
	
	return 0;
}

