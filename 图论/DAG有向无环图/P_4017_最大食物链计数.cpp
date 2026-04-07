//拓扑排序 + 动态规划 (DP)
//在有向无环图中统计路径数，最标准的方法是利用拓扑排序。我们定义 f[i] 为：从生产者开始，到达生物 i 的食物链条数。
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 80112002;
const int MAXN = 5e3 + 5;
vector<int> a[MAXN];
int ind[MAXN];// 入度
int oud[MAXN];// 出度
int f[MAXN];// 存储到达该节点的路径数
int n, m;
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int u, v;
    for (int i = 0; i < m;i++)
    {
        cin >> u >> v;
        a[u].push_back(v);
        ind[v]++;// 吃人的是出边
        oud[u]++;// 被吃的是入边
    }
    queue<int> q;
    // 1. 找到所有生产者（入度为 0 且 有出边）
    // 注意：孤立点（入度0出度0）在生物学上不算食物链，需排除
    for (int i = 1; i <= n;i++)
    {
        if(ind[i] == 0)
        {
            if(oud[i] == 0)
                continue;// 排除孤立点
            f[i] = 1;
            q.push(i);
        }
    }

    int ans = 0;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        // 如果是最高级消费者（出度为 0），累加答案
        if(oud[u] == 0)
        {
            ans = (ans + f[u]) % MOD;
        }

        for(int v : a[u])
        {
            f[v] = (f[v] + f[u]) % MOD;// 路径累加
            ind[v]--;
            //如果v的入度是0，说明f[v]在此已经统计完了
            if(ind[v] == 0)
                q.push(v);
        }
    }
    cout << ans;
}