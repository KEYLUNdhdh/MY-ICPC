#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXN 1005

long long stack[MAXN];
int top = 0;

int is_integer(char s[]) {
    int i = 0;

    if (s[0] == '+' || s[0] == '-') {
        if (s[1] == '\0') return 0;  // 单独的 + 或 - 不是整数
        i = 1;
    }

    for (; s[i] != '\0'; i++) {
        if (!isdigit(s[i])) return 0;
    }

    return 1;
}

int is_operator(char s[]) {
    return strlen(s) == 1 &&
           (s[0] == '+' || s[0] == '-' || s[0] == '*' ||
            s[0] == '/' || s[0] == '%');
}

int main() {
    char line[MAXN];
    char token[MAXN];

    fgets(line, MAXN, stdin);

    char *p = strtok(line, " \n");

    while (p != NULL) {
        strcpy(token, p);

        if (is_integer(token)) {
            stack[top++] = atoll(token);
        } else if (is_operator(token)) {
            if (top < 2) {
                printf("错误：表达式不规范。\n");
                printf("%d", 1000000000);
                return 0;
            }
            long long b = stack[--top];
            long long a = stack[--top];

            if (token[0] == '+') {
                stack[top++] = a + b;
            } else if (token[0] == '-') {
                stack[top++] = a - b;
            } else if (token[0] == '*') {
                stack[top++] = a * b;
            } else if (token[0] == '/') {
                if (b == 0) {
                    printf("错误：除法操作分母为零。\n");
                    printf("%d", 1000000000);
                    return 0;
                }
                stack[top++] = a / b;
            } else if (token[0] == '%') {
                if (b == 0) {
                    printf("错误：取模操作除数为零。\n");
                    printf("%d", 1000000000);
                    return 0;
                }
                stack[top++] = a % b;
            }
        } else {
            printf("错误：表达式不规范。\n");
            printf("%d", 1000000000);
            return 0;
        }

        p = strtok(NULL, " \n");
    }

    if (top != 1) {
        printf("错误：表达式不规范。\n");
        printf("%d", 1000000000);

    } else {
        printf("%lld\n", stack[0]);
    }

    return 0;
}

// 第一次调用 char *p = strtok(line, " \n");

// 传入要切割的原始字符串 line（就是你输入的整行后缀表达式），同时指定分隔符是空格和换行符
// strtok 会从字符串开头开始找，找到第一个分隔符就把它替换成 \0，然后返回第一个 token（也就是第一个数字/运算符）的起始地址，存在指针 p 里。
// 循环里持续调用 p = strtok(NULL, " \n");

// 传入 NULL 表示从上一次切割结束的位置继续切割
// 重复“找分隔符→截断→返回当前token地址”的过程，直到遍历完整个字符串，再也找不到新的token时，返回 NULL，循环结束。




// 哦对了，遇到新建指针的玩意一定要malloc，一定要malloc