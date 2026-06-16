#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMaxSize 1000001
#define NIL -1
typedef int Position;
typedef struct StringNode *String;
struct StringNode {
    char data[kMaxSize];  /* 存储字符的数组 */
    int length;           /* 字符串长度 */
};

String InitStr();
String ReadString();
Position PatternMatch(String s, String t);

int main(void)
{
	int n, i;
	String string, pattern;
	Position p;
	
	string = ReadString();
	scanf("%d\n", &n);
	for (i=0; i<n; i++) {
		pattern = ReadString();
		p = PatternMatch(string, pattern);
		if (p != NIL) 
			printf("%s\n", string->data+p);
		else
			printf("Not Found\n");
	}
	return 0;
}

String InitStr()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


String ReadString()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


Position PatternMatch(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

