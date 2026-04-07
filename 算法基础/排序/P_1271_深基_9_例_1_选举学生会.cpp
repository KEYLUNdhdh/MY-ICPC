#include <iostream>
#include <algorithm>
using namespace std;
int a[2000005] = {0};
int temp[2000005] = {0};
void mergesort(int a[],int left,int right,int temp[])
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergesort(a, left, mid, temp);
    mergesort(a, mid + 1, right, temp);

    int i = left, j = mid + 1;
    int index = 0;
    while (i <=mid && j <= right)
    {
        if (a[i] <= a[j])
        {
            temp[index++] = a[i++];
        }
        else
        {
            temp[index++] = a[j++];
        }
    }
    while (i <=mid)
    {
        temp[index++] = a[i++];
    }
    while (j <= right)
    {
        temp[index++] = a[j++];
    }
    for (int k = 0; k < index;k++)
    {
        a[left + k] = temp[k];
    }
}
void swap(int& a,int& b)
{
    int c = a;
    a = b;
    b = c;
}
// void quicksort(int a[],int left,int right)
// {
//     if (left >= right)
//         return;
//     int pivot = a[left + (right - left) / 2];
//     int begin = left;
//     int end = right;
//     while (begin <= end)
//     {
//         if (a[begin] < pivot && begin <=end)
//         {
//             begin++;
//         }
//         if (a[end] > pivot && begin <= end)
//         {
//             end--;
//         }
//         if (begin <= end)
//         {
//             swap(a[begin], a[end]);
//             begin++;
//             end--;
//         }
//         quicksort(a, left, end);
//         quicksort(a, begin, right);
//     }
// }
int main()
{
    ios::sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m;i++)
        cin >> a[i];
    mergesort(a, 0, m - 1, temp);
    // quicksort(a, 0, m - 1);
    // sort(a, a + m);
    for (int i = 0; i < m;++i)
    {
        cout << a[i] << " ";
    }
    return 0;
}