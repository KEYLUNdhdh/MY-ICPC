#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int cnt[N] = {0};
int n;
int main()
{
    cin >> n;
    int a, b;
    for (int i = 0; i < n - 1;i++)
    {
        cin >> a >> b;
        cnt[a]++;
        cnt[b]++;
    }
    int need = 0;
    for (int i = 1; i <= n;i++)
    {
        if(cnt[i] < 2)
        {
            need += 2 - cnt[i];
        }
    }
    int ans = need / 2;
    need = need % 2;
    ans += 1 * need;
    cout << ans;
}