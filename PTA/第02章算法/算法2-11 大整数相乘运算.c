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

BigInt ReadBigInt();
BigInt BigIntMultiply( BigInt a, BigInt b );

int main(void)
{
	BigInt a, b, c;
	int i;
	
	a = ReadBigInt();
	b = ReadBigInt();
	c = BigIntMultiply( a, b );
	if (c->length == 0) {
		printf("0");
	}
	else if (c->sign == -1) {
		printf("-");
	}
	for (i=c->length-1; i>=0; i--) {
		printf("%d", c->digits[i]);
	}
	 
	return 0;
}

/* 算法2-11：大整数相乘运算  BigIntMultiply(a, b) */ 
BigInt BigIntMultiply( BigInt a, BigInt b )
{
	BigInt c = (BigInt)malloc(sizeof(struct BigIntNode));
	memset(c->digits, 0, sizeof(c->digits));

	// for (int i = 0; i < a->length;i++)
	// 	printf("%d", a->digits[i]);
	// printf("\n");
	if(a->sign == -1 && b->sign == -1)
		c->sign = 1;
	else if(a->sign == 1 && b->sign == 1)
		c->sign = 1;
	else
		c->sign = -1;
	for (int i = 0; i < a->length;i++)
	{
		for (int j = 0; j < b->length;j++)
		{
			if(i + j >= 1000)
			{
				printf("错误：位数超限。");
				exit(0);
			}
			c->digits[i + j] += a->digits[i] * b->digits[j];
		}
	}
	for (int i = 0; i < a->length + b->length;i++)
	{
		c->digits[i + 1] += c->digits[i] / 10;
		c->digits[i] %= 10;
	}
	int maxlen = a->length + b->length;
	while (maxlen > 1 && c->digits[maxlen - 1] == 0) 
        maxlen--;

	c->length = maxlen;
	return c;
}	

/* 算法2-11 结束 */ 

BigInt ReadBigInt()
{
	BigInt a = (BigInt)malloc(sizeof(struct BigIntNode));
	memset(a->digits, 0, sizeof(a->digits));
	char str[1005];
	scanf("%s", str);
	if(str[0] == '-')
	{
		a->sign = -1;
		int t = strlen(str);
		for (int i = 0; i < t;i++)
			str[i] = str[i + 1];
		str[t - 1] = '\0';
	}
	else
		a->sign = 1;
	int n = strlen(str);
	a->length = n;
	for (int i = 0; i < n;i++)
		a->digits[i] = str[n - i - 1] - '0';

	// printf("%d", a->sign);
	// for (int i = 0; i < a->length;i++)
	// 	printf("%d", a->digits[i]);
	// printf("\n");
	return a;
}
 

