#include <bits/stdc++.h>
#define ll unsigned long long
using namespace std;
const int N = 1e5 + 5;
// 动态开点需要预估空间。
// 总操作数 1e5，所以节点总数大约开到 4e6 ~ 6e6 比较稳妥。所以这里乘了120来保证
//N=10^9，树的深度约为 log_2(10^9) 约为 30。每次操作（查询或修改）最多访问 2 条路径，大约新建 30 到 60 个节点。
//
// 【修改】ls和rs改为数组，存储子节点的实际编号
ll n, m, ans[N * 120], tag[N * 120], ls[N * 120], rs[N * 120];
ll cnt = 0;// 【新增】当前已分配的节点编号计数器

// 【新增】辅助函数：计算区间 [L, R] 的初始和 (等差数列求和)
// 因为题目要求初始 a[i] = i
inline ll cal_sum(ll l,ll r)
{
    return (l + r) * (r - l + 1) / 2;
}
// push_up: 向上更新大小
inline void push_up(ll p)
{
    // 动态开点中，如果子节点不存在(为0)，则认为其值为0(但这题特殊，下面逻辑保证存在的节点才有ans)所以有的题要进一步检查
    // 实际上我们在进入子节点前都会动态创建，所以这里可以直接加
    ans[p] = ans[ls[p]] + ans[rs[p]];
}
// f 函数：处理单个节点 (逻辑不变)
inline void f(ll p,ll l,ll r,ll k)
{
    // 注意：在调用 f 之前，必须保证 p 已经存在（被创建了）
    tag[p] = tag[p] + k;
    ans[p] = ans[p] + k * (r - l + 1);
}
// push_down 函数：下发任务
// 【修改】需要动态创建子节点
inline void push_down(ll p,ll l,ll r)
{
    ll mid = l + r >> 1;
    // 如果左儿子不存在，开点，并初始化为原始数列的和
    if(!ls[p])
    {
        ls[p] = ++cnt;
        ans[ls[p]] = cal_sum(l, mid);//如果是默认开点，这里的ans是默认为零的。这题数组已经给好了要初始化
    }
    // 如果右儿子不存在，开点，并初始化
    if(!rs[p])
    {
        rs[p] = ++cnt;
        ans[rs[p]] = cal_sum(mid + 1, r);//如果是默认开点，这里的ans是默认为零的。这题数组已经给好了要初始化
    }
    // 正常下发 tag
    f(ls[p], l, mid, tag[p]);
    f(rs[p], mid + 1, r, tag[p]);
    //记得清空节点p的lazy值
    tag[p] = 0;
}

//如果题目说 N=10^9，初始时有 M 个位置有特定的值（比如 a[500]=3, a[9999]=10），其他位置是 0。
//这种情况下，不能像 build 那样一次性建成。我们通常把这些初始值看作是 M 次单点修改（Update）。先假装树全是 0（什么都不干）。读入初始数据 (index, value)，直接调用 update(index, index, 1, n, root, value)。把初始值“插入”到树里。

// update: 区间修改
// 【修改】p 改为引用传参 (ll &p)，以便修改父节点的 ls/rs 指向
inline void update(ll nl,ll nr,ll l,ll r,ll &p,ll k)
{
    // 如果当前节点不存在，动态创建
    if(!p)
    {
        p = ++cnt;
        ans[p] = cal_sum(l, r);// 初始化该节点的值为区间下标和
        //如果是默认开点，这里的ans是默认为零的。这题数组已经给好了要初始化
    }
    //如果l，r范围在目标范围内
    if(nl <= l && nr >= r)
    {
        ans[p] += k * (r - l + 1);
        tag[p] += k;
        return;//别忘了return，没有继续往下的意义
    }
    //下传标记
    push_down(p, l, r);

    ll mid = l + r >> 1;
    if(nl <= mid)
        update(nl, nr, l, mid, ls[p], k);
    if(nr >= mid + 1)
        update(nl, nr, mid + 1, r, rs[p], k);
    //更新父节点大小
    push_up(p);
}
// query: 区间查询
// 【修改】p 改为引用传参 (ll &p)
ll query(ll q_x,ll q_y,ll l,ll r,ll &p)
{
    // 如果访问到了一个不存在的节点
    if(!p)
    {
        p = ++cnt;
        ans[p] = cal_sum(l, r);// 它的值是初始状态
        // 这里不需要 return，因为可能需要继续深入或者部分重叠
        // 但其实如果完全包含且没有tag，可以直接返回。
        // 为了逻辑统一，我们让它继续走标准流程。
    }
    if(q_x <= l && q_y >= r)
        return ans[p];
    //上面没有return，说明需要向下走了，这里下传标记
    push_down(p, l, r);
    //这里做区间检查，并相应的递归处理
    ll mid = l + r >> 1;
    ll res = 0;
    if(q_x <= mid)
        res += query(q_x, q_y, l, mid, ls[p]);
    if(q_y >= mid + 1)
        res += query(q_x, q_y, mid + 1, r, rs[p]);
    //别忘了返回值
    return res;
}

void scan()
{
    cin >> n >> m;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    scan();

    ll a1, b, c, d, e, f;
    ll root = 0;// 【新增】定义根节点，初始为 0（未创建）

    while(m--)
    {
        cin >> a1;
        if(a1 == 1)
        {
            cin >> b >> c >> d;
            // 传入 root，update 内部会判断如果 root 为 0 则创建
            update(b, c, 1, n, root, d);
        }
        else
        {
            cin >> e >> f;
            cout << query(e, f, 1, n, root) << "\n";
        }
    }

    return 0;
}