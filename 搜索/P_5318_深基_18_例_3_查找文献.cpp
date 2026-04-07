#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
vector<int> a[MAXN];
int vis[MAXN];
int n, m;
void dfs(int k)
{
    if(!vis[k])
    {
        cout << k << " ";
        vis[k] = 1;
    }
    if(a[k].empty())
        return;
    for (auto i : a[k])
    {
        //if判断的位置很重要
        if(!vis[i])
            dfs(i);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

   
    cin >> n >> m;
    int x, y;
    for (int i = 1; i <= m;i++)
    {
        cin >> x >> y;
        a[x].push_back(y);
    }
    for (int i = 1; i <= n;i++)
    {
        sort(a[i].begin(), a[i].end());
    }
    // dfs
    dfs(1);
    cout << "\n";
    //bfs
    memset(vis, 0, sizeof vis);
    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while(!q.empty())
    {
            int k = q.front();
            q.pop();
            cout << k << " ";
            for(auto i : a[k])
            {
                //if判断的位置很重要
                if(!vis[i])
                {
                    vis[i] = 1;
                    q.push(i);
                }
            }
    }
}