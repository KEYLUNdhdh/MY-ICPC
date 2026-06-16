#include <stdio.h>
#include <stdlib.h>

typedef int CoefSet;  /* 定义多项式系数为int型 */ 
 
typedef struct PolyNode *Position; /* 指针即结点位置 */
struct PolyNode {
    CoefSet coef;  /* 系数 */
    int expon;     /* 指数 */ 
    Position next; /* 线性表中下一个元素的位置 */
};
typedef Position Polynomial;

Position Attach(CoefSet coef, int expon, Position rear);
Polynomial ReadPoly();
void PrintPoly(Polynomial p);
 
Polynomial PolyDifferentiation( Polynomial p )
{
    int cnt = 1;
    while(p)
    {
        int xi = p->coef;
        int zhi = p->expon;
        if(zhi == 0)
        {
            p = p->next;
            continue;
        }
        if(cnt != 1)
            printf(" ");
        int newxi = xi * zhi;
        int newzhi = zhi - 1;
        printf("%d %d", newxi, newzhi);
        p = p->next;
        cnt++;
    }
    if(cnt == 1)
        printf("0 0");
    return NULL;
}


int main(void)
{
	Polynomial p;
	
	p = ReadPoly();
	PolyDifferentiation(p);
	
	return 0;
}


Polynomial ReadPoly()
{
    int xi, zhi;
    Polynomial head = NULL, tail = NULL;
    while(scanf("%d %d", &xi, &zhi) != EOF)
    {
        // 删掉你原本循环里的逻辑，改成：
        Polynomial temp = (Polynomial)malloc(sizeof(struct PolyNode));
        temp->coef = xi;
        temp->expon = zhi;
        temp->next = NULL; // 关键：防野指针

        if (head == NULL) {
            head = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }
    return head;
}
 


