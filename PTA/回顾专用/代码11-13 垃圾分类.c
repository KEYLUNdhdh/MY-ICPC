#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define kMaxNameLen 10
typedef char ElemSet[kMaxNameLen+1];  /* 默认元素为字符串*/
typedef int Position; /* 数组下标是元素的位置 */
typedef enum {Unknown, GanLaji, ShiLaji, KeHuiShou, YouHaiLaji} Type;
typedef struct RecordNode {
    ElemSet key; /* 关键字：物品名称 */
    Type type;   /* 垃圾分类 */
} Records;
#define kMaxN 100000

/* 折半查找，返回下标，若找不到返回0（哨兵位置） */
Position BinarySearch(Records record[], int low, int high, ElemSet key)
{
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = strcmp(record[mid].key, key);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;   // 返回0表示未找到，因为0位置是哨兵
}

/* 按名称升序比较，供qsort使用 */
int CmpName(const void *a, const void *b)
{
    Records *pa = (Records *)a;
    Records *pb = (Records *)b;
    return strcmp(pa->key, pb->key);
}

/* 根据类型输出对应的文字 */
void Output(Type type)
{
    switch (type) {
        case GanLaji:    printf("Gan laji\n"); break;
        case ShiLaji:    printf("Shi laji\n"); break;
        case KeHuiShou:  printf("Ke Hui Shou\n"); break;
        case YouHaiLaji: printf("You Hai laji\n"); break;
        default:         printf("?\n");
    }
}

int main()
{
    Records *items;
    ElemSet query;
    int n, i;
    
    scanf("%d\n", &n);
    items = (Records *)malloc(sizeof(Records) * (n+1));
    /* 第0个位置设为岗哨，数据从下标1开始 */
    items[0].type = Unknown; /* 哨兵类型为“不知道”*/
    for (i=1; i<=n; i++) {
        scanf("%s %d\n", items[i].key, &items[i].type);
    }
    qsort(items+1, n, sizeof(Records), CmpName);
    scanf("%s\n", query);
    while (query[0]!='#') {
          i = BinarySearch(items, 1, n, query);
          Output(items[i].type);
          scanf("%s\n", query);
    }
    
    return 0;
}

//哦牛逼，就是把字符串硬排序，然后二分查找