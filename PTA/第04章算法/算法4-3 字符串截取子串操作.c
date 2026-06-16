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


/* 算法4-3：字符串截取子串操作  SubString(s, pos, len) */ 
String SubString(String s, int pos, int len)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

/* 算法4-3 结束 */ 

String ReadString()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


int main(void)
{
	Position pos;
	int len;
	String s, sub_s;
	
	s = ReadString();
	scanf("%d %d", &pos, &len);
	sub_s = SubString(s, pos, len);
	printf("%s\n", sub_s->data);
	
	return 0;
}

