#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200;
vector<int> adj[MAXN];
int inDegree[MAXN];
int n;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    int tp;
    for (int i = 1; i <= n;i++)
    {
        cin >> tp;
        while(tp != 0)
        {
            adj[i].push_back(tp);
            inDegree[tp]++;
            cin >> tp;
        }
    }
    queue<int> q;
    for (int i = 1; i <= n;i++)
    {
        if(inDegree[i] == 0)
            q.push(i);
    }
    int cnt = 0;
    vector<int> res;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        res.push_back(u);
        for (int i = 0; i < adj[u].size();i++)
        {
            int v = adj[u][i];
            inDegree[v]--;
            if(inDegree[v] == 0)
                q.push(v);
        }
        cnt++;
    }
    if (cnt == n)
    {
        for (int i = 0; i < res.size();i++)
            cout << res[i] << " "   ;
    }
}