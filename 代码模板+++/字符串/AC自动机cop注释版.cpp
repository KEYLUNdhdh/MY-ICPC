#include <bits/stdc++.h>
#define debug(x) { cerr << #x << " = " << x << "\n"; }
using namespace std;
using i64 = long long;

// 父类：纯净的字典树
struct Trie
{
    vector<array<int, 70>> ch;


    Trie()
    {
        newNode();
    }

    int newNode()
    {
        ch.push_back({0});
        return ch.size() - 1;
    }

    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        return 69;// 兜底防越界

    }

    // 核心改变：不在这里记 cnt 了！而是返回该模式串结尾的节点编号
    int insert(const string& s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u]) ch[p][u] = newNode();
            p = ch[p][u];
        }
        return p; // 返回终点编号，外部用数组存起来
    }
};

// 子类：AC自动机 (拓扑排序优化版)
struct ACAuto : public Trie
{
    vector<int> fail;
    vector<int> cnt;      // 记录每个节点被“打标记”的次数
    vector<int> bfsOrder; // 记录 BFS 出队的顺序，用作最终的拓扑序

    ACAuto() : Trie() {}

    void build()
    {
        int n = ch.size();
        fail.assign(n, 0);
        cnt.assign(n, 0);

        queue<int> q;
        for (int i = 0; i < 70; i++)
        {
            if (ch[0][i])
            {
                q.push(ch[0][i]);
                bfsOrder.push_back(ch[0][i]); // 记录入队节点
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < 70; i++)
            {
                if (ch[u][i])
                {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.push(ch[u][i]);
                    bfsOrder.push_back(ch[u][i]); // 记录入队节点
                }
                else
                {
                    ch[u][i] = ch[fail[u]][i];
                }
            }
        }
    }

    // 1. O(|S|) 极速匹配打标记
    void query(const string &t)
    {
        int u = 0;
        for (char c : t)
        {
            u = ch[u][getId(c)];
            cnt[u]++; // 究极优化：只打标记，死也不跳 fail！
        }
    }

    // 2. 拓扑排序：秋后算账，统一把频次向上推
    void topoCount()
    {
        // 倒序遍历 BFS 序列，刚好就是从 Fail 树的最底层往上推的拓扑序！
        for (int i = bfsOrder.size() - 1; i >= 0; i--)
        {
            int u = bfsOrder[i];
            cnt[fail[u]] += cnt[u]; // 把自己的访问次数，加上去送给干爹
        }
    }
    
    // 获取某个节点最终的频次
    int getCnt(int nodeId) const 
    {
        return cnt[nodeId];
    }
};

void solve()
{
    int n;
    cin >> n;

    ACAuto ac;
    vector<int> pos(n + 1); // pos[i] 记录第 i 个模式串的结尾对应的节点编号

    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        // 把插入后的终点编号存起来，这就完美解决了“有完全相同的模式串”的坑
        pos[i] = ac.insert(s); 
    }

    ac.build();

    string t;
    cin >> t;

    ac.query(t);      // 给经过的节点打标记
    ac.topoCount();   // 拓扑排序，向上汇总频次

    // 按顺序输出每个模式串的出现次数
    for (int i = 1; i <= n; i++)
    {
        cout << ac.getCnt(pos[i]) << "\n";
    }
}

int main()
{
    // 输入规模极大，一定要开快读
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}