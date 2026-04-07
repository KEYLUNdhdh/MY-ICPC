#include <bits/stdc++.h>
#define int long long
using namespace std;
int l, r;
const int MAXN = 1e5 + 5;
int isPrime[MAXN];
int Prime[MAXN];
int idx = 0;
bool f[1000005];
void ola(int n)
{
    for (int i = 0; i < MAXN;i++)
        isPrime[i] = 1;
    isPrime[1] = 0;
    for (int i = 2; i < n;i++)
    {
        if(isPrime[i])
        {
            Prime[idx] = i;
            idx++;
        }
        for (int j = 0; j < idx && Prime[j] * i <= n;j++)
        {
            isPrime[Prime[j] * i] = 0;
            if(i % Prime[j] == 0)
                break;
        }
    }
}

void ela()
{
    for (int i = 0; i < idx;i++)
    {
        int st = l / Prime[i];
        for (int j = max(2ll,(l + Prime[i] - 1)/Prime[i]);Prime[i]  * j <= r;j++)
        {
            f[Prime[i] * j - l] = true;
        }
    }
    return;
}
signed main()
{
    cin >> l >> r;
    ola(MAXN - 5);
    ela();
    int cnt = 0;
    for (int i = l; i <= r;i++)
    {
        if(i > 1 && !f[i - l])
            cnt++;
    }
    cout << cnt;
}