#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<int> inid(30);
vector<int> adj[30];
int vis[30];
inline int  gid(char a)
{
    return (a - 'A' + 1);
}
//判断是否有环存在直接使用拓扑排序
int sortt(int ci)
{
    //传入形参，避免影响全局变量
    vector<int> ini = inid;
    queue<int> q;
    for (int i = 1; i <= n;i++)
    {
        if(vis[i] && ini[i] == 0)
            q.push(i);
    }
    int viscnt = 0;
    for (int i = 1; i <= 26; i++)
    {
        viscnt += vis[i];
    }
    vector<int> res;
    int f = 0;
    while(!q.empty())
    {
        if(q.size() != 1)
            f = 1;//如果一次性传入了两个，说明这时候条件不足
        int u = q.front();
        q.pop();
        res.push_back(u);
        if(res.size() == n)
        {
            break;
        }
        for(auto it : adj[u])
        {
            ini[it]--;
            if(ini[it] == 0)
                q.push(it);
        }
    }
    if(res.size() == n && f == 0)//成功排序
    {
        cout << "Sorted sequence determined after " << ci << " relations: ";
        for(auto it : res)
        {
            cout << (char)('A' + it - 1);
        }
        cout << ".";
        exit(0);
    }
    else if(res.size() < viscnt)//有环
    {
        return 1;
    }
    else 
    {
        //上面都没退出，说明条件不足
        return 2;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    string s;
    int cir;
    for (int i = 1; i <= m;i++)
    {
        cin >> s;
        int u = gid(s[0]);
        int v = gid(s.back());
        vis[u] = 1, vis[v] = 1;
        char bs = s[1];
        if(bs == '>')
        {
            inid[u]++;
            adj[v].push_back(u);
        }
        else
        {
            inid[v]++;
            adj[u].push_back(v);
        }
        cir = sortt(i);
        if(cir == 1)
        {
            cout << "Inconsistency found after " << i << " relations.";
            return 0;
        }
    }
    if(cir == 2)
    {
        cout << "Sorted sequence cannot be determined.";
    }
}