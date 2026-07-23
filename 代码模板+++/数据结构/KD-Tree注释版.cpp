#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using ld = long double;

// 直接硬编码提速
static constexpr int MAXK = 5;
struct Point
{
    array<i64, MAXK> x{};
    i64 v = 0;
};


struct KDTree
{
    struct Node
    {
        int ls = 0, rs = 0;
        // minn[i] 代表子树内所有第 i 维坐标的最小值
        array<i64, MAXK> minn{}, maxx{};// 空间的“左下角”和“右上角”（包围盒边界）
        Point p{};// 这个节点实际存放的那个点（坐标和权值）
        i64 sum = 0, lazy = 0; // 整个的权值总和，也就是划定的空间里面权重的总和，以及用来批量修改的懒标记
        int sz = 0;// 以这个节点为根的子树里一共包含了多少个实体点
    };

    int k;
    int root;
    ld alpha;
    vector<Node> tr;
    vector<int> flatNodes;

    KDTree(int k_, int reserveSize = 2e5) : k(k_), root(0), alpha(0.75)
    {
        assert(k >= 1 && k <= MAXK);
        tr.reserve(reserveSize + 1);
        tr.emplace_back();// 空节点
        flatNodes.reserve(reserveSize);
    }

    int newNode(const Point &p)
    {
        int u = tr.size();
        tr.emplace_back();
        tr[u].p = p;
        tr[u].maxx = tr[u].minn = p.x;
        tr[u].sum = p.v;
        tr[u].sz = 1;
        return u;
    }

    // 更新父节点信息
    void pushUp(int u)
    {
        int l = tr[u].ls, r = tr[u].rs;
        tr[u].sz = tr[l].sz + tr[r].sz + 1;// 算上自己
        tr[u].sum = tr[l].sum + tr[r].sum + tr[u].p.v; // 算上自己

        for (int i = 0; i < k;i++)
        {
            tr[u].minn[i] = tr[u].maxx[i] = tr[u].p.x[i];
            // 根据子树信息更新空间上覆盖范围
            if(l)
            {
                tr[u].minn[i] = min(tr[u].minn[i], tr[l].minn[i]);
                tr[u].maxx[i] = max(tr[u].maxx[i], tr[l].maxx[i]);

            }
            if(r)
            {
                tr[u].minn[i] = min(tr[u].minn[i], tr[r].minn[i]);
                tr[u].maxx[i] = max(tr[u].maxx[i], tr[r].maxx[i]);
            }
        }
    }

    // 修改信息，+v
    void apply(int u, i64 v)
    {
        if(!u)
            return;
        
        tr[u].p.v += v;
        tr[u].sum += v * tr[u].sz;
        tr[u].lazy += v;
    }

    // 下传懒标记
    void pushDown(int u)
    {
        if(tr[u].lazy)
        {
            apply(tr[u].ls, tr[u].lazy);
            apply(tr[u].rs, tr[u].lazy);
            tr[u].lazy = 0;
        }
    }

    // 在失衡的时候，重新对 u 的子树进行建树操作
    void flatten(int u)
    {
        if(!u)
            return;

        // 重构前必须把所有懒标记全部下传。
        // 因为重构之后，节点的父子关系会改变。
        pushDown(u);

        // 把当前子树所有节点放入 flatten 当中
        // 这里使用的是中序遍历，但实际上只要每个节点恰好放一次即可，不要求必须中序
        flatten(tr[u].ls);
        flatNodes.push_back(u);
        flatten(tr[u].rs);
    }

    // 建树过程
    int build(int l, int r, int dim)
    {
        if(l > r)
            return 0;

        int m = l + r >> 1;// 找中间位置

        // 核心：nth_element。把它当成一个“快速选择”的函数。
        // 它能保证在第 dim 维上，m 左边的点都比它小，右边的都比它大。
        // 它能在 O(N) 时间内把第 m 小的元素放在 m 的位置上，并且保证左边比它小，右边比它大。
        nth_element(flatNodes.begin() + l, flatNodes.begin() + m, flatNodes.begin() + r + 1, [&](int a, int b) { return tr[a].p.x[dim] < tr[b].p.x[dim]; });

        int u = flatNodes[m];// 选出中位数所在的点作为根
        tr[u].ls = build(l, m - 1, (dim + 1) % k);// 左边去左子树，维度轮换
        tr[u].rs = build(m + 1, r, (dim + 1) % k);// 右边去右子树，维度轮换
        pushUp(u);
        return u;
    }

