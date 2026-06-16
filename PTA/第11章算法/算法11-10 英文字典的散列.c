#include <stdio.h>
#include <stdlib.h>

typedef int HashVal;  /* 默认散列值为int型*/
#define kMaxLen 10
 
/* 算法11-10：英文字典的散列 StringHash(string, table_size) */
HashVal StringHash(char string[], int table_size)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 
/* 算法11-10 结束 */ 

int main(void)
{
	char string[kMaxLen+1];
	int table_size;
	
	scanf("%s %d", string, &table_size);
	printf("%d", StringHash(string, table_size));
	
	return 0;
}

