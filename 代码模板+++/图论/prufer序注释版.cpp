#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<int, int> pii;
struct Prufer
{
    // 1. 由树生成 Prufer 序列 (Tree to Prufer)
    // 传入点数 n 和 树的边集 edges，返回长度为 n-2 的 Prufer 序列
    static vector<int> treeToPrufer(int n, const vector<pii> &edges)
    {
        vector<int> pruferSeq;
        if(n <= 2)// n <= 2 时 Prufer 序列为空
            return pruferSeq;

        vector<int> degree(n + 1, 0);
        vector<int> xorSum(n + 1, 0);// 黑科技：维护相邻节点的异或和

        // 统计度数并计算异或和
        for(const auto &[u, v] : edges)
        {
            degree[u]++;
            degree[v]++;
            xorSum[u] ^= v;
            xorSum[v] ^= u;
        }

        // 寻找编号最小的叶子节点
        int ptr = 1;
        while(ptr <= n && degree[ptr] != 1)
            ptr++;

        int leaf = ptr;

        // 生成序列
        for (int i = 0; i < n - 2;i++)
        {
            // 当节点的度数为 1 时，它的异或和就是它唯一相邻的节点！
            int neighbor = xorSum[leaf];
            pruferSeq.push_back(neighbor);

            // 砍掉这条边，更新邻居的信息
            degree[leaf]--;
            degree[neighbor]--;
            xorSum[neighbor] ^= leaf;

            // 核心优化：如果邻居变成了新的叶子，且编号比指针 ptr 还小
            // 那么下一步必须立刻处理这个新叶子
            if(degree[neighbor] == 1 && neighbor < ptr)
                leaf = neighbor;
            else
            {
                ptr++;
                while(ptr <= n && degree[ptr] != 1)
                    ptr++;
                leaf = ptr;
            }
        }
        return pruferSeq;
    }

    // 2. 由 Prufer 序列还原树 (Prufer to Tree)
    // 传入点数 n 和长度为 n-2 的 Prufer 序列，返回树的边集 edges
    static vector<pii> pruferToTree(int n, const vector<int> &pruferSeq)
    {
        vector<pii> edges;
        if(n == 2)//特判
        {
            edges.push_back({1, 2});
            return edges;
        }

        vector<int> degree(n + 1, 1);// 初始默认所有点度数至少为 1
        for(int node : pruferSeq)
            degree[node]++;// 序列中出现一次，度数加一

        // 寻找编号最小的叶子节点
        int ptr = 1;
        while(ptr <= n && degree[ptr] != 1)
            ptr++;
        int leaf = ptr;

        // 还原连边
        for(int node : pruferSeq)
        {
            edges.push_back({leaf, node});// 最小叶子必然与序列当前元素相连
            degree[leaf]--;
            degree[node]--;

            // 同样的优化逻辑：检查是否产生了更小的新叶子
            if(degree[node] == 1 && node < ptr)
                leaf = node;
            else
            {
                ptr++;
                while(ptr <= n && degree[ptr] != 1)
                    ptr++;
                leaf = ptr;
            }
        }

        // 序列遍历完后，必然恰好剩下两个度数为 1 的节点
        int u = -1, v = -1;
        for (int i = 1; i <= n;i++)
        {
            if(degree[i] == 1)
            {
                if(u == -1)
                    u = i;
                else
                    v = i;
            }
        }

        if(u != -1 && v != -1)
            edges.push_back({u, v});// 把最后剩下的两点连起来

        return edges;
    }
};