#include <stdio.h>
#include <stdlib.h>


typedef int ElemSet; /* 默认元素为整数*/
#define kMinSize 5 /* 最小规模必须大于alpha */
#define alpha 4
#define infinity (1e9)
typedef struct SubProblemNode *SubProblems;
struct SubProblemNode {
	int l; /* 子问题的左端点 */
	int n; /* 子问题的规模   */
};

ElemSet Min( ElemSet x, ElemSet y )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


ElemSet Max( ElemSet x, ElemSet y )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void Conquer (ElemSet *a, int l, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


SubProblems Divide(int l, int n, int m)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


ElemSet *Merge(ElemSet *a, SubProblems part, int n)
{
	ElemSet *t;
	int p[alpha], pt, min_elem, min_idx, i;
	
	t = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<alpha; i++) {
		p[i] = part[i].l; /* 每个子问题的当前元素位置 */
	}
	for (pt=0; pt<n; pt++) {
		min_elem = infinity;
		for (i=0; i<alpha; i++) { /* 找所有子问题当前元素的最小值 */
			if (p[i]<(part[i].l+part[i].n) && a[p[i]]<min_elem) {
				min_elem = a[p[i]];
				min_idx = i;
			}
		}
		t[pt] = a[p[min_idx]]; /* 放入t中 */
		p[min_idx]++;
	}
	return t;
}

/* 算法15-7 分治法的伪代码描述 DivideAndConquer(n) */
void DivideAndConquer(ElemSet *a, int l, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}
 
/* 算法15-7 结束 */ 

int main(void)
{
	ElemSet *a;
	int n, i;
	
	scanf("%d", &n);
	a = (ElemSet *)malloc(sizeof(ElemSet) * n);
	for (i=0; i<n; i++) {
		scanf("%d", &a[i]);
	}
	DivideAndConquer(a, 0, n);
	for (i=0; i<n; i++) {
		printf("%d ", a[i]);
	} 

	return 0;
}

