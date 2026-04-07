#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
//其实我们还可以拓扑排序去找环，这个好理解一点，不过写起来比较麻烦
//dfs去查找环
//1. 核心原理：“迷宫拉线法”
// 想象你正在走一个极其复杂的迷宫，你手里拿着一团毛线，每走一步就放线，并且在经过的房间墙上画个 ✓（标记已访问）。
// 探索：你不断进入没画 ✓ 的新房间。
// 避免回头：你进下一个房间时，绝不会顺着手里的线直接退回刚刚离开的那个房间。
// 发现环：突然，你推开一扇门，发现这个房间墙上居然已经画过 ✓ 了！ 而且你很确定，这个房间绝不是你上一秒刚刚离开的那个房间。这意味着什么？意味着你绕了一圈，又走回了之前来过的地方！
// 回溯提取：现在，你只要顺着手里拉出的毛线，从当前房间一路往回倒带，直到退回那个画过 ✓ 的房间。你刚刚顺着毛线往回走的这条路径，加上这扇“撞车”的门，就完完整整地构成了一个环！

//当我们发现矛盾时，我们用start和end去标记迷宫的环的终点和起点，后面直接退出整个dfs。

//所以说最终，我们标记了每个点的parent，在退出dfs后，通过一个while循环就能把环上的所有点取出来。后面就是二分查找了
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> vis(n + 1, 0);
    vector<int> pa(n + 1, -1);
    for (int i = 0; i < n;i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> cycle;
    int s = -1, e = -1;
    auto dfs = [&](auto self, int u, int p) -> void
    {
        vis[u] = 1;
        pa[u] = p;
        for(int v : adj[u])
        {
            if(v == p)
                continue;
            if(vis[v])
            {
                s = v;
                e = u;
                return;
            }

            self(self, v, u);

            if(s != -1)
                return;
        }
    };
    dfs(dfs, 1, 0);
    int cur = e;
    while(cur != s)
    {
        cycle.push_back(cur);
        cur = pa[cur];
    }
    cycle.push_back(s);
    auto query = [&](int u, int v) -> int
    {
        cout << "? " << u << " " << v << "\n";
        cout.flush();
        int res;
        cin >> res;
        return res;
    };
    int ans = query(s, e);
    if(ans != 1)
    {
        cout << "! " << s << " " << e << "\n";
        cout.flush();
        return;
    }
    int len = cycle.size();
    int l = 0, r = len - 1;
    int cnt = 0;
    while(l + 1 < r)
    {
        int idx = l + r >> 1;
        int mid = cycle[idx];
        ans = query(cycle[l], mid);
        int dis = idx - l;
        if(ans == dis)
            l = idx;
        else
            r = idx;
    }
    cout << "! " << cycle[l] << " " << cycle[r] << "\n";
    cout.flush();
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}