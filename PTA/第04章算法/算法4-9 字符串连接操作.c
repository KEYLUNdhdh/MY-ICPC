#include <stdio.h>
#include <stdlib.h>

#define NormalCode 0
#define ErrorCode 1

typedef struct StringNode *Position; /* 指针即结点位置 */
struct StringNode {
    char data;       /* 存储数据 */
    Position next;   /* 链接存储中下一个元素的位置 */
};
typedef struct StringHeadNode *String;
struct StringHeadNode {
    Position head;   /* 字符串头指针，初始化为NULL */
    int length;      /* 字符串长度 */
};

String InitStr()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法4-9：字符串连接操作  StrConcat(s,t) */ 
void StrConcat(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法4-9 结束 */ 

String ReadString()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void PrintString( String s )
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


int main(void)
{
	String s, t;
	
	s = ReadString();
	t = ReadString();
	StrConcat(s,t);
	PrintString(s);
	
	return 0;
}

