#include <stdio.h>
#include <stdlib.h>

typedef struct ArrNode *ArrPtr;
struct ArrNode {
	int *data; /*存储数据的数组*/
	int size;  /*数组的大小*/
};

/* 算法1-3：将数组中元素反转存放 ReverseArray1(array) */
void ReverseArray1(ArrPtr array)
{
	for (int i = 0; i < array->size / 2;i++)
	{
		int tmp = array->data[i];
		int idx = array->size - i - 1;
		array->data[i] = array->data[idx];
		array->data[idx] = tmp;
	}
}

/* 算法1-3 结束 */

int main(void)
{
	int i, n;
	ArrPtr array;
	
	array = (ArrPtr)malloc(sizeof(struct ArrNode));
	scanf("%d", &n);
	array->size = n;
	array->data = (int *)malloc(sizeof(int)*array->size); 
	for (i=0; i<n; i++) {
		scanf("%d", &array->data[i]);
	}
	ReverseArray1(array);
	for (i=0; i<n; i++) {
		printf("%d ", array->data[i]);
	}
	return 0;
}
