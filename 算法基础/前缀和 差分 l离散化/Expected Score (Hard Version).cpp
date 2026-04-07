// ld ji(ld a,ld l,ld r)
// {
//     if (a > r)
//     {   
//         return ((a * a * r - a * a * l) - (r * r * r / (ld)3 - l * l * l / (ld)3));
//     }
//     else if(a < l)
//     {
//         return ((r * r * r / (ld)3 - l * l * l / (ld)3) - (a * a * r - a * a * l));
//     }
//     else
//     {
//         return (4 * a * a * a / (ld)3 - a * a * (l + r) + (l * l * l + r * r * r) / (ld)3);
//     }
// }
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
typedef struct segment{
    ld l, r;
}seg;
int n, m;
const int N = 1e5 + 5;
ld a[N] = {0};
seg lr[N];
ld prefix_san[N];
ld prefix_rdisl[N];

bool comp(seg s1,seg s2)
{
    return s1.l < s2.l;
}
int binary_rend(int a)
{
    int left = 0;
    int right = m + 1;
    while(left + 1 != right)
    {
        int mid = left + right >> 1;
        if(lr[mid].r <= a)
            left = mid;
        else
            right = mid;
    }
    return left;
}
int binary_lstart(int a)
{
    int left = 0;
    int right = m + 1;
    while(left + 1 != right)
    {
        int mid = left + right >> 1;
        if(lr[mid].l < a)
            left = mid;
        else
            right = mid;
    }
    return right;
}
int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n;i++)
        cin >> a[i];
    for (int i = 1; i <= m;i++)
        cin >> lr[i].l;
    for (int i = 1; i <= m;i++)
        cin >> lr[i].r;
    sort(lr + 1, lr + m + 1, comp);
    // int posrend = 0, poslstart = 0;
    prefix_san[0] = 0;
    prefix_rdisl[0] = 0;
    ld tlen = 0;
    for (int i = 1; i <= m;i++)
    {
        tlen += lr[i].r - lr[i].l;
    }
    for (int i = 1; i <= m; i++)
    {
        prefix_san[i] = lr[i].r * lr[i].r * lr[i].r / (ld)3 - lr[i].l * lr[i].l * lr[i].l / (ld)3 + prefix_san[i - 1];
    }
    for (int i = 1; i <= m;i++)
    {
        prefix_rdisl[i] = prefix_rdisl[i - 1] + lr[i].r - lr[i].l;
    }
        ld ans = 0;
    for (int i = 1; i <= n;i++)//a < l在右边 a > r 在左边
    {
        int posrend = binary_rend(a[i]);
        int poslstart = binary_lstart(a[i]);
        // ld temp = 0;
        ld tp1 = prefix_rdisl[posrend] * a[i] * a[i] - prefix_san[posrend];
        ld tp2 = (prefix_san[m] - prefix_san[poslstart - 1]) - (prefix_rdisl[m] - prefix_rdisl[poslstart - 1]) * a[i] * a[i];
        for (int k = posrend + 1; k < poslstart;k++)
        {
            ans += (4 * a[i] * a[i] * a[i] / (ld)3 - a[i] * a[i] * (lr[k].l + lr[k].r) + (lr[k].l * lr[k].l * lr[k].l + lr[k].r * lr[k].r * lr[k].r) / (ld)3);
        }
        ans += tp1 + tp2;
    }
    ans = ans / ((ld)n * tlen);
    cout  << fixed << setprecision(10)<< ans;
}