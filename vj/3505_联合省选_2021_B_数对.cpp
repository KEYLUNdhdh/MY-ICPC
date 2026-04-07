#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAX = 5e5 + 5;
const int N = 2e5 + 5;
int a[N] = {0};
int cnt[MAX] = {0};
int n,maxx = 0;
void wayout()
{
    for (int i = 0; i < n;i++)
    {
        for (int j = 1; a[i] * j <= maxx;j++)
        {
            cnt[a[i] * j]++;
        }
    }
} 
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        maxx = max(maxx, a[i]);
    }
    wayout();
    int sumall = 0;
    for (int i = 0; i < n;i++)
    {
        sumall += cnt[a[i]];
    }
    cout << sumall - n;
}