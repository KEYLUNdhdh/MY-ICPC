//拓扑思想
//拓扑，就是一个解决大小关系的东西。用有向图表示谁比谁大（大的定义要根据题意来），题目中可以抽象为级别（如本题）或年龄大小。
//既然一条线路经过的都要大于等于某个等级，那剩下的就都小于这个等级。
//这看似是废话，但其实就是废话我们可以发现，线路上停靠的点的等级都比未停靠的点的等级高。
//那这是什么，这不是大小关系吗！
//拓扑，秒了！
//所以，先拓扑排序，再分层。
//温馨提示：拓扑时是未停留的指向停留的，后面分层要用。
#include <bits/stdc++.h>
using namespace std;
int n, m;
const int MAXN = 1e3 + 5;
int ind[MAXN];
vector<int> adj[MAXN];
int used[MAXN][MAXN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m;i++)
    {
        vector<int> vis(n + 1, 0);
        vector<int> vec;
        int s;
        cin >> s;
        int u;
        for (int i = 0; i < s;i++)
        { 
            cin >> u;
            vis[u] = 1;
            vec.push_back(u);
        }
        for (int i = vec.front(); i <= vec.back();i++)
        {
            if(!vis[i])
            {
                for(auto it : vec)
                {
                    if(!used[i][it])
                    {
                        used[i][it] = 1;
                        adj[i].push_back(it);
                        ind[it]++;
                    }
                }
            }
        }
    }

    queue<int> q;
    for (int i = 1; i <= n;i++)
    {
        if(ind[i] == 0)
            q.push(i);
    }
    int cnt = 0;
    while(!q.empty())
    {
        int len = q.size();
        while(len--)
        {
            int u = q.front();
            q.pop();
            for(auto it : adj[u])
            {
                ind[it]--;
                if(ind[it] == 0)
                q.push(it);
            }
        }
        cnt++;
    }
    cout << cnt;
}