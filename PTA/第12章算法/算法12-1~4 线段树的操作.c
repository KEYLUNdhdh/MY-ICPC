#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef int ElemSet;  /* 默认元素为整型 */
typedef int Position; /* 数组下标是元素位置 */
typedef ElemSet *SegTree;
#define kMaxNum 1e9

ElemSet Min(ElemSet x, ElemSet y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法12-1：求最小值线段树的初始化 BuildSegTree(seg_tree, array, l, r, p) */
void BuildSegTree(SegTree seg_tree, ElemSet array[], int l, int r, Position p)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法12-1 结束 */ 

/* 算法12-2：求最小值线段树的点更新 Update(seg_tree, l, r, p, idx, value) */
void Update(SegTree seg_tree, int l, int r, Position p, Position idx, ElemSet value)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法12-2 结束 */ 

/* 算法12-3：求最小值线段树的区间查询 Query(seg_tree, l, r, p, ql, qr) */
ElemSet Query(SegTree seg_tree, int l, int r, Position p, int ql, int qr)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法12-3 结束 */ 

/* 算法12-4：求最小值线段树的区间增值更新 RangeUpdate(seg_tree, lazy, l, r, p, ql, qr, c) */
void RangeUpdate(SegTree seg_tree, SegTree lazy, int l, int r, Position p, int ql, int qr, ElemSet c)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法12-4 结束 */ 
#define kMaxSize 1000

int main(void)
{
	ElemSet array[kMaxSize], value, c;
	SegTree seg_tree, lazy;
	Position idx;
	int n, i, ql, qr;
	
	scanf("%d", &n);
	for (i=1; i<=n; i++) {
		scanf("%d", &array[i]);
	}
	seg_tree = (SegTree)malloc(sizeof(ElemSet) * (4*n+1));
	lazy = (SegTree)malloc(sizeof(ElemSet) * (4*n+1));
	BuildSegTree(seg_tree, array, 1, n, 1);
	scanf("%d %d", &ql, &qr);
	printf("min[%d, %d] = %d\n", ql, qr, Query(seg_tree, 1, n, 1, ql, qr));
	scanf("%d %d", &idx, &value);
	Update(seg_tree, 1, n, 1, idx, value);
	printf("min[%d, %d] = %d\n", ql, qr, Query(seg_tree, 1, n, 1, ql, qr));
	scanf("%d %d %d", &ql, &qr, &c);
	memset(lazy, 0, sizeof(ElemSet) * (4*n+1));
	RangeUpdate(seg_tree, lazy, 1, n, 1, ql, qr, c);
	printf("min[%d, %d] = %d\n", ql, qr, Query(seg_tree, 1, n, 1, ql, qr));

	return 0;
}

