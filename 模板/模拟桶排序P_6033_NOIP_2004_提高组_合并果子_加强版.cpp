#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e7 + 5;
const int MAX = 1e5 + 1;
int q1[N], q2[N];
int h1, h2, t1, t2;
int cnt[MAX];
inline int read()
{
    char ch;
    ch = getchar();
    int x = 0;
    int f = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
signed main()
{
    ios::sync_with_stdio(0);
    int n;
    n = read();
    int val;
    for (int i = 0; i < n;i++)
    {
        val = read();
        cnt[val]++;
    }
    h1 = 0, h2 = 0, t1 = 0, t2 = 0;
    for (int i = 0; i < MAX;i++)
    {
        while(cnt[i] > 0)
        {
            q1[t1++] = i;
            cnt[i]--;
        }
    }
    int ans = 0;
    int x, y;
    for (int i = 0; i < n - 1;i++)
    {
        if (h2 == t2 || h1 < t1 && q1[h1] < q2[h2])
        {
            x = q1[h1++];
        }
        else
        {
            x = q2[h2++];
        }
        if (h2 == t2 || h1 < t1 && q1[h1] < q2[h2])
        {
            y = q1[h1++];
        }
        else
        {
            y = q2[h2++];
        }
        ans += x + y;
        q2[t2++] = x + y;
    }
    cout << ans;
    return 0;
}