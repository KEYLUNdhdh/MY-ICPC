#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
ll n, m,h[N],p[N];//p代表parent，记录每个节点的根
//h代表每个节点的子树的高度
void initial()//初始化高度为一，根指向自己
{
    for (ll i = 1; i <= n;i++)
    {
        p[i] = i;
        h[i] = 1;
    }
}
//查找根
ll Find(ll x)
{
    if(p[x] == x)//p[x] == x说明当前节点就是一个树的根
        return x;
    else
        ///这里执行了两个操作
        ///1.赋值:查找成功后从根节点向下更新每个节点的根，让所有遍历的节点都指向这个树的总根(等号执行完再return不影响递归
        //2.递归查找
        return p[x] = Find(p[x]);
}
//注意，再Find里p[x]可能修改，但我们没有更新树的高度h，其实不用管，总体上数的高度为logn，时间复杂度可以接受
//合并
void Union(ll x,ll y)
{
    //获取根节点
    ll rootx = Find(x);
    ll rooty = Find(y);
    //如果不是同一个树
    if(rootx != rooty)
    {
        //高度不一样，把让矮的树成为高的树的子树，不用更新高度
        if(h[rootx] > h[rooty])
        {
            p[rooty] = rootx;
        }
        else if(h[rootx] < h[rooty])
        {
            p[rootx] = rooty;
        }
        //高度一样，随便选一个成为总跟，高度加一就行
        else
        {
            p[rootx] = rooty;
            h[rooty]++;
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    initial();
    ll z, x, y;
    while(m--)
    {
        cin >> z >> x >> y;
        if(z == 1)
        {
            Union(x, y);
        }
        else
        {
            if(Find(x) == Find(y))
            {
                cout << "Y\n";
            }
            else
                cout << "N\n";  
        }
    }
}