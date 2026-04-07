#include <bits/stdc++.h>
using namespace std;
int k,n,m;
const int MAXN = 1e3 + 5;
int ava[MAXN];
int mk[MAXN];
int vis[MAXN];
vector<int> adj[MAXN];
void dfs(int u)
{
    mk[u]++;
    for(auto it : adj[u])
    {
        if(!vis[it])
        {
            vis[it] = 1;
            dfs(it);
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> k >> n >> m;
    int tp;
    for (int i = 0; i < k;i++)
    {
        cin >> tp;
        ava[tp] = 1;
    }
    int u, v;
    for (int i = 0;i < m;i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n;i++)
    {
        if(ava[i])
        {
            vis[i] = 1;
            dfs(i);
            for (int j = 1; j <= n;j++)
                vis[j] = 0;
        }
    }
    int count = 0;
    for (int i = 1; i <= n;i++)
        count += ava[i];
        int cnt = 0;
    for (int i = 1; i <= n;i++)
    {
        if(mk[i] == count)
            cnt++;
    }
    cout << cnt;
}