//Splay树（伸展树） 是一种自平衡二叉搜索树，它通过伸展操作将最近访问的节点旋转到树根，从而在均摊意义上保持高效。其核心思想是：每次对节点的访问（查找、插入、删除）都会引发一次从该节点到根的路径上的一系列旋转，使该节点成为新的根。这种“即用即调整”的策略使得经常访问的节点总是靠近根，后续操作更快。
// Splay树（伸展树）完全满足二叉搜索树（BST）
// 对于任意节点 p：
// 左子树中所有节点的值都 小于 p.val
// 右子树中所有节点的值都 大于 p.val

//应用场景
//维护 bst情况下，同时可以进行由有限的区间加法或者减法
//减法只减去左子树，加法只加右子树，保证bst性质
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Splay
{
    struct Node
    {
        int val, id, lazy, size;
        Node *ch[2];
        Node *parent;

        Node(int v, int idx = 0) : val(v), id(idx), lazy(0), size(1), ch{nullptr, nullptr}, parent(nullptr) {}
    };
    Node *root;

    Splay() : root(nullptr) {}
    ~Splay() { clear(root); }

    void clear(Node *t)
    {
        if(!t)
            return;
        clear(t->ch[0]);
        clear(t->ch[1]);
        delete t;
    }

    // ---------- 辅助函数 ----------
    //如果 t 是父节点的右儿子，表达式为 true，返回 1。
    //如果 t 是父节点的左儿子，表达式为 false，返回 0。
    int getpos(Node* t) const
    {
        return t->parent ? (t->parent->ch[1] == t) : 0;
    }
    //更新size用
    //在 Splay 树（或其他平衡树）中，每个节点通常存储以该节点为根的子树的大小（size）。这个信息对于实现按排名查询（如 kth）、求排名（rank）等操作是必不可少的
    void pushup(Node* t)
    {
        if(!t)
            return;
        t->size = 1;
        if(t->ch[0])
            t->size += t->ch[0]->size;
        if(t->ch[1])
            t->size += t->ch[1]->size;
    }
    //执行加法
    void applytag(Node *t, int v)
    {
        if(!t)
            return;
        t->val += v;
        t->lazy += v;
    }
    //下放tag   
    void pushdown(Node *t)
    {
        if(!t || t->lazy == 0)
            return;
        if(t->ch[0])
            applytag(t->ch[0], t->lazy);
        if(t->ch[1])
            applytag(t->ch[1], t->lazy);
        t->lazy = 0;
    }
    // ---------- 旋转与伸展 ----------
    //交换t和t->parent 将t往上移
    void rotate(Node *t)
    {
        Node *q = t->parent;
        int x = !getpos(t);// 如果 t 是左儿子 (getpos=0)，则 x=1，右旋；如果 t 是右儿子 (getpos=1)，则 x=0，左旋
        q->ch[!x] = t->ch[x];
        if(t->ch[x])
            t->ch[x]->parent = q;
        t->parent = q->parent;
        if(q->parent)
            q->parent->ch[getpos(q)] = t;
        t->ch[x] = q;
        q->parent = t;
        pushup(q);
        pushup(t);
    }
    //伸展 (splay)：将指定节点通过旋转提升到根，沿途下传懒标记。
    void splay(Node *t)
    {
        // 第一部分：收集祖先并下传懒标记
        //Splay 树支持区间修改时，常会使用懒标记。当一个节点带有懒标记时，其子树内的所有节点值都需要加上某个偏移量，但在实际访问子节点之前，标记不会下传。旋转操作会改变父子关系，如果旋转时某个祖先节点还挂着懒标记，那么它的子节点（即将被旋转上来的节点）可能处于不正确状态。因此，在旋转前必须确保从根到目标节点 t 的路径上的所有节点的懒标记都已下传。
        vector<Node *> stk;
        for (Node *i = t; i->parent; i = i->parent)
            stk.push_back(i->parent);
        while(!stk.empty())
        {
            pushdown(stk.back());
            stk.pop_back();
        }
        pushdown(t);
        // 第二部分：双层旋转（zig-zig 和 zig-zag）
        //1.父节点是根（!t->parent->parent）：此时只需一次单旋转，直接执行 rotate(t) 即可。
        //2.父节点不是根（存在祖父节点）：
        // 判断 t 和其父节点相对于祖父节点的方位是否相同（即 getpos(t) == getpos(t->parent)）。
        // 相同方位（例如 t 是左儿子，其父也是左儿子，形成一条直线）：这种情况称为 zig-zig。此时先旋转父节点 t->parent，再旋转 t。这样做的目的是使树更平衡，将这条长路径“折叠”起来，减少树的深度。自己模拟一下就能发现树的深度变小了
        // 不同方位（例如 t 是左儿子，其父是右儿子，形成折线）：这种情况称为 zig-zag。此时先旋转 t 自身，再旋转 t（实际上第二次旋转会处理父节点，因为旋转后 t 上升了一层，循环继续）。让树的高度有效降低。
        while(t->parent)//只要 t 还不是根，就继续旋转。
        {
            if(t->parent->parent)
            {
                if(getpos(t) == getpos(t->parent))
                    rotate(t->parent);
                else
                    rotate(t);
            }
            rotate(t);
        }
        root = t;
    }

    // ---------- 分裂与合并 ----------
    //分裂（split）：以值 x 为界，将树分成 < x 和 >= x 两部分
    //pair第一个元素是左子树的根（值 < x），第二个元素是右子树的根（值 ≥ x）
    pair<Node*, Node*> split(Node *t, int x)
    {
        if(!t)
            return {nullptr, nullptr};
        //寻找第一个 ≥ x 的节点
        Node *v = nullptr;
        Node *j = t;
        for (Node *i = t; i; )
        {
            pushdown(i); // 下传懒标记，确保当前值正确
            j = i;// 记录最后访问的节点
            if(i->val >= x)
            {
                v = i;// 记录第一个遇到的 ≥ x 的节点
                i = i->ch[0]; // 继续向左，寻找更小的 ≥ x 的节点
            }
            else
            {
                i = i->ch[1]; // 向右，因为当前值 < x，要找 ≥ x 只能向右
            }
        }
        //循环结束后，v 要么指向第一个 ≥ x 的节点，要么为 nullptr（说明所有节点都 < x）。
        //伸展最后访问的节点 j，为后续可能的分裂做准备。即使没有找到 v，将 j 伸展后，整棵树以 j 为根，方便直接返回。
        splay(j);
        if(!v)//如果没找到
            return {j, nullptr};
        splay(v);//找到了，以v为根，由于 v 是第一个 ≥ x 的节点，它的左子树中所有节点必然 < x（BST 性质），而右子树中所有节点都 ≥ v.val ≥ x。
        Node *u = v->ch[0];//将 v 的左孩子 u 取出，这就是我们需要的左子树（所有 < x 的节点）
        if(u)
        {
            v->ch[0] = u->parent = nullptr;//断开 u 与 v 的连接
            pushup(v);//更新子树大小
        }
        return {u, v};
    }
    //合并（merge）：要求输入的左树的最大值 < 右树的最小值，否则合并后的树会破坏 BST 结构。
    Node* merge(Node *l,Node *r)
    {
        //特判
        if(!l)
            return r;
        if(!r)
            return l;
        Node *i = l;
        while(i->ch[1])
            i = i->ch[1];
        Node *ck = r;
        while(ck->ch[0])
            ck = ck->ch[0];
        assert(i->val < ck->val && "Merge precondition violated: left max >= right min");
        //如果assert后没问题，我们提升i为根节点，保证了i的左子树所有节点均小于i->val，且i的右子树为空，这时候我们直接链接就行
        splay(i);
        i->ch[1] = r;
        r->parent = i;
        pushup(i);
        return i;//返回合并后的根节点
    }

    // ---------- 基本操作 ----------
    //插入
    void insert(int val, int id = 0)
    {
        Node *x = new Node(val, id);
        if(!root)
        {
            root = x;
            return;
        }
        auto [L, R] = split(root, val);
        root = merge(merge(L, x), R);
    }
    //全部清除
    void eraseAll(int val)
    {
        if(!root)
            return;
        auto [L, MR] = split(root, val);
        //M这里存储的是节点值全是val的树
        auto [M, R] = split(MR, val + 1);
        if(M)
            clear(M);
        root = merge(L, R);
    }
    //只删除一个
    void eraseSingle(int val)
    {
        if(!root)
            return;
        auto [L, MR] = split(root, val);
        auto [M, R] = split(MR, val + 1);
        if(M)
        {
            //我们就把M的根节点删掉就行
            Node *v = M;
            Node *l = v->ch[0];
            Node *r = v->ch[1];
            if(l)
                l->parent = nullptr;
            if(r)
                r->parent = nullptr;
            delete v;
            M = merge(l, r);
        }
        root = merge(merge(L, M), R);
    }
    //查找某个数是否存在
    bool find(int val)
    {
        auto [L, R] = split(root, val);
        bool ok = false;
        if(R && R->val == val)
            ok = true;
        root = merge(L, R);
        return ok;
    }
    //查询一个数从小往大排为第几个
    int rank(int val)
    {
        auto [L, R] = split(root, val);
        int res = (L ? L->size : 0) + 1;
        root = merge(L, R);
        return res;
    }
    //查询第k小的数
    int kth(int k)
    {
        assert(root && k >= 1 && k <= root->size);
        Node *t = root;//从根节点开始
        while(t)
        {
            pushdown(t);//先调用 pushdown(t) 下传懒标记，保证左右子树的 size 和节点值准确。
            int lsz = t->ch[0] ? t->ch[0]->size : 0;//获取左子树大小
            if(k <= lsz)
                t = t->ch[0];//说明此时到左子树去找
            else if(k == lsz + 1)//说明当前节点 t 就是第 k 小的节点。
            {
                splay(t);//此时调用 splay(t) 将其伸展到根（优化后续操作）让访问次数较多的元素位于离根更近的位置，优化速度
                return t->val;
            }
            else//在右子树，相应的去找就行
            {
                k -= lsz + 1;
                t = t->ch[1];
            }
        }
        return -1;//一般不可能在这里return，while循环里就return完了
    }
    //返回整个树的大小
    int size() const
    {
        return root ? root->size : 0;
    }
    // //区间加法
    // //这里l ，r代表的是真实数值，不是下标
    // void rangeAdd(int l, int r, int delta)
    // {
    //     if(l > r)
    //         return;
    //     auto [L, MR] = split(root, l);
    //     auto [M, R] = split(MR, r + 1);
    //     if(M)
    //         applytag(M, delta);//将 M 根节点的值增加 delta（t->val += delta）。并将 M 根节点的懒标记累加 delta（t->lazy += delta）。
    //     root = merge(merge(L, M), R);//复原
    // }
    //做中序遍历
    void inOrder(Node *t, vector<int> &out)
    {
        if(!t)
            return;
        pushdown(t);
        inOrder(t->ch[0], out);
        out.push_back(t->val);
        inOrder(t->ch[1], out);
    }
    //对所有> x的执行add操作
    // >= x的情况自己微调
    void add(int x, int addval)
    {
        auto [L, MR] = split(root, x);
        auto [M, R] = split(MR, x + 1);
        if(R)
            applytag(R, x);
        
        root = merge(merge(L, M), R);
    }
    //这个是special Add,在一组数插入之前就执行add，add 那些>=x的树完再插入
    void spe(int x, int id)
    {
        auto [L, R] = split(root, x);
        if(R)
            applytag(R, x);
        Node *node = new Node(x, id);
        Node *Lnode = merge(L, node);
        root = merge(Lnode, R);

        splay(node);
    }
    //对所有< x的执行minus操作
    void minus(int x,int mival)
    {
        auto [L, R] = split(root, x);
        if(L)
            applytag(L, -mival);        
        root = merge(L, R);
    }
    void print()
    {
        vector<int> vals;
        inOrder(root, vals);
        for(int v : vals)
            cout << v << " ";
        cout << "\n";
    }

    void debugPrint()
    {
        vector<int> vals;
        inOrder(root, vals);
        for(int v : vals)
            cerr << v << " ";
        cerr << "\n";
    }
};

// int main() {
//     Splay sp;
//     sp.insert(5);
//     sp.insert(3);
//     sp.insert(8);
//     sp.insert(1);
//     sp.print();                 // 应输出 1 3 5 8
//     sp.rangeAdd(3, 8, 10);      // 对值在[3,8]的节点加10
//     sp.print();                 // 应输出 1 13 15 18
//     sp.eraseAll(13);
//     sp.print();                 // 应输出 1 15 18
//     cout << sp.kth(2) << '\n';  // 应输出 15
//     return 0;
// }