#include <stdio.h>
#include <stdlib.h>

// 本题要求实现
void MergeSort(int a[], int l, int r)
{
    if(l >= r)
        return;
    int mid = l + r >> 1;
    MergeSort(a, l, mid);
    MergeSort(a, mid + 1, r);
    int i = l, j = mid + 1, idx = 0;
    int len = r - l + 1;
    int tmp[len];
    while(i <= mid && j <= r)
    {
        if(a[i] <= a[j])
            tmp[idx++] = a[i++];
        else
            tmp[idx++] = a[j++];
    }
    while(i <= mid)
        tmp[idx++] = a[i++];
    while(j <= r)
        tmp[idx++] = a[j++];
    for (int k = 0; k < len;k++)
        a[k + l] = tmp[k];
}


const int MAXLEN = 5000 + 10;
int main() {
        int n;
        scanf("%d", &n);
        int a[MAXLEN];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    MergeSort(a, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}