#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMaxSize 1000
#define ErrorCode -1 
 
typedef struct BigIntNode *BigInt;
struct BigIntNode {
	int digits[kMaxSize]; /* 各位数字从低位到高位顺次存储 */
	int length; /* 位数 */
	int sign;   /* 正负 */
};
 
int max( int x, int y )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


BigInt ReadBigInt();
BigInt BigIntAdd( BigInt a, BigInt b );

int main(void)
{
	BigInt a, b, c;
	int i;
	
	a = ReadBigInt();
	b = ReadBigInt();
	c = BigIntAdd( a, b );
	for (i=c->length-1; i>=0; i--) {
		printf("%d", c->digits[i]);
	}
	 
	return 0;
}

/* 算法2-10：大整数相加运算  BigIntAdd( a, b ) */ 
BigInt BigIntAdd( BigInt a, BigInt b )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法2-10 结束 */ 


BigInt ReadBigInt()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

