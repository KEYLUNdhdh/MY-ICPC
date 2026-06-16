#include <stdio.h>
#include <stdlib.h>

#define kMaxSize 3000001
#define NIL -1

typedef int Position;
typedef struct StringNode *String;
struct StringNode {
    char data[kMaxSize];  /* 存储字符的数组 */
    int length;           /* 字符串长度 */
};


// 如果有 string.h头文件，直接用 strstr()写即可。
/* 算法4-11：朴素字符串匹配算法  PatternMatchBF(s, t) */ 
/* 构建next数组：KMP的核心预处理步骤 */
// void buildNext(String t, int *next) {
//     int i = 0, j = -1;
//     next[0] = -1;
//     while (i < t->length - 1) {
//         if (j == NIL || t->data[i] == t->data[j]) {
//             i++;
//             j++;
//             next[i] = j;
//         } else {
//             j = next[j];
//         }
//     }
// }

// /* KMP匹配算法 */
// Position PatternMatchBF(String s, String t) {
//     int *next = (int *)malloc(sizeof(int) * t->length);
//     buildNext(t, next);
    
//     int i = 0, j = 0;
//     int sLen = s->length;
//     int tLen = t->length;
    
//     while (i < sLen && j < tLen) {
//         if (j == NIL || s->data[i] == t->data[j]) {
//             i++;
//             j++;
//         } else {
//             j = next[j]; // 不匹配时，根据next数组回退
//         }
//     }
    
//     free(next);
//     if (j == tLen) {
//         return i - tLen; // 返回匹配起始位置
//     } else {
//         return NIL; // 匹配失败
//     }
// }


void buildNext(String t, int *next)
{
    int i = 0, j = -1;
    next[0] = -1;
    while(i < t->length - 1)
    {
        if(j == -1 || t->data[i] == t->data[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

Position PatternMatchBF(String s, String t)
{
    int *next = (int *)malloc(sizeof(int) * t->length);
    buildNext(t, next);

    int i = 0, j = 0;
    int slen = s->length;
    int tlen = t->length;
    int firstpos = -1;
    int cnt = 0;
    while(i < slen && j < tlen)
    {
        if(j == -1 || s->data[i] == t->data[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
           
        if(j == tlen)
        {
            cnt++;
            if(firstpos == -1)
            {
                firstpos = i - tlen;
            }
            j = next[j - 1];//同时增加计数功能
        }
    }

    return firstpos;
}
/* 算法4-11 结束 */ 

String ReadString()
{
    String tmp = (String)malloc(sizeof(struct StringNode));
    tmp->length = 0;
    fgets(tmp->data, 1000005, stdin);
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
	String s, t;
	Position p;
	
	s = ReadString();
	t = ReadString();
	p = PatternMatchBF(s,t);
	if (p != NIL) 
		printf("%s\n", s->data+p);
	else
		printf("匹配失败。\n");
	
	return 0;
}

