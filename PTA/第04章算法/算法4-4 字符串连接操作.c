#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 1001
typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct StringNode *String;
struct StringNode {
    char data[kMaxSize];  /* 存储字符的数组 */
    int length;             /* 字符串长度 */
};

String InitStr()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


/* 算法4-4：字符串连接操作  StrConcat(s,t) */ 
void StrConcat(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}

/* 算法4-4 结束 */ 

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
	StrConcat(s,t);
	printf("%s\n", s->data);
	
	return 0;
}

