#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<int, int> pii;
struct Prufer
{
    static vector<int> treeToPrufer(int n, const vector<pii> &edges)
    {
        vector<int> pruferSeq;
        if(n <= 2)
            return pruferSeq;

        vector<int> degree(n + 1, 0);
        vector<int> xorSum(n + 1, 0);

        for(const auto &[u, v] : edges)
        {
            degree[u]++;
            degree[v]++;
            xorSum[u] ^= v;
            xorSum[v] ^= u;
        }

        int ptr = 1;
        while(ptr <= n && degree[ptr] != 1)
            ptr++;

        int leaf = ptr;

        for (int i = 0; i < n - 2;i++)
        {
            int neighbor = xorSum[leaf];
            pruferSeq.push_back(neighbor);

            degree[leaf]--;
            degree[neighbor]--;
            xorSum[neighbor] ^= leaf;

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

    static vector<pii> pruferToTree(int n, const vector<int> &pruferSeq)
    {
        vector<pii> edges;
        if(n == 2)
        {
            edges.push_back({1, 2});
            return edges;
        }

        vector<int> degree(n + 1, 1);
        for(int node : pruferSeq)
            degree[node]++;

        int ptr = 1;
        while(ptr <= n && degree[ptr] != 1)
            ptr++;

        int leaf = ptr;
        for(int node : pruferSeq)
        {
            edges.push_back({leaf, node});
            degree[leaf]--;
            degree[node]--;

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
            edges.push_back({u, v});

        return edges;
    }
};