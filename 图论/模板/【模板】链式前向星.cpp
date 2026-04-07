#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
struct edge{
    int v;
    int w;
    int next;
}e[MAXN << 1];
int head[MAXN];
int cnt, n, m;
//加边函数（头插法）
//head[u] 始终指向该点最后一条加入的边。通过 next 属性，我们可以像剥洋葱一样从最后一条边一直往前找到第一条边。
void add(int u,int v)
{
    e[++cnt].v = v;// 新边指向 v
    e[cnt].w = 1;// 新边的 next 指向 head 记录的旧边
    // head 更新为新边的下标
    e[cnt].next = head[u];
    head[u] = cnt;
} 
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m;i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    for (int i = 1; i <= n;i++)
    {
        if(head[i] == 0)
        {
            cout << "None" << "\n";
            continue;
        }
        vector<int> vec;
        //链式前向星的遍历逻辑，e[j]存储的是边，所以要e[j].取出点来
        for (int j = head[i]; j;j = e[j].next)
        {
            vec.push_back(e[j].v);
        }
        sort(vec.begin(), vec.end());
        for (auto i = vec.begin(); i != vec.end();i++)
        {
            cout << *i << " ";
        }
        cout << "\n";
    }
}