#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 1000001
#define NIL -1

typedef int Position;
typedef struct StringNode *String;
struct StringNode {
    char data[kMaxSize];  /* 存储字符的数组 */
    int length;           /* 字符串长度 */
};

String InitStr()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法4-13：求解字符串t的next数组  GetNext (t, next) */ 
void GetNext(String t, int next[])
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法4-13 结束 */ 

/* 算法4-14：字符串匹配的KMP算法  PatternMatchKMP(s, t) */ 
Position PatternMatchKMP(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法4-14 结束 */ 

String ReadString()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	String s, t;
	Position p;
	
	s = ReadString();
	t = ReadString();
	p = PatternMatchKMP(s,t);
	if (p != NIL) 
		printf("%s\n", s->data+p);
	else
		printf("匹配失败。\n");
	
	return 0;
}

