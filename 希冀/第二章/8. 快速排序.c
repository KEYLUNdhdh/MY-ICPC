#include <stdio.h>


// 本题要求实现
void QuickSort(int a[], int l, int r)
{
    if(l >= r)
        return;
    int pivot = a[(l + r) / 2];
    int begin = l;
    int end = r;
    while(begin <= end)
    {
        while(a[begin] < pivot && begin <= end)
            begin++;
        while(a[end] > pivot && begin <= end)
            end--;
        if(begin <= end)
        {
            int tmp = a[begin];
            a[begin] = a[end];
            a[end] = tmp;
            begin++;
            end--;
        }
    }
    QuickSort(a, l, end);
    QuickSort(a, begin, r);
}
const int MAXLEN = 5000 + 10;
int main() {
        int n;
        scanf("%d", &n);
        int a[MAXLEN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    QuickSort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}