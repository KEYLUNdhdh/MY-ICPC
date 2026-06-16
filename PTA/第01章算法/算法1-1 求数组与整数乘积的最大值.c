#include <stdio.h>
#include <stdlib.h>

typedef struct ArrNode *ArrPtr;
struct ArrNode {
	int *data; /*存储数据的数组*/
	int size;  /*数组的大小*/
};

/* 算法1-1：求数组与整数乘积的最大值 MaxProduct1(array, m) */ 
int MaxProduct1(ArrPtr array, int m)
{
	int maxx = 0;
	for (int i = 0; i < array->size;i++)
	{
		array->data[i] *= m;
		if(array->data[i] > maxx)
			maxx = array->data[i];
	}
	return maxx;
}

/* 算法1-1 结束 */ 

int main(void)
{
	int i, n, m;
	ArrPtr array;
	
	array = (ArrPtr)malloc(sizeof(struct ArrNode));
	scanf("%d %d", &n, &m);
	array->size = n;
	array->data = (int *)malloc(sizeof(int)*array->size); 
	for (i=0; i<n; i++) {
		scanf("%d", &array->data[i]);
	}
	printf("%d\n", MaxProduct1(array, m));
	return 0;
}
