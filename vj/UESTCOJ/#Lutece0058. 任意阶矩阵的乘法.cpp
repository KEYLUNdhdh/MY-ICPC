#include <bits/stdc++.h>
using namespace std;
int a[20][20], b[20][20], res[20][20];
int m,n,q;
void chen(int i,int j)
{
    res[i][j] = 0;
    for (int k = 0; k < n;k++)
    {
        res[i][j] += a[i][k] * b[k][j];
    }
}
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> m >> n >> q;
        for (int i = 0; i < m;i++)
            for (int j = 0; j < n;j++)
                cin >> a[i][j];
        for (int i = 0; i < n;i++)
            for (int j = 0; j < q;j++)
                cin >> b[i][j];
        for (int i = 0; i < m;i++)
            for (int j = 0; j < q;j++)
                chen(i, j);
        for (int i = 0; i < m;i++)
        {
            for (int j = 0; j < q;j++)
            {
                cout << res[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}