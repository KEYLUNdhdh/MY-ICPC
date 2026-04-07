#include <bits/stdc++.h>
using namespace std;
int a[10][10];
int vis[5];
int main()
{
    int sx, sy;
    for (int i = 1; i <= 4;i++)
    {
        for (int j = 1; j <= 4;j++)
        {
            cin >> a[i][j];
            if(a[i][j] == 0)
                sx = i, sy = j;
        }
    }
    for (int k = 1; k <= 4;k++)
    {
        vis[a[sx][k]] = 1;
    }
    for (int i = 1; i <= 4;i++)
    {
        if(!vis[i])
            cout << i;
    }
}