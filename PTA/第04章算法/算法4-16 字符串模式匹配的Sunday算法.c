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


Position MapChar( char c )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法4-16：字符串模式匹配的Sunday算法  PatternMatchSunday(s,t) */ 
Position PatternMatchSunday(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法4-16 结束 */ 

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
	p = PatternMatchSunday(s,t);
	if (p != NIL) 
		printf("%s\n", s->data+p);
	else
		printf("匹配失败。\n");
	
	return 0;
}

