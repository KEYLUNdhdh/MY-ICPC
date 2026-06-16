#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 1000000
typedef int Position; /* 整型下标，表示元素的位置 */
typedef struct StringNode *String;
struct StringNode {
    char data[kMaxSize];  /* 存储字符的数组 */
    int length;             /* 字符串长度 */
};


/* 算法4-1：字符串插入操作StrInsert(s, pos, t) */ 
void StrInsert(String s, Position pos, String t)
{
    int len = t->length;
    pos--;
    if(pos > s->length || pos < 0 )
    {
        printf("错误：指定插入位置不存在。\n");
        return;

    }
    for (int i = s->length - 1; i >= pos;i--)
    {
        s->data[i + len] = s->data[i];
    }
    s->length = s->length + t->length;
    s->data[s->length] = '\0';
    for (int i = pos; i <= pos + len - 1;i++)
        s->data[i] = t->data[i - pos];

    return;
}

/* 算法4-1 结束 */ 

String ReadString()
{
    String tmp = (String)malloc(sizeof(struct StringNode));
    tmp->length = 0;
    fgets(tmp->data, 1000000, stdin);
    for (int i = 0;;i++)
    {
        if(tmp->data[i] == '\n')
        {
            tmp->data[i] = '\0';
            tmp->length = i;
            break;
        }
    }
    return tmp;
}


int main(void)
{
	Position pos;
	String s, t;
	
	s = ReadString();
	t = ReadString();
    scanf("%d", &pos);
	StrInsert(s, pos, t);
	printf("%s\n", s->data);
	
	return 0;
}

