//使用单点修改加上区间查询，所以这个树没有懒标记
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<class Info>
struct SegmentTree
{
    int n;
    vector<Info> info;
    SegmentTree() : n{0} {}
    //直接指定大小和默认值
    //用途：当你只知道数组有多长，但还没准备好具体数据时使用。
    //逻辑：它接收长度 n_ 和一个可选的初始值 v_（如果不传，就用 Info 的默认构造函数）。它直接调用 init(n_, v_)。
    SegmentTree(int n_,Info v_ = Info())
    {
        init(n_, v_);
    }
    //从一个现成的数组（Vector）创建
    //用途：这是最常用的方式。如果你已经有一个装满数据的 vector，直接传进来，线段树会自动根据这个 vector 的内容建树。
    //模板参数 T：这里用了模板，意味着你的原始数据不一定要是 Info 类型。比如原始数据是 int，线段树会自动把它们转化成 Info 存储（前提是 Info 支持从 int 转化）。
    template<class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }
    //“桥梁”函数
    //它创建了一个临时 vector，里面装了 n_ 个 v_，然后交给最核心的 init(vector<T> init_) 函数去处理。
    void init(int n_,Info v_ = Info())
    {
        //类模板参数推导
        //即vector<Info>(n_,v_)
        init(vector(n_, v_));
    }
    template<class T>
    //**init start from 0-index**
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 * n + 1, Info());
        //这行 function<void(int, int, int)> build = ... 的作用是给这个匿名函数起个名字，并允许它递归。
        //为什么不直接用 auto？ 在 C++ 中，如果你写 auto build = [&](...){ build(...); };，编译器会报错。因为在定义 build 的时候，它还没定义完，内部没法调用自己。 使用 std::function 明确了函数的签名（返回 void，接受三个 int），所以它支持递归调用。
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if(r == l)  
            {
                info[p] = init_[l - 1];
                return;
            }
            int m = l + (r - l) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            //子节点build完别忘了更新父节点
            pull(p);
        };
        build(1, 1, n);
    }
    //向上更新
    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    //找到数组中下标为 x 的那个元素，把它更新为新的值 v，并同步更新所有包含这个位置的区间信息。
    //单点修改：不需要懒标记。因为你只改一个点，直接改到最底层再一路传上来即可。
    void modify(int p,int l,int r,int x,const Info &v)
    {
        if(r == l)
        {
            info[p] = v;
            return;
        }
        int m = l + (r - l) / 2;
        if(x <= m)
        {
            modify(2 * p, l, m, x, v);
        }
        else
        {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int p,const Info &v)
    {
        modify(1, 1, n, p, v);
    }
    Info rangeQuery(int p,int l,int r,int x,int y)
    {
        //如果返回Info(）默认构造，必须满足Info x + Info()后仍为x
        if(l > y || r < x)
            return Info();
        if(l >= x && r <= y)
            return info[p];
        int m = l + (r - l) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    Info rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }
    template<class F>
    //F 是模板参数，代表一个函数对象（Functor）、函数指针或 Lambda 表达式。pred 是 Predicate（谓词） 的缩写。
    //所以这里的pred实际上是一个函数指针，并且返回的是bool类型的
    //!pred(info[p])这是最聪明的地方。如果当前整个区间的信息都不满足条件，那么这个区间的任何子节点也一定不满足，直接回头，不用再往下搜了。
    int findFirst(int p,int l,int r ,int x,int y,F pred)
    {
        if(l > y || r < x || !pred(info[p]))
            return -1;
        //如果已经递归到了叶子节点，且通过了上面的 pred 检查，说明这个位置就是我们要找的。
        if(r == l)
        {
            return l;
        }
        int m = l + (r - l) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);//因为要找first 先看左子树
        if(res == -1)// 如果左子树没找到，才去看右子树
            res = findFirst(2 * p + 1, m + 1, r, x, y, pred);
        return res;
    }
    template<class F>
    int findFirst(int x,int y,F pred)
    {
        return findFirst(1, 1, n, x, y, pred);
    }
    template<class F>
    //同findfirst
    int findLast(int p,int l,int r,int x,int y,F pred)
    {
        if(l > y || r < x || !pred(info[p]))
            return -1;
        if(r == l)
            return l;
        int m = l + (r - l) / 2;
        int res = findLast(2 * p + 1, m + 1, r, x, y, pred);
        if (res == -1)
            res = findLast(2 * p, l, m, x, y, pred);
        return res;
    }
    template<class F>
    int findLast(int x,int y,F pred)
    {
        return findLast(1, 1, n, x, y, pred);
    }
};
//Info could be modified according to the subject
struct Info
{
    //....
};

//Info operator+(Info a,Info b)...
//Info operator-....