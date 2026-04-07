#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int p[N] = {0};
int n, q;
int u, k;
vector<int> adj[N];//以vector<int>为元素的数组
int sz[N];//存储子树大小
int pos[N];//存储每个节点在dfs序列的下标
vector<int> order;//存储dfs序列
void dfs(int u)
{
    //这个是sz算上当前这个节点u，所以为1
    sz[u] = 1;
    //这个存储的是u在整个order里的索引
    pos[u] = order.size();
    //存进u
    order.push_back(u);
    //遍历u的子节点
    for (int v: adj[u])
    {
        //简简单单递归好吧,访问构建dfs序，每个节点只被遍历一次.
        dfs(v);
        // 递归计算子树的大小
        sz[u] += sz[v];
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> q;
    int parent;
    for (int i = 2; i <= n;i++)
    {
        cin >> parent;
        adj[parent].push_back(i);
    }
    //预处理
    dfs(1);
    while (q--)
    {
        cin >> u >> k;
        if (k > sz[u])
        {
            cout << "-1\n";
            continue;
        }
        else
        {
            cout << order[pos[u] + k - 1] << "\n";
        }
    }
}

// 树的 先序遍历（Pre-order Traversal，也就是 DFS 序）。
// DFS 序（DFS Order）：
// 题目中描述：军官 a 选择最小编号的下属 b，传达命令，直到 b 的分支全部传达完，再找下一个下属。这正是深度优先搜索（DFS）的过程。
// 整棵树的 DFS 序是固定的：如果我们从根节点（指挥官 1）开始做一次 DFS，我们可以得到一个包含所有军官的序列（我们称之为 order 数组）。
// 子树的 DFS 序是连续的：这是 DFS 的一个重要性质：在一棵树的 DFS 序列中，以 $u$ 为根的子树内的所有节点，会连续地排在 u 的后面。
// 假设：pos[u] 是军官 u 在全局 DFS 序列 order 中的起始下标。sz[u] 是以 $u$ 为根的子树的大小（包括 u 自己）。那么，如果我们从 u 开始传播命令，被访问到的节点序列，正是全局 order 数组中从 pos[u] 开始，长度为 sz[u] 的那一段。
// 处理查询 (u, k)：我们要找从 u 开始传播的第 k 个人。因为 u 自己是第 1 个人，所以我们要找的人在全局数组 order 中的下标应该是 pos[u] + k - 1。
// 边界检查： 如果 k > sz[u]，说明 u 的子树里没有那么多人，输出 -1。否则，输出 order[pos[u] + k - 1]。
// 算法步骤建图： 
// 读取输入，利用邻接表 vector<int> adj[N] 存图。注意题目要求“选择最小编号的下属”，输入时 i 从 2 增加到 n，我们直接将 i 加入其父节点的列表中，列表天然就是有序的，不需要额外排序。
// 预处理（DFS）： 从根节点 1 开始跑一遍 DFS。记录全局 DFS 序列 order。记录每个节点在序列中的位置 pos[u]。记录每个节点的子树大小 sz[u]。
// 回答查询： 对于每个询问 (u, k)，利用 O(1) 的公式直接输出结果。





//AI给的代码
// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// const int N = 200005;

// // adj 存储邻接表
// vector<int> adj[N];
// // sz 存储子树大小
// int sz[N];
// // pos 存储每个节点在 dfs 序列中的下标 (0-based)
// int pos[N];
// // order 存储 dfs 序列，order[i] 表示第 i 个被访问的节点编号
// vector<int> order;

// // 深度优先搜索
// void dfs(int u) {
//     // 记录当前节点 u 的子树大小初始为 1 (它自己)
//     sz[u] = 1;
//     // 记录 u 在全局序列中的位置
//     pos[u] = order.size();
//     // 将 u 加入全局序列
//     order.push_back(u);

//     // 递归访问所有子节点
//     for (int v : adj[u]) {
//         dfs(v);
//         // 回溯时累加子树大小
//         sz[u] += sz[v];
//     }
// }

// int main() {
//     // 优化输入输出速度
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, q;
//     if (cin >> n >> q) {
//         // 读取树的结构
//         // 输入给的是 p2, p3 ... pn，即节点 i 的父亲是 pi
//         for (int i = 2; i <= n; i++) {
//             int parent;
//             cin >> parent;
//             adj[parent].push_back(i);
//         }

//         // 预处理
//         dfs(1);

//         // 处理查询
//         for (int i = 0; i < q; i++) {
//             int u, k;
//             cin >> u >> k;

//             // 如果 k 大于 u 的子树大小，说明超出范围
//             if (k > sz[u]) {
//                 cout << "-1\n";
//             } else {
//                 // u 在 order 中的位置是 pos[u]
//                 // u 是第 1 个，我们要找第 k 个
//                 // 所以偏移量是 k - 1
//                 cout << order[pos[u] + k - 1] << "\n";
//             }
//         }
//     }
//     return 0;
// }