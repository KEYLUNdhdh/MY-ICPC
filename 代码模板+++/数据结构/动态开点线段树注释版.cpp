#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct dynamicSegmentTree
{
    i64 maxVal, offsetValue, rootNode;
    //sum:该值域区间内存在的数字总数
    // ls, rs左右子节点的数组下标指针
    vector<i64> ls, rs, sum;
    // 构造函数：初始化常量和 0 号空节点
    dynamicSegmentTree(i64 maxVal_= 2e7 + 5, i64 offset = 1e7 + 1)
    {
        maxVal = maxVal_;
        offset = offsetValue;
        rootNode = 0;

        // 0 号索引作为超级空节点 (Null Node) 保留
        ls.assign(1, 0);
        rs.assign(1, 0);
        sum.assign(1, 0);
    }
    // 内部方法：动态分配新节点
    i64 newNode()
    {
        ls.push_back(0);
        rs.push_back(0);
        sum.push_back(0);
        return ls.size() - 1;
    }
    // 内部方法：核心递归更新
    void update(i64 &u, int l, int r, i64 val, i64 cnt)
    {
        if(!u)
            u = newNode();// 如果当前节点不存在，现场开辟
        sum[u] += cnt;// 路径上的区间总数加上变动量 (插入传 1，删除传 -1)
        if(l == r)// 递归到底，锁定具体数值
            return;
        int m = l + r >> 1;
        if(val <= m)
            update(ls[u], l, m, val, cnt);
        else
            update(rs[u], m + 1, r, val, cnt);
    }
    // 核心 2：查询严格小于 val 的数字个数，再 +1 得到排名
    i64 getRnk(i64 u, int l, int r, i64 val)
    {
        if(!u)// 如果走到了空节点，说明没有更小的了
            return 1;
        if(l == r)
            return 1;
        int m = l + r >> 1;
        if(val <= m)
            return getRnk(ls[u], l, m, val);
        else
            return sum[ls[u]] + getRnk(rs[u], m + 1, r, val);// 如果向右走，说明左子树的所有数都严格小于 val，直接累加左子树的 sum
    }
    // 核心 3：通过二分查找排名第 k 的数值
    i64 getKth(i64 u, int l, int r, i64 k)
    {
        if(l == r)// 找到了具体的数值
            return l;
        int m = l + r >> 1;
        int lc = sum[ls[u]];
        if(k <= lc)// 左子树的数量够 k 个，答案一定在左边
            return getKth(ls[u], l, m, k);
        else// 左子树数量不够，去右子树找第 (k - left_cnt) 个
            return getKth(rs[u], m + 1, r, k - lc);
    }

    void insert(i64 x)
    {
        update(rootNode, 1, maxVal, x + offsetValue, 1);
    }

    void remove(i64 x)
    {
        update(rootNode, 1, maxVal, x + offsetValue, -1);
    }

    i64 rank(i64 x)
    {
        return getRnk(rootNode, 1, maxVal, x + offsetValue);
    }

    i64 kth(i64 x)
    {
        return getKth(rootNode, 1, maxVal, x) -  offsetValue;
    }

    i64 prev(i64 x)
    {
        return (kth(rank(x) - 1));
    }

    i64 nxt(i64 x)
    {
        return (kth(rank(x + 1)));
    }
};