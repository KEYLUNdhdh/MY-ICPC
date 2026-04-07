#include <bits/stdc++.h>
using namespace std;

void solve(int case_num)
{
    int n, m;
    cin >> n >> m;
    // 使用邻接矩阵存储二元关系，初始化为 0
    // 节点编号为 1 到 n，所以开 n + 1 的大小
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;//有u -> v的边
    }

    //1.判断自反性
    bool is_reflexive = true;
    for (int i = 1; i <= n;i++)
    {
        if(!adj[i][i])
        {
            is_reflexive = false;
            break;
        }
    }

    //2 & 3.判断对称性与反对称性
    bool is_symmetric = true;
    bool is_antisymmetric = true;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            if(adj[i][j])
            {
                // 如果有 i->j，但没有 j->i，则不对称
                if(!adj[j][i])
                    is_symmetric = false;
                // 如果 i != j，且同时存在 i->j 和 j->i，则不反对称
                if(i != j && adj[j][i])
                    is_antisymmetric = false;
            }
        }
    }

    //4.判断传递性
    bool is_transitive = true;
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            if(adj[i][j])
            {
                for (int k = 1; k <= n;k++)
                {
                    // 存在 i->j 和 j->k，但不存在 i->k，不满足transitive
                    if(adj[j][k] && !adj[i][k])
                        is_transitive = false;
                    goto end_transitive;// 只要找到一个反例就可以直接跳出三重循环
                }
            }
        }
    }
    end_transitive:;
    // 格式化输出结果
    cout << "Case #" << case_num << "\n";
    cout << "Reflexive: " << (is_reflexive ? "Yes" : "No") << "\n";
    cout << "Symmetric: " << (is_symmetric ? "Yes" : "No") << "\n";
    cout << "Antisymmetric: " << (is_antisymmetric ? "Yes" : "No") << "\n";
    cout << "Transitive: " << (is_transitive ? "Yes" : "No") << "\n";
}

signed main()
{
    // 关流同步，加速 IO
    ios::sync_with_stdio(0);
    cin.tie(0);

    //支持多测
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T;i++)
        solve(i);

    return 0;
}