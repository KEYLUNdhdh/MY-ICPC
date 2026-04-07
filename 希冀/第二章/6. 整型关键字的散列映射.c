#include <stdio.h>
#include <stdlib.h>

typedef enum { Empty, Active, Inactive } Status;

typedef struct {
    int key;
} Record;

typedef struct {
    Record data;
    Status status;
} DataNode;

typedef struct {
    DataNode* ht;   // 散列表数组
    int size;       // 当前元素个数
    int table_size; // 散列表长度
} HashTable;

int Hash(int key, int table_size) {
    return key % table_size;
}

// 线性探查
int SolveCollision(int key, int count) {
    return 1;
}

// 本题要求实现
int SearchHash(HashTable* htable, int key)
{
    int pos = Hash(key, htable->table_size);
    while(htable->ht[pos].status == Active && htable->ht[pos].data.key != key)
        pos = (pos + 1) % htable->table_size;
    return pos;
}

// 插入
void InsertHash(HashTable* htable, Record x) {
    int p = SearchHash(htable, x.key);
    printf("%d ", p);
    if (htable->ht[p].status != Active) {
        htable->ht[p].data = x;
        htable->ht[p].status = Active;
        htable->size++;
    }
}

int main() {
    int n, table_size;
    scanf("%d %d", &n, &table_size);

    HashTable htable;
    htable.ht = (DataNode*)malloc(table_size * sizeof(DataNode));
    htable.size = 0;
    htable.table_size = table_size;

    // 初始化
    for (int i = 0; i < table_size; i++) {
        htable.ht[i].status = Empty;
    }

    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        Record rec;
        rec.key = k;
        InsertHash(&htable, rec);
    }

    free(htable.ht);
    return 0;
}