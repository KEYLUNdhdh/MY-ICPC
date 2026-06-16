#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMaxSize 201
typedef int Position; /* 整型下标，表示元素的位置 */
#define NIL -1
typedef struct StringNode *String;
struct StringNode {
    char data[kMaxSize];  /* 存储字符的数组 */
    int length;           /* 字符串长度 */
};

String InitStr(); /* 代码4-1给出*/
void ReadString(String s); /* 代码4-17略改 */ 
void SubString(String s, int pos, int len, String sub_s); /* 代码4-3略改 */
void StrRemove(String s, Position pos, int len);  /* 代码4-2给出 */
void StrInsert(String s, Position pos, String t); /* 代码4-1给出*/
void StrConcat(String s, String t);               /* 代码4-4给出*/
Position PatternMatch(String s, Position start, String t); /* 代码4-17略改 */ 

int main(void)
{
	String s, clipboard, s1, s2;
	int n, i;
	Position p1, p2;
	
	s = InitStr();         /* 原始字符串 */
	clipboard = InitStr(); /* 剪贴板 */
	s1 = InitStr();        /* 插入位置前的字符串 */
	s2 = InitStr();        /* 插入位置后的字符串 */
	
	ReadString(s); /* 读入原始字符串 */
	scanf("%d\n", &n); /* 读入操作次数 */
	for (i=0; i<n; i++) { /* 逐次执行操作 */
		scanf("%d %d ", &p1, &p2); /* 读入剪切位置 */ 
		SubString(s, p1, p2-p1+1, clipboard); /* 将子串存入剪贴板 */
		StrRemove(s, p1, p2-p1+1); /* 删除该子串 */
		ReadString(s1); /* 读入插入位置前的字符串 */
		ReadString(s2); /* 读入插入位置后的字符串 */
		p1 = PatternMatch(s, 0, s1); /* 从s的初始位置开始，匹配s1 */
		while (p1 != NIL) { /* 如果s1匹配成功 */
			p2 = PatternMatch(s, p1+s1->length, s2); /* 跳过s1开始匹配s2 */
			if (p1+s1->length == p2) { /* 如果匹配成功的s1和s2相连 */
				break; /* 则找到了插入的位置，跳出循环 */
			}
			else { /* 当前找到的s1不满足要求 */
				p1 = PatternMatch(s, p1+1, s1); /* 从下一个位置开始再次尝试匹配s1 */ 
			}
		}
		if (p1 != NIL) { /* 找到了插入的位置 */
			StrInsert(s, p2+1, clipboard); /* 将剪贴板内容插入 */
		}
		else { /* 插入位置没找到 */
			StrConcat(s, clipboard); /* 将剪贴板内容贴在s最后 */
		}
		clipboard->length = 0; /* 清空剪贴板 */
	}
	printf("%s\n", s->data); /* 输出最后结果 */ 
	
	return 0;
}

String InitStr()
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}


void ReadString(String s)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void SubString(String s, int pos, int len, String sub_s)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void StrRemove(String s, Position pos, int len)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void StrInsert(String s, Position pos, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


void StrConcat(String s, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
}


Position PatternMatch(String s, Position start, String t)
{
    /* TODO: 请在这里补全算法逻辑。
       main() 中的输入输出已经保留，你只需要实现本函数。 */
    return NULL;
}

