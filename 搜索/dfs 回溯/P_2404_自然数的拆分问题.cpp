#include <bits/stdc++.h>
using namespace std;
int n;
int a[11] = {0};
void dfs(int s,int sum,int step)
{
    if(s == n)
        return;
    if(sum == n)
    {
        for (int i = 0; i < step;i++)
        {
            cout << a[i];
            if(i != step - 1)
                cout << "+";
        }
        cout << "\n";
        return;
    }
    for (int i = s; i <= n - sum;i++)
    {
        a[step] = i;
        dfs(i, sum+ i, step + 1);
    }
    return;
}
int main()
{
    
    cin >> n;
    dfs(1, 0, 0);
}