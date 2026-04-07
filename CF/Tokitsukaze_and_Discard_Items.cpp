#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n, m, k;
const int N = 1e5 + 5;
int a[N] = {0};
signed main()
{
    ios::sync_with_stdio(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= m;i++)
        cin >> a[i];
    int remove = 0;
    int cnt = 0;
    int i = 1;
    while(i <= m)
    {
        int cur = a[i] - remove;
        // int cur_ye = cur / k + 1;
        int cur_lim = k * ((cur - 1) / k + 1);
        int right = i;
        while(a[right] - remove <= cur_lim && right <= m)
            right++;
        right--;
        remove += right - i + 1;
        cnt++;
        i = right + 1;
    }
    cout << cnt;
}