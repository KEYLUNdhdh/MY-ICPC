#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;      // 数据数组，从索引1开始使用
    int size;       // 当前规模
    int capacity;   // 堆容量
} MinHeap;

// 创建最小堆
MinHeap* CreateMinHeap(int capacity) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h->capacity = capacity;
    h->size = 0;
    h->data = (int*)malloc((capacity + 1) * sizeof(int)); // 0号不使用
    return h;
}

// 上调操作
void SiftUp(MinHeap* heap, int i) {
    int elem = heap->data[i];
    while (i > 1 && elem < heap->data[i / 2]) {
        heap->data[i] = heap->data[i / 2];
        i /= 2;
    }
    heap->data[i] = elem;
}

// 下调操作
void SiftDown(MinHeap* heap, int i) {
    int elem = heap->data[i];
    int last = heap->size;
    while (1) {
        int child = i * 2;
        if (child < last && heap->data[child + 1] < heap->data[child])
            child++;
        if (child > last)
            break;
        if (heap->data[child] < elem) {
            heap->data[i] = heap->data[child];
            i = child;
        } else
            break;
    }
    heap->data[i] = elem;
}

// 插入操作
void Insert(MinHeap* heap, int x) {
    if (heap->size == heap->capacity) {
        printf("错误：堆已满，无法插入。\n");
        return;
    }
    heap->size++;
    heap->data[heap->size] = x;
    SiftUp(heap, heap->size);
}

// 删除堆顶
int ExtractMin(MinHeap* heap) {
    int minKey = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    SiftDown(heap, 1);
    return minKey;
}

// 本题要求实现
void Path(MinHeap* h, int x)
{
    while(x >= 1)
    {
        printf("%d", h->data[x]);
        if(x > 1)
            printf(" ");
        x /= 2;
    }
    printf("\n");
    
}
int main() {
    int n, m, x;
    scanf("%d %d", &n, &m);
    
    MinHeap* h = CreateMinHeap(n);
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        Insert(h, x);
    }
    for (int i = 0; i < m; i++){
        scanf("%d", &x);
        Path(h, x);
    }
    
    free(h->data);
    free(h);
    return 0;
}