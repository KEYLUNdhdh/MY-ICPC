//线段树可以实现区间修改+区间查询，但是树状数组不可兼得，树状数组优点是敲起来更方便
//单点修改+区间查询
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 5e5 + 5;

int n, m;
ll tree[MAXN];// 树状数组本体//tree[x] 存的不是第 x 个数的值，而是一段特定区间的和。

// 【核心函数 1】lowbit
// 获取二进制最低位的 1
inline int lowbit(int x)
{
    return x & (-x);
}
// 【核心函数 2】单点修改 (Add)
// 含义：将第 x 个数加上 k
// 逻辑：x 受到更新，所有覆盖了 x 的父节点（x + lowbit(x)）都要更新

//扩大区间的覆盖范围（右边界右移，左边界也对应左移扩展）。
//右边界从 x 变成了 y (变大了)。
//同时，由于进位消除了原来的低位 1，新的 lowbit(y) 变得更大了（翻倍甚至更多）。
//这个“变大”的幅度足够大，保证了新区间 tree[y] 的左边界一定会向左扩展（或者至少保持不变，实际上总是向左），从而牢牢地把原来的位置 x 包裹在肚子里。这个保证不会加多无关区间

//同时，x + lowbit(x) 是“紧挨着” x 的、且能包含 x 的最小父区间。这个保证不会少加有关区间
void add(int x,int k)
{
    // 只要 x 没有超出 n 的范围，就不断向上爬
    while(x <= n)
    {
        tree[x] += k;// 更新当前节点
        x += lowbit(x);// 【关键】爬向父节点
    }
}
// 含义：查询前 x 个数的和 (a[1] + ... + a[x])

//那么x -= lowbit(x)想象一下二进制也是好解决的，保证是充要的
ll query(int x)
{
    ll res = 0;
    while(x > 0)
    {
        res += tree[x];// 加上当前这一段的和
        x -= lowbit(x);// 【关键】跳向左边的邻居区间
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    // 2. 建树（初始化）
    // 这一步非常巧妙。一开始 tree 数组全是 0。
    // 我们读入一个数 val，就假装是“在位置 i 上加了 val”。
    // 这样循环一遍，树状数组就建立好了。
    for (int i = 1; i <= n;i++)
    {
        int val;
        cin >> val;
        add(i, val);
    }

    while(m--)
    {
        int op;
        cin >> op;

        if(op == 1)
        {
            int x, k;
            cin >> x >> k;
            add(x, k);
        }
        else
        {
            int x, y;
            cin >> x >> y;
            // 区间查询 [x, y]
            // 树状数组只会算 query(k) = sum[1...k]。
            // 所以 sum[x...y] = sum[1...y] - sum[1...x-1]
            cout << query(y) - query(x - 1) << "\n";
        }
    }
}