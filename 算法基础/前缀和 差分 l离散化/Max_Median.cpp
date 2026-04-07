#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[200005] = {0};

bool check(int p)
{
    int prefix[200005] = {0};
    for (int i = 1; i <= n;i++)
    {
        if (a[i] < p)
        {
            prefix[i] = prefix[i - 1] - 1;
        }
        else
        {
            prefix[i] = prefix[i - 1] + 1;
        }
    }
    int min_num = prefix[0];
    for (int i = k; i <= n;i++)
    {
        if (prefix[i] - min_num > 0)
        {
            return true;
        }
        min_num = min(min_num, prefix[i - k + 1]);
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> k;
    int max_n = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        max_n = max(a[i], max_n);
    }
    int l = 0;
    int r = max_n + 1;
    while (l + 1 != r)
    {
        int mid = l + r >> 1;
        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    cout << l;
}