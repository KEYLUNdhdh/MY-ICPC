// // 预处理 DFN 序、深度、以及倍增求 LCA 的 ST 表
//     void dfs(int u, int p, int d)
//     {
//         dfn[u] = ++timer;
//         dep[u] = d;
//         st[0][u] = p;
//         for (int i = 1; i < 20;i++)
//             st[i][u] = st[i - 1][st[i - 1][u]];
//         for(int v : adj[u])
//         {
//             if(v != p)
//                 dfs(v, u, d + 1);
//         }
//     }

// // 倍增求 LCA
//     int getLCA(int u, int v)
//     {
//         if(dep[u] < dep[v])
//             swap(u, v);
//         for (int i = 19; i >= 0; i--)
//         {
//             if(dep[st[i][u]] >= dep[v])
//                 u = st[i][u];
//         }

//         if(u == v)
//             return u;

//         for (int i = 19; i >= 0;i--)
//         {
//             if(st[i][u] != st[i][v])
//             {
//                 u = st[i][u];
//                 v = st[i][v];
//             }
//         }
//         return st[0][u];
//     }