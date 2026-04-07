#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
//多源bfs
void solve()
{
    int n, m;
    cin >> n >> m;
    //邻接表
    vector<vector<int>> ve(n + 1, vector<int>());
    //入度
    vector<int> ind(n + 1);
    for (int i = 1; i <= m;i++)
    {
        int u, v;
        cin >> u >> v;
        ind[u]++, ind[v]++;
        //双向建边
        ve[u].push_back(v);
        ve[v].push_back(u);
    }
    //统计每个繁华度的点，顺便排好了序
    map<int, deque<int>> mp;
    for (int i = 1; i <= n;i++)
    {
        mp[ind[i]].push_back(i);
    }
    vector<int> dis(n + 1, 1e9), ans(n + 1);
    //&减小空间占用
    //views::reverse反向遍历
    //x繁华度，q为该繁华度的所有点
    //繁华度最多有sqrt(m)种
    for(auto &[x , q] : mp | views::reverse)
    {
        for(auto &i : q)
        {
            //从高到低扫，如果dis[i]没更新过，说明它不能到达更高繁华度的点直接置为-1
            if(dis[i] > 1e8)
                dis[i] = -1;
            //更新从高到低的最短距离
            ans[i] = dis[i];
            //将距离置为0，因为我们此时从这个繁华度的点出发了
            dis[i] = 0;
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop_front();
            for(int &v : ve[u])
            {
                //繁华度更高的点不去
                if(ind[v] >= x)
                    continue;
                //如果相邻点此时距离更短，那么更新
                if(dis[v] > dis[u] + 1)
                {
                    dis[v] = dis[u] + 1;
                    //这时候这个点周围的点都会受到影响，进入队列准备更新
                    q.push_back(v);
                }
            }
        }
    }
    for (int i = 1; i <= n;i++)
        cout << ans[i] << " ";
    return;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}