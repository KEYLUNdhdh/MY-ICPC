#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[100005] = {0};
int timecc[100005] = {0};    int n, m;
void counttime(int m)
{
    timecc[6] = 12;
    timecc[7] = 12;
    for (int i = 8; i <= m + 2;i++)
    {
        timecc[i] = min(timecc[i - 1] + timecc[i - 2], 720ll);
    }
}
signed main()
{
    int n, m;
    cin >> n >> m;
    counttime(m);
    int id;
    string tp;
    string ori;
    int cnt = 0;
    for (int i = 0; i< m;i++)
    {
        cin >> id >> tp;
        // if (i == 0)
        // {
        //     ori = tp;
        //     cnt++;
        // }
        if (tp == ori)
        {
            cnt++;
        }
        else
        {
            cnt = 1;
            ori = tp;
        }
        if (cnt >= 6)
        {
            a[id] += timecc[cnt];
        }
    }
    for (int i = 1; i <= n;i++)
    {
        if (a[i] >= 720)
            a[i] = 720;
    }
        for (int i = 1; i <= n; i++)
        {
            cout << a[i] << " ";
        }
}