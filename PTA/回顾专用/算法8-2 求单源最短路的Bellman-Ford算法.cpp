#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // 建图：邻接表存边
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    // 初始化距离、入队标记、松弛次数
    vector<int> dist(n, INT_MAX);
    vector<bool> inqueue(n, false);
    vector<int> cnt(n, 0);
    queue<int> q;

    const int s = 0; // 源点固定为0
    dist[s] = 0;
    q.push(s);
    inqueue[s] = true;
    cnt[s] = 1;

    bool has_neg_cycle = false;

    while (!q.empty() && !has_neg_cycle) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;

        // 松弛所有出边
        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            // 可以松弛
            // u要被松驰过才能继续传递
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                // 如果没入队就入队
                if (!inqueue[v]) {
                    cnt[v]++;
                    // 如果入队次数超过n次，说明存在负权环
                    if (cnt[v] >= n) {
                        has_neg_cycle = true;
                        break;
                    }
                    q.push(v);
                    inqueue[v] = true;
                }
            }
        }
    }

    // 输出结果
    cout << "BF returns " << (has_neg_cycle ? 0 : 1) << endl;
    for (int i = 0; i < n; i++) {
        cout << "dist[" << i << "] = " << dist[i] << endl;
    }

    return 0;
}


//一般的bellman ford
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// 边的结构体
struct Edge {
    int u, v, w;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    edges.reserve(m);

    // 读入所有边
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<int> dist(n, INT_MAX);
    const int s = 0;
    dist[s] = 0;
    bool has_neg_cycle = false;

    // 核心步骤：迭代n-1次松弛所有边
    for (int i = 0; i < n - 1; i++) {
        bool updated = false;
        for (const Edge& e : edges) {
            int u = e.u;
            int v = e.v;
            int w = e.w;
            // 可以松弛的条件
            if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        // 如果这一轮没有更新，可以提前退出
        if (!updated) break;
    }

    // 第n次迭代检查负权环：还能松弛说明存在负权圈
    for (const Edge& e : edges) {
        int u = e.u;
        int v = e.v;
        int w = e.w;
        if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
            has_neg_cycle = true;
            break;
        }
    }

    // 按要求格式输出
    cout << "BF returns " << (has_neg_cycle ? 0 : 1) << endl;
    for (int i = 0; i < n; i++) {
        cout << "dist[" << i << "] = " << dist[i] << endl;
    }

    return 0;
}
