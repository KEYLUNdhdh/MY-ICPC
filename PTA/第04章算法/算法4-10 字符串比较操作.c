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


/* 算法4-10：字符串比较操作  StrCompare(s,t) */ 
int StrCompare(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return 0;
}

/* 算法4-10 结束 */ 

String ReadString()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	String s, t;
	
	s = ReadString();
	t = ReadString();
	printf("%d\n", StrCompare(s,t));
	
	return 0;
}

