#include <stdio.h>
#include <stdlib.h>

typedef struct SeqNode *SeqPtr;
struct SeqNode {
	int *array;        /* 存储数据的数组 */
	int n;             /* 数组的大小 */
	int max_sum;       /* 最大和 */
	int start, finish; /* 最大连续子序列左右两端点的数组下标 */
};

/* 算法1-9：连续子序列最大和的O(n)算法 MaxSubsequenceSum3(s) */
int MaxSubsequenceSum3(SeqPtr s)
{
	int sum = 0;
	s->start = 0;
	s->finish = 0;
	s->max_sum = -1e9;
	int curs = 0;
	for (int i = 0; i < s->n;i++)
	{
		if(sum + s->array[i] > sum)
		{
			sum += s->array[i];
			if(sum > s->max_sum)
			{
				s->max_sum = sum;
				s->finish = i;
				s->start = curs;
			}
		}
		else if(sum + s->array[i] < 0)
		{
			sum = 0;
			curs = i + 1;
		}
		else
			sum += s->array[i];
	}
	if(s->max_sum <= 0)
	{
		s->max_sum = 0;
		s->start = -1;
		s->finish = -1;
	}
	return s->max_sum;
}

/* 算法1-9 结束 */

int main(void)
{
	int i;
	SeqPtr s;

	s = (SeqPtr)malloc(sizeof(struct SeqNode));
	scanf("%d", &s->n);
	s->array = (int *)malloc(sizeof(int)*s->n);
	for (i=0; i<s->n; i++) {
		scanf("%d", &s->array[i]);
	}
	printf("%d\n", MaxSubsequenceSum3(s));
	printf("%d %d\n", s->start, s->finish);
	return 0;
}

