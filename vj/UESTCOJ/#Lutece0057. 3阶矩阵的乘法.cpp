#include <bits/stdc++.h>
using namespace std;
int a[3][3], b[3][3], res[3][3];

void chen(int i,int j)
{
    res[i][j] = 0;
    for (int k = 0; k < 3;k++)
    {
        res[i][j] += a[i][k] * b[k][j];
    }
}
int main()
{
    int n;
    cin >> n;
    while(n--)
    {
        for (int i = 0; i < 3;i++)
            for (int j = 0; j < 3;j++)
                cin >> a[i][j];
        for (int i = 0; i < 3;i++)
            for (int j = 0; j < 3;j++)
                cin >> b[i][j];
        for (int i = 0; i < 3;i++)
            for (int j = 0; j < 3;j++)
                chen(i, j);
        for (int i = 0; i < 3;i++)
        {
            for (int j = 0; j < 3;j++)
            {
                cout << res[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}