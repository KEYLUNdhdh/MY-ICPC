#include <bits/stdc++.h>
#define int long long
#define ld long double
using namespace std;
int n, k;
int m[25];
int f = 0;
int sum = 0, summ = 0;
void dfs(int cur,int cnt,int su,int suu)
{
    if(f)
        return;
    if(cnt == k)
    {
        if(suu * sum == su * summ)
            f = 1;
        return;
    }
    if(cur > n)
        return;
    dfs(cur + 1, cnt + 1, su + m[cur], suu + m[cur] * cur);
    dfs(cur + 1, cnt,su, suu);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n;i++)
    {
        cin >> m[i];
        sum += m[i];
        summ += m[i] * i;
    }
    dfs(1,0,0,0);
    if(f)
        cout << "Yes";
    else
        cout << "No";
}