//线段树之所以称为“树”，是因为其具有树的结构特性。线段树由于本身是专门用来处理区间问题的（包括 RMQ、RSQ 问题等）。
//因为虽然线段树好像很快，但是它只能维护带有结合律的信息，比如区间 max/min、∑、xor 之类的，但是不带有结合律的信息就不能维护；而分块则灵活得多，可以维护很多别的东西,因为实际上分块的本质就是优雅的暴力。
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1e5 + 5;
ll n, m, a[MAXN], ans[MAXN << 2], tag[MAXN << 2];
// ans[] 是线段树数组,用来存储区间和，tag[] 是懒标记数组
//线段树一般需要开 4 倍空间

//获取左孩子
inline ll ls(ll x)
{
    return x << 1;// 左移一位，等价于 x * 2
}
//获取右孩子
inline ll rs(ll x)
{
    return x << 1|1;// 左移一位或是1，等价于 x * 2 + 1
}
//push_up: 向上更新..当子节点的信息发生变化后，更新父节点的信息。
inline void push_up(ll p)
{
    //当前节点区间和 = 左儿子区间和 + 右儿子区间和。
    ans[p] = ans[ls(p)] + ans[rs(p)];
}
//build: 建树
//l,r代表区间边界
void build(ll p,ll l,ll r)
{
    tag[p] = 0;// 初始化懒标记为 0
    if(l == r)
    {
        ans[p] = a[l];// 直接赋值
        return;
    }
    ll mid = l + r >> 1;// 取中点
    build(ls(p), l, mid);// 递归建左子树
    build(rs(p), mid + 1, r);// 递归建右子树
    push_up(p);// 子节点建好后，更新当前父节点
} 
//f 函数：处理单个节点
inline void f(ll p,ll l,ll r,ll k)
{
    tag[p] = tag[p] + k;// 1. 记录账单：在该节点上打上标记，表示"欠"下面 k 的增量
    ans[p] = ans[p] + k * (r - l + 1);// 2. 更新当前节点的值：区间内每个数都加 k，总和增加 k * 区间长度
}
// push_down 函数：下发任务
//时机: 在每次我们需要深入访问子节点（无论是查询还是修改）之前，必须先调用 push_down。
inline void push_down(ll p,ll l,ll r)
{
    ll mid = l + r >> 1;
    // 把当前节点 p 的标记 tag[p] 传给左儿子
    f(ls(p), l, mid, tag[p]);
    // 把当前节点 p 的标记 tag[p] 传给右儿子
    f(rs(p), mid + 1, r, tag[p]);
    // 当前节点的任务已经分发下去，账单清零
    tag[p] = 0;
}
//update: 区间修改
// nl, nr: 目标修改区间
// l, r: 当前节点 p 代表的区间
// k: 要增加的值
inline void update(ll nl,ll nr,ll l,ll r,ll p,ll k)
{
    // 1. 如果当前区间完全包含在目标区间内
    if(nl <= l && nr >= r)
    {
        ans[p] += k * (r - l + 1);// 直接更新当前节点数值
        tag[p] += k;// 打上懒标记，不再向下递归
        return;
    }
    // 2. 如果不完全包含，当前节点p不需要操作，后续需要下放
    push_down(p, l, r);// 【关键】下传之前的标记，防止逻辑冲突
    ll mid = l + r >> 1;
    // 如果目标区间涉及到左儿子，递归左边
    if(nl <= mid)
        update(nl, nr, l, mid, ls(p), k);
    // 如果目标区间涉及到右儿子，递归右边
    if(nr >= mid + 1)
        update(nl, nr, mid + 1, r, rs(p), k);

    push_up(p);// 子节点变了，回溯时更新父节点
}
//query: 区间查询
ll query(ll q_x,ll q_y,ll l,ll r,ll p)
{
    ll res = 0;
    // 1. 如果当前区间完全包含在查询区间内，直接返回当前节点的值
    if(q_x <= l && q_y >= r)
        return ans[p];
    ll mid = l + r >> 1;
    // 2. 否则需要深入子节点，先下放标记
    push_down(p, l, r);// 【关键】既然要查细分数据，必须把欠的账还给子节点

    // 递归查询左右两边,思路和update差不多
    if(q_x <= mid)
        res += query(q_x, q_y, l, mid, ls(p));
    if(q_y >= mid + 1)
        res += query(q_x, q_y, mid + 1, r, rs(p));
    return res;
}
void scan()
{
    cin >> n >> m;
    for (ll i = 1; i <= n;i++)
    {
        cin >> a[i];
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    scan();
    ll a1, b, c, d, e, f;
    build(1, 1, n);

    while(m--)
    {
        cin >> a1;
        if(a1 == 1)
        {
            cin >> b >> c >> d;
            update(b, c, 1, n, 1, d);
        }   
        else
        {
            cin >> e >> f;
            cout << query(e, f, 1, n, 1) << "\n";
        }
    }
    return 0;
}