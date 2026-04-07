#include <bits/stdc++.h>
using namespace std;
int cur[10005] = {0};
int vis[10005] = {0};
int f[10005] = {0};//建立递归层
int n,m;
void dfs(int step,vector<int>& vec,int index)
{
    if (step == n)
    {
        m--;
        if (m == -1)
        {
            for (int i = 0; i < vec.size();i++)
            {
                cout << vec[i] << ((i != vec.size() - 1) ? " " : "")    ;
            }
            exit(0);
        }
        return;
    }
    for (int i = (f[index] == 0 ? cur[index] : 1); i <= n;i++)
    {
        if(!vis[i])
        {
            vec.push_back(i);
            vis[i] = 1;
            dfs(step + 1, vec, index + 1);
            vec.pop_back();
            vis[i] = 0;
        }
    }
    f[index] = 1;
    return;
}

int main()
{
    cin >> n >> m;
    // m++;
    for (int i = 1; i <=n;i++)
    {
        cin >> cur[i];
    }
    vector<int> vec;
    dfs(0,vec, 1);
}