    // 判断当前子树是否平衡，不平衡要重新建树
    void checkRebuild(int &u, int dim)
    {
        // alpha 通常等于 0.75。意思是：如果你有一个儿子的体积占了你整个家族的 75% 以上，说明失衡了！
        if(tr[tr[u].ls].sz > alpha * tr[u].sz || tr[tr[u].rs].sz > alpha * tr[u].sz)
        {
            flatNodes.clear();
            flatten(u);// 暴力把这棵子树拍扁（提取出所有节点）
            u = build(0, flatNodes.size() - 1, dim);// 用刚刚的 build 函数重新建一棵完美平衡的子树
        }
    }

    void _insert(int &u, const Point &p, int dim)
    {
        // 为空就新建
        if(!u)
        {
            u = newNode(p);
            return;
        }

        // 下传是为了防止新节点错误继承之前的区间加法信息
        pushDown(u);

        // 小于去左边
        if(p.x[dim] <= tr[u].p.x[dim])
        {
            // 为什么要拷贝一份？
            // 因为插入时新建节点可能导致 tr 这个 vector 的地址发生改变，发生野指针错误
            int ls = tr[u].ls;
            _insert(ls, p, (dim + 1) % k);
            tr[u].ls = ls;
        }
        else// 大于去右边
        {
            int rs = tr[u].rs;
            _insert(rs, p, (dim + 1) % k);
            tr[u].rs = rs;
        }
        // 更新父节点
        pushUp(u);
        // 插入后检查是否失衡，失衡要重建子树
        checkRebuild(u, dim);
    }

    // 盘点点是否在查询举行内
    // forall i, A_i <=  p_i <=  B_i
    bool isPointInside(const Point &p, const Point &A, const Point &B)
    {
        for (int i = 0; i < k;i++)
            if(p.x[i] < A.x[i] || p.x[i] > B.x[i])
                return false;

        return true;
    }

    // 子树的包围盒与 A，B 对应的查询矩形之间的关系
    // -1：不相交
    //  0：部分相交
    //  1：完全包含
    int relation(int u, const Point &A, const Point &B) const
    {
        bool inside = true;

        for(int i = 0; i < k; i++)
        {
            // 如果某个维度在区间外，那就是不相交
            if(tr[u].maxx[i] < A.x[i] || tr[u].minn[i] > B.x[i])
                return -1;

            // 判断能不能完全包含
            if(tr[u].minn[i] < A.x[i] || tr[u].maxx[i] > B.x[i])
                inside = false;
        }

        return inside ? 1 : 0;
    }

    // 修改
    void _modify(int u, const Point &A, const Point &B, i64 v)
    {
        // 为空不修改
        if(!u)
            return;

        // 获取关系
        int rel = relation(u, A, B);

        // 不相交就不修改
        if(rel == -1)
            return;

        // 完全包含直接修改
        if(rel == 1)
        {
            apply(u, v);
            return;
        }

        // 不完全包含要递归修改
        // 先下传信息，因为要访问子树的真实信息
        pushDown(u);

        // 先看看是否要修改 u 节点上的信息
        if(isPointInside(tr[u].p, A, B))
            tr[u].p.v += v;

        // 递归处理
        _modify(tr[u].ls, A, B, v);
        _modify(tr[u].rs, A, B, v);
        // 更新父亲
        pushUp(u);
    }

    // 区间查询权重
    i64 _query(int u, const Point &A, const Point &B)
    {

        // 没有就空
        if(!u)
            return 0;

        int rel = relation(u, A, B);

        // 不相交，没贡献
        if(rel == -1)
            return 0;

        // 完全包含，全部算上=。
        if(rel == 1)
            return tr[u].sum;

        // 部分包含，查询子树。
        pushDown(u);
        i64 res = 0;
        
        // 别忘了先加上 u 这个子树根节点的信息
        if(isPointInside(tr[u].p, A, B))
            res += tr[u].p.v;

        res += _query(tr[u].ls, A, B);
        res += _query(tr[u].rs, A, B);
        return res;
    }

    void insert(const Point &p) { _insert(root, p, 0); }
    void modify(const Point &A, const Point &B, i64 v) { _modify(root, A, B, v); }
    i64 query(const Point &A, const Point &B) { return _query(root, A, B); }
};