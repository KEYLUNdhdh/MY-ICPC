#include <bits/stdc++.h>
using namespace std;
int n;
int ans[15];
int line[15];
int diag1[30];
int diag2[30];
int cnt = 0;
void dfs(int row)
{
    if(row > n)
    {
        cnt++;
        if(cnt <= 3)
        {
            for (int i = 1; i <= n;i++)
                cout << ans[i] << " ";
            cout << "\n";
        }
        
    }
    for (int j = 1; j <= n;j++)
    {
        if(!line[j] && !diag1[row + j] && !diag2[row - j + n])
        {
            ans[row] = j;
            line[j] = 1;
            diag1[j + row] = 1;
            diag2[row - j + n] = 1;
            dfs(row + 1);
            line[j] = 0;
            diag1[j + row] = 0;
            diag2[row - j + n] = 0;
        }
    }
}
int main()
{
    cin >> n;
    dfs(1);
    cout << cnt;
}