//线段树可以实现区间修改+区间查询，但是树状数组不可兼得，树状数组优点是敲起来更方便
//区间修改+单点查询
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
const int MAXN = 5e5 + 5;
int tree[MAXN];//tree是维护的差分数组，满足tree[i] = a[i] - a[i  -1]
// 【核心函数 1】lowbit
inline int lowbit(int x)
{
    return x & (-x);
}
// 【核心函数 2】单点修改
// 在差分数组中，这意味着：差分值 d[x] 增加了 k
void add(int x,int k)
{
    while(x <= n)
    {
        tree[x] += k;
        x += lowbit(x);
    }
}
// 【核心函数 3】前缀查询
// 在差分数组中，求前缀和 query(x) 得到的就是 原数组 a[x] 的值
int query(int x)
{
    int res = 0;
    while(x > 0)
    {
        res += tree[x];
        x -= lowbit(x);
    }

    return res;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    // 3. 【建树过程】 (关键变化点)
    // 我们需要维护差分数组。
    // a[i] 的初始值对于差分数组的影响是：d[i] = a[i] - a[i-1]
    int prev = 0;// 记录上一个数 a[i-1]
    int now = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> now;
        // 核心：插入差分值
        add(i, now - prev);
        prev = now;
    }
    int op, x, y,k;
    while(m--)
    {
        cin >> op;
        if(op == 1)
        {
            cin >> x >> y >> k;
            //让 d[x] 增加 k（这样查询前缀和时，从 x 开始往后的所有数都变大了k）。
            //让 d[y+1] 减少 k（这样从 y+1 开始往后的数，抵消了之前的增加，恢复原状）。
            add(x, k);
            add(y + 1, -k);
        }
        else
        {
            cin >> x;
            // 操作 2: 单点查询 x
            // 差分数组的前缀和就是原数组的值
            cout << query(x) << "\n";
        }
    }
    return 0;
}