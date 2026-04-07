#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
typedef pair<int, int> pii;
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
    int getpos(Node* t) const
    {
        return t->parent ? (t->parent->ch[1] == t) : 0;
    }
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
    void applytag(Node *t, int v)
    {
        if(!t)
            return;
        t->val += v;
        t->lazy += v;
    }
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
    void rotate(Node *t)
    {
        Node *q = t->parent;
        int x = !getpos(t);
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
    void splay(Node *t)
    {
        vector<Node *> stk;
        for (Node *i = t; i->parent; i = i->parent)
            stk.push_back(i->parent);
        while(!stk.empty())
        {
            pushdown(stk.back());
            stk.pop_back();
        }
        pushdown(t);

        while(t->parent)
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
    pair<Node*, Node*> split(Node *t, int x)
    {
        if(!t)
            return {nullptr, nullptr};
        Node *v = nullptr;
        Node *j = t;
        for (Node *i = t; i; )
        {
            pushdown(i);
            j = i;
            if(i->val >= x)
            {
                v = i;
                i = i->ch[0];
            }
            else
            {
                i = i->ch[1];
            }
        }
        splay(j);
        if(!v)
            return {j, nullptr};
        splay(v);
        Node *u = v->ch[0];
        if(u)
        {
            v->ch[0] = u->parent = nullptr;
            pushup(v);
        }
        return {u, v};
    }

    Node* merge(Node *l,Node *r)
    {
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
        splay(i);
        i->ch[1] = r;
        r->parent = i;
        pushup(i);
        return i;
    }

    // ---------- 基本操作 ----------
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

    void eraseAll(int val)
    {
        if(!root)
            return;
        auto [L, MR] = split(root, val);
        auto [M, R] = split(MR, val + 1);
        if(M)
            clear(M);
        root = merge(L, R);
    }

    void eraseSingle(int val)
    {
        if(!root)
            return;
        auto [L, MR] = split(root, val);
        auto [M, R] = split(MR, val + 1);
        if(M)
        {
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

    bool find(int val)
    {
        auto [L, R] = split(root, val);
        bool ok = false;
        if(R && R->val == val)
            ok = true;
        root = merge(L, R);
        return ok;
    }

    int rank(int val)
    {
        auto [L, R] = split(root, val);
        int res = (L ? L->size : 0) + 1;
        root = merge(L, R);
        return res;
    }
    
    int kth(int k)
    {
        assert(root && k >= 1 && k <= root->size);
        Node *t = root;
        while(t)
        {
            pushdown(t);
            int lsz = t->ch[0] ? t->ch[0]->size : 0;
            if(k <= lsz)
                t = t->ch[0];
            else if(k == lsz + 1)
            {
                splay(t);
                return t->val;
            }
            else
            {
                k -= lsz + 1;
                t = t->ch[1];
            }
        }
        return -1;
    }

    int size() const
    {
        return root ? root->size : 0;
    }

    void inOrder(Node *t, vector<pii> &out)
    {
        if(!t)
            return;
        pushdown(t);
        inOrder(t->ch[0], out);
        out.push_back({t->val, t->id});
        inOrder(t->ch[1], out);
    }
    //对所有> x的执行add操作
    // >= x的情况自己微调
    void add(int x, int addval)
    {
        auto [L, MR] = split(root, x);
        auto [M, R] = split(MR, x + 1);
        if(R)
            applytag(R, addval);
        
        root = merge(merge(L, M), R);
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
        vector<pii> vals;
        inOrder(root, vals);
        for(auto v : vals)
            cout << v.first << " ";
        cout << "\n";
    }

    void debugPrint()
    {
        vector<pii> vals;
        inOrder(root, vals);
        for(auto v : vals)
            cerr << v.first << " ";
        cerr << "\n";
    }
};

int main() {
    Splay sp;
    sp.insert(5);
    sp.insert(3);
    sp.insert(8);
    sp.insert(1);
    sp.print();                 // 应输出 1 3 5 8      
    sp.print();                 // 应输出 1 13 15 18
    sp.eraseAll(13);
    sp.print();                 // 应输出 1 15 18
    cout << sp.kth(2) << '\n';  // 应输出 15
    return 0;
}