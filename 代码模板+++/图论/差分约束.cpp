#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<long, long> pll;
struct DiffConstraint
{
    int n;

    vector<vector<pll>> adj;
    vector<i64> dist;
    vector<int> count;
    vector<int> inQueue;

    DiffConstraint(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        adj.assign(n + 1, vector<pll>());
        dist.assign(n + 1, 0);
        count.assign(n + 1, 0);
        inQueue.assign(n + 1, 0);
    }

    void addEdge(int u, int v, i64 w) 
    {
        adj[u].push_back({v, w});
    }

    bool sol()
    {
        queue<int> q;

        for (int i = 1; i <= n;i++)
        {
            dist[i] = 0;
            inQueue[i] = 1;
            count[i] = 1;
            q.push(i);
        }

        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            inQueue[u] = 0;

            for(const auto &[v, w] : adj[u])
            {
                if(dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;

                    if(!inQueue[v])
                    {
                        q.push(v);
                        inQueue[v] = 1;
                        count[v]++;

                        if(count[v] >= n)
                            return false;
                    }
                }
            }
        }
        return true;
    }
};