#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// 限定最大节点数 (编译期常量，用于 bitset)
const int MAXN = 2005;

// 解决单组测试数据的核心函数
void solve()
{
    int m;
    cin >> m;

    map<string, int> name2id;//存储每个节点的name到id的映射
    vector<string> id2name;//存储每个节点id到name的映射
    id2name.push_back("");// 占位符，让 ID 从 1 开始

    int node_count = 0;//统计一共有多少个节点

    // 内部 Lambda 表达式，用于动态分配 ID
    auto get_id = [&](const string &name) -> int
    {
        if(name2id.find(name) == name2id.end())
        {
            name2id[name] = ++node_count;
            id2name.push_back(name);
        }
        return name2id[name];
    };

    // 1. 先读取所有边，以此确定 node_count
    vector<pair<string, string>> edges(m);
    for (int i = 0; i < m;i++)
    {
        cin >> edges[i].first >> edges[i].second;
        get_id(edges[i].first);
        get_id(edges[i].second);
    }

    vector<vector<int>> adj(node_count + 1);//邻接表，存储每个点能到达哪些点
    vector<int> in_degree(node_count + 1, 0);//存储每个点的入度
    vector<bitset<MAXN>> reach(node_count + 1);//reach[u]为从节点u出发能够到达的节点集合（包含自身）。
    vector<bitset<MAXN>> rev_reach(node_count + 1);//rev_reach[u]从其他节点出发能到达u的节点

    // 2. 建图与自环初始化
    for (int i = 0; i < m;i++)
    {
        int u = get_id(edges[i].first);
        int v = get_id(edges[i].second);
        adj[u].push_back(v);
        in_degree[v]++;
    }

    for (int i = 1; i <= node_count;i++)
    {
        reach[i].set(i);
        rev_reach[i].set(i);
    }

    // 3. Kahn 算法拓扑排序
    vector<int> topo_order;
    queue<int> q;
    for(int i = 1;i <= node_count;i++)
    {
        if(in_degree[i] == 0)
            q.push(i);
    }

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);
        for(int v : adj[u])
        {
            in_degree[v]--;
            if(in_degree[v] == 0)
                q.push(v);
        }
    }

    // 4. 拓扑 DP 求解可达性矩阵
    // 4.1 正向拓扑序：求反向可达 (LB 基石)
    for (int i = 0; i < node_count;i++)
    {
        int u = topo_order[i];
        for(int v : adj[u])
            rev_reach[v] |= rev_reach[u];
    }

    // 4.2 逆向拓扑序：求正向可达 (UB 基石)
    for (int i = node_count - 1; i >= 0;i--)
    {
        int u = topo_order[i];
        for(int v : adj[u])
            reach[u] |= reach[v];
    }

    // 5. 处理在线查询
    int Q;
    cin >> Q;

    // 打印 bitset 辅助 Lambda
    auto print_set = [&](const bitset<MAXN> &bs) -> void
    {
        bool first = true;
        for (int i = 1; i <= node_count;i++)
        {
            if(bs[i])
            {
                if(!first)
                    cout << ", ";
                cout << id2name[i];
                first = false;
            }
        }
        if(first)
            cout << "Node";
        cout << "\n";
    };

    for (int q_idx = 1; q_idx <= Q; q_idx++)
    {
        int K;
        cin >> K;
        vector<int> subset;
        cout << "--- Query " << q_idx << " --- Subset: {";
        for (int i = 0; i < K;i++)
        {
            string name;
            cin >> name;
            if(name2id.find(name) != name2id.end())
            {
                subset.push_back(name2id[name]);
            }
            cout << name << (i == K - 1 ? "" : " ");
        }
        cout << "}\n";

        bitset<MAXN> UB;
        UB.set();
        for (int u : subset)
            UB &= reach[u];

        bitset<MAXN> LB;
        LB.set();
        for(int u : subset)
            LB &= rev_reach[u];
        
        int lub = -1, glb = -1;
        for (int i = 1; i <= node_count; i++)
        {
            if(UB[i] && (UB & reach[i]) == UB)
            {
                lub = i;
                break;
            }
        }
        for (int i = 1; i <= node_count; i++)
        {
            if(LB[i] && (LB & rev_reach[i]) == LB)
            {
                glb = i;
                break;
            }
        }   

        cout << "Upper Bounds: "; print_set(UB);
        cout << "Lower Bounds: "; print_set(LB);
        cout << "Least Upper Bound (LUB): " << (lub != -1 ? id2name[lub] : "None") << "\n";
        cout << "Greatest Lower Bound (GLB): " << (glb != -1 ? id2name[glb] : "None") << "\n\n";
    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    for (int i = 1; i <= T;i++)
    {
        cout << "========== Test Case " << i << " ==========\n";
        solve();
    }

    return 0;
}