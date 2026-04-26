#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;

// 应用场景
//动态维护一次函数的最值： 给定平面上的若干条线段（或直线），随时查询在某一个指定的横坐标 x 处，哪条线段的 y 值最大（或最小）。
//斜率优化 DP（Convex Hull Trick）： 当 DP 转移方程可以化简为 y=kx+b 的形式，且斜率 k 和查询的 x 都不单调时，如果用单调队列会非常繁琐（甚至需要用到平衡树）。此时，李超线段树可以直接把直线插入进去，无视非单调的限制，用极低的心智负担解决复杂的斜率优化问题。

// 线段结构体
struct Line
{
    db k, b;
    int id;
};
// 线段树的每一个节点代表一个横坐标区间 [l, r]，该节点上记录的，是在该区间的中点 mid 处，取值最大（或最小）的那条线段的编号。这种设计巧妙地规避了不同直线互相交叉导致无法用常规懒标记维护的问题。
struct LiChaoTree
{
    int n;
    vector<int> tree;// tree[p] 存的是覆盖区间 p 中点处 y 值最大的线段编号
    vector<Line> lines;
    //注意：传入的n代表当前的x轴上的值域范围，开小了会RE
    LiChaoTree(int n_) : n(n_), tree(4 * n_ + 1, 0), lines(1, {0, 0, 0}) {}

    // 计算线段 id 在横坐标 x 处的 y 值
    db calc(int id, int x)
    {
        if(!id)
            return 0;
        return lines[id].k * x + lines[id].b;
    }
    // 浮点数比较函数，处理精度误差
    int cmp(db x, db y)
    {
        const db EPS = 1e-9;
        if(x - y > EPS)
            return 1;
        if(y - x > EPS)
            return -1;
        return 0;
    }
    // 外部调用：添加一条两端点为 (x0, y0) 到 (x1, y1) 的线段，编号为 id
    void addLine(int x0, int y0, int x1, int y1, int id)
    {
        if(x0 > x1)
        {
            swap(x0, x1);
            swap(y0, y1);
        }

        db k, b;
        if(x0 == x1)
        {
            k = 0;
            b = max(y0, y1);
        }
        else
        {
            k = 1. * (y1 - y0) / (x1 - x0);
            b = y0 - k * x0;
        }
        lines.push_back({k, b, id});
        insert(1, 1, n, x0, x1, id);//准备在区间x0到x1插入我们的线段
    }
    // 内部函数：线段树区间插入
    void insert(int p, int l, int r,int x, int y, int u)//u指的是id
    {
        if(x <= l && r <= y)
        {
            int &v = tree[p];
            int m = l + r >> 1;
            // 如果该区间目前没有优势线段，直接上位
            if(!v)
            {
                v = u;
                return;
            }

            // 比较新线段 u 和老线段 v 在中点的值
            int fm = cmp(calc(u, m), calc(v, m));
            // 如果 u 在中点更优，或者值一样但 u 的编号更小，u 取代 v 成为此区间的霸主
            if(fm == 1 || (fm == 0 && u < v))
            {
                swap(u, v);
            }
            //交换完后， 此时 v 一定是中点更优的线段，u 是被淘汰的“败者”
            // 如果区间不能再分，或者败者为空，直接结束
            if(l == r || !u)
                return;
            
            // 败者 u 虽然在中点比不过 v，但在区间的左半边或右半边可能仍有机会
            int fl = cmp(calc(u, l), calc(v, l));
            if(fl == 1 || (fl == 0 && u < v))
                insert(p << 1, l, m, x, y, u);// u 在左端点比 v 高，说明它们的交点在左半边，把 u 丢给左儿子继续竞争
            else
                insert(p << 1 | 1, m + 1, r, x, y, u);// 否则交点必定在右半边，丢给右儿子
            return;
        }
        // 常规的线段树找区间逻辑
        int m = l + r >> 1;
        if(x <= m)
            insert(p << 1, l, m, x, y, u);
        if(y >= m + 1)
            insert(p << 1 | 1, m + 1, r, x, y, u);
    }
    // 内部函数：单点查询
    int query(int p, int l, int r, int x)
    {
        if(l == r)
            return tree[p];

        int m = l + r >> 1;
        int ans = tree[p];// 沿途记录当前遇到的最强线段
        int sub = 0;

        // 往下递归走到叶子节点
        if(x <= m)
            sub = query(p << 1, l, m, x);
        else
            sub = query(p << 1 | 1, m + 1, r, x);

        if(!ans)
            return sub;
        if(!sub)
            return ans;

        // 比较本层节点记录的线段，和子树返回的线段，谁在 x 处更优
        int flag = cmp(calc(ans, x), calc(sub, x));
        if(flag == -1 || (flag == 0 && sub < ans))
            return sub;
        return ans;
    }

    int query(int x)
    {
        return query(1, 1, n, x);
    }
};
