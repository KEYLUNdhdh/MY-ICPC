#include <stdio.h>
#include <stdlib.h>

typedef double CoefSet;  /* 定义多项式系数为double型 */
#define eps (1e-9)
 
typedef struct PolyNode *Position; /* 指针即结点位置 */
struct PolyNode {
    CoefSet coef;  /* 系数 */
    int expon;     /* 指数 */ 
    Position next; /* 线性表中下一个元素的位置 */
};
typedef Position Polynomial;

Position Attach(CoefSet coef, int expon, Position rear);
Polynomial ReadPoly();
Polynomial PolynomialAdd( Polynomial p1, Polynomial p2 );

int main(void)
{
	Polynomial p1, p2, p;
	Position tmp;
	
	p1 = ReadPoly();
	p2 = ReadPoly();
	p = PolynomialAdd(p1, p2);
	tmp = p;
	while (tmp != NULL) {
		printf("%.2f %d\n", tmp->coef, tmp->expon);
		tmp = tmp->next;
	}
	return 0;
}

/* 算法2-9：一元多项式加法运算  PolynomialAdd(p1, p2) */ 
Polynomial PolynomialAdd( Polynomial p1, Polynomial p2 )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法2-9 结束 */ 

Position Attach(CoefSet coef, int expon, Position rear)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


Polynomial ReadPoly()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}
 

