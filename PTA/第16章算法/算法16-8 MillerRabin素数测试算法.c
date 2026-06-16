#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { false, true } bool;

double Random (double a, double b)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


int PowMod(int a, int i, int n)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}


/* 算法16-8：Miller-Rabin素数测试算法 MillerRabin_IsPrime(n, k) */
bool MillerRabin_IsPrime(int n, int k)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法16-8 结束 */ 

int main(void)
{
	int n, k;
	
	scanf("%d %d", &n, &k);
	printf("%d", MillerRabin_IsPrime(n, k));
		
	return 0;
}

