#include <bits/stdc++.h>
#define lyc_fan_club main
#define int long long
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \ 
}
#define cutline {cerr << "----------------------\n";}

using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) // PII 
{
    return os << "(" << p.first << ", " << p.second << ")\n";
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) //vector
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v) //set
{
    os << "[";
    for (auto x = v.begin(); x != v.end(); x++)
    {
        if (x != v.begin())
            os << ", ";
        os << *x;
    }
    return os << "]\n";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &v) //map
{
    os << " {";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << "(" << it->first << " -> " << it->second << ")"; //键值对
    }
    return os << "}\n";
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
constexpr int MOD = 998244353, INF = 1e9 + 7;

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


void solve()
{
    int n;
    cin >> n;
    Splay sp;
    vector<int> a(n);
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        sp.spe(a[i], i);
    }
    vector<pii> ans;
    sp.inOrder(sp.root, ans);
    sort(ans.begin(), ans.end(), [](pii p, pii q)
         { return p.second < q.second; });
    for (int i = 0; i < n; i++)
    {
        cout << ans[i].first << " ";
    }
    cout << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}