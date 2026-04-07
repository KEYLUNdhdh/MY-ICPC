#include <bits/stdc++.h>
using namespace std;

// 假设 mod = 3，这意味着这是一个三元循环克制的世界：
// 0 (同类)：我们是朋友。
// 1 (吃)：我吃你（我比你强 1 级）。
// 2 (被吃)：你吃我（我比你强 2 级，或者说我比你弱 1 级，因为 2≡−1(mod3)）。
//从食物链角度看，A吃B，B吃C，导出C吃A，因为这个是三元循环克制所决定的事实，而我们的带权并查集就是在维护这个过程

// mod = 3，d[x] 到底存的是什么？
// 把并查集看作一棵树，d[x] 存的是 x 和它的父节点（上司）的关系。
// 我们可以把 d[x] 理解为 “地位差”：
// d[x] = 0: x 和爸爸是同类。、
// d[x] = 1: x 吃爸爸。
// d[x] = 2: x 被爸爸吃。
// 在食物链的条件下，0,1,2对应的关系是有严格讲究的

struct DSU
{
    vector<int> f, siz, d;
    int mod;//mod的大小代表有几种关系，敌人/朋友为2种关系，食物链有3种关系(天敌->此时被吃，同类->即不吃也不被吃，猎物->吃别人)

    DSU(int n,int mod_) : f(n + 1), siz(n + 1, 1), d(n + 1, 0), mod(mod_)
    {
        iota(f.begin(), f.end(), 0);
    }
    // 路径压缩 + 权值更新
    // find 函数里的路径压缩 d[x] = (d[x] + d[f[x]]) % 3 是在做什么？
    // 假设场景：
    // 你 (x) 吃 组长 (f[x])。 （你比组长强 1 级）
    // 组长 吃 老板 (root)。 （组长比老板强 1 级）
    // 当你直接向老板汇报时，你和老板的关系是什么？
    // 你 vs 老板=(你 vs 组长)+(组长 vs 老板)=1+1=2
    // 所以，你吃组长，组长吃老板 ⇒ 老板吃你。这就是向量累加的意义。
    int find(int x)
    {
        if (x != f[x])
        {
            int root = find(f[x]);// 递归找根
            d[x] = (d[x] + d[f[x]]) % mod;// 核心：累加路径权值
            f[x] = root;// 路径压缩
        }
        return f[x];
    }
    // 合并 x 和 y，关系为：x -> y 的权值为 v
    // 返回值：true 表示合并成功或者已经在一个集合中且该关系v是正确的，false 表示已经在一个集合且矛盾
    bool merge(int x,int y,int v)
    {
        int rootx = find(x);
        int rooty = find(y);
        if(rootx == rooty)
        {
            //如果x,y在同一集合，说明x,y的关系在之前已经确定
            //(x→y)=(x→root)−(y→root)
            //relation(x,y)=d[x]−d[y]
            // 验证矛盾：(d[x] - d[y]) % MOD 应该等于 v
            int check = (d[x] - d[y] + mod) % mod;
            return check == v;
        }
        // 按秩合并：把小树贴到大树上，可以略微减少递归深度
        if(siz[rootx] < siz[rooty])
        {
            swap(rootx, rooty);
            // 注意：交换了 x, y 的根，原本 x->y 是 v，现在 y->x 是 -v，即（mod - v) % mod
            v = (mod - v) % mod;
            swap(x, y);
        }
        // 将 rootY 接到 rootX 下面
        f[rooty] = rootx;
        siz[rootx] += siz[rooty];
        //虚线边： rooty→rootx。关系是 ?。
        //我们要计算从 rooty 走到 rootx 的“距离”。但是我们不能直接飞过去，我们得绕路走已知路径
        // 推导：想象成向量加法
        //val(x->rootX) + val(rootX->rootY) - val(y->rootY) = v
        //即d[x]          + d[rootY]          - d[y]          = v
        //      d[rootY] = v + d[y] - d[x]
        // 这里需要特别注意方向，根据上面的 swap，现在的方向是 x (大树那边) -> y (小树那边)
        // 我们要计算 d[rootY] (rootY 到 rootX 的距离)
        // 向量路径：rootY -> y -> x -> rootX
        // d[rootY] = -d[y] - v + d[x]
        // 即核心向量公式：d[rootY] = d[x] - d[y] - v (在模意义下)
        d[rooty] = (d[x] - d[y] - v + mod) % mod;
        return true;
    }
    //求x -> y
    int query(int x,int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if(rootx != rooty)
            return -1;
        return (d[x] - d[y] + mod) % mod;
    }
};