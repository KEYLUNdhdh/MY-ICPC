#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 1001
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


void StrInsert(String s, int pos, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void StrRemove(String s, int pos, int len)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


Position PatternMatchBF(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法 4-12：字符串替换算法  Replace(s, sub_s, t) */
void Replace(String s, String sub_s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法 4-12 结束 */ 

String ReadString()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	String s, sub_s, t;
	Position p;
	
	s = ReadString();
	sub_s = ReadString();
	t = ReadString();
	Replace(s, sub_s, t);
	printf("%s\n", s->data);
	
	return 0;
}

