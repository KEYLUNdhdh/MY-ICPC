#include <stdio.h>
#include <stdlib.h>

typedef int ElemSet; /* 默认元素为整数*/

int IsInsertion( ElemSet *a, ElemSet *b, int n );
void NextInsertion( ElemSet *b, int n, int p );
int MergeLength( ElemSet *b, int n );
void TwoWayMerge(ElemSet *a, ElemSet *t, int l, int m, int r);
void NextMerge( ElemSet *b, ElemSet *a, int n );
void PrintResults( ElemSet *a, int n );

int main(void)
{
	ElemSet *a, *b;
	int n, i, p;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n); /* a存原始序列 */
	b = (ElemSet *)malloc(sizeof(ElemSet) * n); /* b存中间序列 */
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	for (i=0; i<n; i++) {
		scanf("%d", &b[i]);
	}
	p = IsInsertion(a, b, n);
	if ( p > 0 ) { /* 如果是插入排序 */
		NextInsertion(b, n, p); /* 执行下一步插入 */
		PrintResults(b, n); /* 输出结果 */
	}
	else { /* 否则执行下一步归并 */
		NextMerge(b, a, n); /* 将b中元素归并到a */
		PrintResults(a, n); /* 输出结果 */
	}

	return 0;
}

int IsInsertion( ElemSet *a, ElemSet *b, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void NextInsertion( ElemSet *b, int n, int p )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int MergeLength( ElemSet *b, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void TwoWayMerge(ElemSet *a, ElemSet *t, int l, int m, int r)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int Min( int x, int y)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


void NextMerge( ElemSet *b, ElemSet *a, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 

void PrintResults( ElemSet *a, int n )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


