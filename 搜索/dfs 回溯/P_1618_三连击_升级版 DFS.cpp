#include <bits/stdc++.h>
using namespace std;
vector<int> vec(10,0);
int vis[10] = {0};
int a, b, c;
int flag = 0;
int num(int m)
{
    int x = 0;
    for (int i = m * 3 - 2; i <= m * 3;i++)
    {
        x = x * 10 + vec[i];
    }
    return x;
}
void dfs(int step)
{
    if (step == 10 && num(1) * b == num(2) * a && num(2) * c == num(3) * b)
    {
        for (int i = 1; i <= 9;i++)
        {
            cout << vec[i];
            if (i % 3 == 0)
                cout << " ";
        }
        cout << "\n";
        flag = 1;
        return;
    }
    if (step == 10)
    {
        return;
    }
    for (int i = 1; i <= 9;i++)
    {
        if (!vis[i])
        {
            vis[i] = 1;
            vec[step] = i;
            dfs(step + 1);
            vis[i] = 0;
            vec[step]  = 0;
        }
    }
    return;
}
int main()
{
    cin >> a >> b >> c;
    dfs(1);
    if(!flag)
    {
        cout << "No!!!";
    }
}