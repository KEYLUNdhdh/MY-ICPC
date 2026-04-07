#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
vector<int> adj[MAXN];// 邻接表：adjlist[u] 存储 u 指向的所有点 v
int inDegree[MAXN] = {0};// 入度数组,记录每个点的依赖数。
int main()
{
    int n, m;
    cin >> n >> m;
    
    
    int a, b;
    for (int i = 0; i < m;i++)
    {
        cin >> a >> b;
        adj[a].push_back(b);// 建立 A -> B 的边
        inDegree[b]++;// B 的入度增加 1
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if(inDegree[i] == 0)
        {
            q.push(i);// 寻找所有“起点”
        }
    }
    int cnt = 0;// 记录弹出的节点数量   
    vector<int> res;// 存储拓扑序列结果
    while(!q.empty())
    {
        int u = q.front();// 弹出当前一个入度为 0 的点
        q.pop();
        res.push_back(u);
        for (int i = 0; i < adj[u].size();i++)
        {
            int v = adj[u][i];// 遍历 u 的所有邻居 v
            inDegree[v]--;// 既然 u 已经处理完了，v 的依赖减少 1
            if(inDegree[v] == 0)// 如果 v 的依赖归零，说明 v 也可以处理了
                q.push(v);
        }
        cnt++;// 处理完一个点，计数器加 1
    }
    if(cnt == n)// 只有处理过的点数等于总点数，才说明无环
    //相应的，如果拓扑排序没能遍历所有的点，说明有环
    {
        for (int i = 0; i < res.size();i++)
        {
            cout << res[i];
            // 格式控制：最后一个数后面没有空格
            if(i != res.size() - 1)
                cout << " ";
        }
    }
    else// 存在环，输出 -1
        cout << -1;
}
