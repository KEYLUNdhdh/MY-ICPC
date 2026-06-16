#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMaxID 6 /* 学号长度*/
#define kMaxName 8 /* 姓名长度 */ 

typedef struct StuNode {
    char id[kMaxID+1];
    char name[kMaxName+1];
    int grade;
} ElemSet;

/* 按学号升序比较 */
int CmpID(const void *a, const void *b)
{
    return strcmp(((ElemSet*)a)->id, ((ElemSet*)b)->id);
}

/* 按姓名字典序升序，姓名相同则按学号升序 */
int CmpName(const void *a, const void *b)
{
    int ret = strcmp(((ElemSet*)a)->name, ((ElemSet*)b)->name);
    if (ret != 0) return ret;
    return strcmp(((ElemSet*)a)->id, ((ElemSet*)b)->id);
}

/* 按成绩升序，成绩相同则按学号升序 */
int CmpGrade(const void *a, const void *b)
{
    int ga = ((ElemSet*)a)->grade;
    int gb = ((ElemSet*)b)->grade;
    if (ga != gb) return ga - gb;
    return strcmp(((ElemSet*)a)->id, ((ElemSet*)b)->id);
}

int main(void)
{
    ElemSet *a;
    int n, c, i;
    
    scanf("%d %d\n", &n, &c);
    a = (ElemSet *)malloc(sizeof(ElemSet) * n);
    for (i=0; i<n; i++) {
        scanf("%s %s %d\n", a[i].id, a[i].name, &a[i].grade);
    }
    switch(c) {
        case 1: qsort(a, n, sizeof(ElemSet), CmpID); break;
        case 2: qsort(a, n, sizeof(ElemSet), CmpName); break;
        case 3: qsort(a, n, sizeof(ElemSet), CmpGrade); break;
        default: break;
    }
    for (i=0; i<n; i++) {
        printf("%s %s %d\n", a[i].id, a[i].name, a[i].grade);
    } 
    return 0;
}


// qsort要求比较函数的返回规则正好和strcmp一致：
// 字符串排出来刚好是升序
// 返回负数：表示a应该排在b前面
// 返回0：表示a和b相等
// 返回正数：表示a应该排在b后面
// 而strcmp本身的返回规则正好匹配，所以可以直接把strcmp的结果当返回值用，不需要额外转换。