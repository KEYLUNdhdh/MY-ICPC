#include<stdio.h>
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

const int MAXN = 105;

signed main()
{
    int n;
    scanf("%d", &n);
    int a[MAXN];
    int b[MAXN];
    for (int i = 0; i < n;i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n;i++)
        scanf("%d", &b[i]);
    int len = -1;
    for (int i = 0; i < n - 1;i++)
    {
        if(b[i] > b[i + 1])
        {
            len = i + 1;
            break;
        }
    }
    int f = 1;
    for (int i = len; i < n;i++)
    {
        if(a[i] != b[i])
        {
            f = 0;
            break;
        }
    }
    if(f)
        printf("Insertion Sort\n");
    else
    {
        printf("Merge Sort\n");
        int tmp = 1;
        for (int i = 0; i < n - 1;i++)
        {
            if(b[i] < b[i + 1])
                tmp++;
            else
            {
                len = (len < tmp ? len : tmp);
                tmp = 1;
            }
        }
    }
    if(f)
    {
        int j = len;
        while(b[j - 1] > b[j])
        {
            int tmp = b[j];
            b[j] = b[j - 1];
            b[j - 1] = tmp;
            j--;
        }
        for (int i = 0; i < n;i++)
            printf("%d ", b[i]);
    }
    else
    {
        int l = 0, r = 2 * len - 1;
        while(l < n)
        {
            r = (r >= n ? n - 1 : r);
            MergeSort(b, l, r);
            r += 2 * len;
            l += 2 * len;
        }
        for (int i = 0; i < n;i++)
            printf("%d ", b[i]);
    }
    
}