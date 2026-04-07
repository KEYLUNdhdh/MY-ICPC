//欧拉通路 (Eulerian Path) 是指在一个图中，从某一个点出发，经过图中每一条边且仅经过一次的路径。如果这条路径最后回到了起点，则称为欧拉回路。
//当你面临的问题可以抽象为“不重复地走完所有街道/边”时，就需要用到它。在本题中，每个单词必须且只能使用一次，而单词的连接（首尾字母相同）恰好构成了边的指向。
//度数平衡：
//情况 A（回路）：所有点的入度 = 出度。
//情况 B（通路）：
//恰好有一个点：out-degree - in-degree = 1（起点）。
//恰好有一个点：in-degree - out-degree = 1（终点）。
//其余所有点：in-degree = out-degree。
#include <bits/stdc++.h>
using namespace std;
struct Node{
    int to, id;
    string word;
};// 边结构体：去向（末字母）、原始编号（防重）、单词全文
int n;
const int MAXN = 1e3 + 5;
string s[MAXN];
vector<Node> adj[MAXN];// 邻接表，存储以某个字母开头的所有单词
int in[30], out[30], fa[30];// 入度、出度、并查集父亲数组
bool exist[30];// 记录哪些字母在单词中出现过
int vis[MAXN];//标记边是否被走过，这是处理“每条边仅一次”的核心。
string path[MAXN];// 存储当前搜寻到的路径

int Find(int x)
{
    if(fa[x] == x)
        return x;
    else
        return fa[x] = Find(fa[x]);
}
//为什么能保证字典序最小？ 因为我们在 main 函数里预先对 s 数组进行了 sort，导致 adj[u] 里的边是按字母序插入的。DFS 总是优先尝试字典序小的单词。
void dfs(int u,int step)
{
    if(step == n)// 边界条件：已经用完了所有 n 条边
    {
        for (int i = 0; i < n;i++)
            cout << path[i] << (i == n - 1 ? "" : ".");
        exit(0);// 关键：找到第一个解（最小字典序）直接强制结束程序
    }
    //在main函数里的处理保证这里每次尝试都是最小字典序
    for (int i = 0; i < adj[u].size();i++)
    {
        Node &e = adj[u][i];
        if(!vis[e.id])
        {
            vis[e.id] = 1;
            path[step] = e.word;
            dfs(e.to, step + 1);
            vis[e.id] = 0;
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n;i++)
        cin >> s[i];
    sort(s, s + n);// 字典序保证的第一步
    for (int i = 1; i <= 26;i++)
        fa[i] = i;
    for (int i = 0; i < n;i++)
    {
        int u = s[i][0] - 'a' + 1;// 起点：首字母
        int v = s[i].back() - 'a' + 1;// 终点：末字母
        adj[u].push_back({v, i, s[i]});
        // 更新度数
        out[u]++;
        in[v]++;
        exist[u] = exist[v] = true;//字符存在
        //并查集合并
        int fu = Find(u), fv = Find(v);
        if(fu != fv)
            fa[fu] = fv;
    }

    int root = -1;
    for (int i = 1; i <= 26;i++)
    {
        if(exist[i])
        {
            if(root == -1)
                root = Find(i);//尽量找最小的字母作为起点
            //如果不在一个集合中，说明不存在欧拉通路，即所有点不连通，退出即可
            else if(Find(i) != root){
                cout << "***";
                return 0;
            }
        }
    }
    //如果是欧拉回路（所有点入度=出度），则 start_node 和 end_node 都会保持 -1
    //如果是欧拉通路，必须满足：一个点 out = in + 1，另一个点 in = out + 1。
    int start_node = -1,end_node = -1;
    int bad = 0;//判断是否可行
    for (int i = 1; i <= 26;i++)
    {
        if(!exist[i])
            continue;
        if(in[i] != out[i])
        {
            if(out[i] == in[i] + 1)
            {
                if(start_node != -1)
                    bad = 1;
                start_node = i;
            }
            else if(in[i] == out[i] + 1)
            {
                if(end_node != -1)
                    bad = 1;
                end_node = i;
            }
            else// 其他度数不平衡的情况
                bad = 1;
        }
    }
    // 特判情况：欧拉回路。从字典序最小的单词首字母开始
    if(start_node == -1 && end_node == -1)
    {
        start_node = s[0][0] - 'a' + 1;
    }
    // 只有一个不平衡，不符合规律
    else if(start_node == -1 || end_node == -1)
    {
        bad = 1;
    }
    if(bad)
        cout << "***";
    else
    {
        dfs(start_node, 0);
        //如果dfs里没结束说明构造不出来
        cout << "***";
    }
}