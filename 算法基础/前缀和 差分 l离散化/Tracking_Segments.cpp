#include <bits/stdc++.h>
using namespace std;
int l[100005] = {0};
int r[100005] = {0};
int inq[100005] = {0};
int n, m;

bool check(int p)
{
    int ori[100005] = {0};
    memset(ori, -1, sizeof(ori));
    int prefix[100005] = {0};
    for (int i = 1; i <= p;i++)
    {
        ori[inq[i]] = 1;
    }
    for (int i = 1; i <= n;i++)
    {
        prefix[i] = prefix[i - 1] + ori[i];
    }
    for (int i = 0; i < m;i++)
    {
        if (prefix[r[i]] - prefix[l[i] -1] > 0)
            return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        for (int i = 0; i < m;i++)
            cin >> l[i] >> r[i];
        int q;
        cin >> q;
        for (int i = 1; i <= q;i++)
            cin >> inq[i];
        int left = 0;
        int right = q + 1;
        while(left + 1 != right)
        {
            int mid = left + right >> 1;
            if (check(mid))
                right = mid;
            else
                left = mid;
        }
        if (right == q + 1)
            cout << "-1\n";
        else
            cout << right << "\n";
    }
}