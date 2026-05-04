#include <bits/stdc++.h>
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
using db = double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937 rnd(time(0));

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr int MOD = 998244353, INF = 1e9;

#include <bits/stdc++.h>
using namespace std;

struct Node 
{
    int id;      
    int size;    
    Node *ch[2];
    Node *parent;
    Node(int _id) : id(_id), size(1), ch{nullptr, nullptr}, parent(nullptr) {}
};

struct SplaySeq 
{

    

    Node *root;
    vector<Node*> pos; 

    SplaySeq(int n) : root(nullptr) 
    {
        pos.resize(n + 2, nullptr); 
    }

    int getpos(Node* t) 
    { 
        return t->parent ? (t->parent->ch[1] == t) : 0; 
    }
    
    void pushup(Node* t) 
    {
        if (!t) 
            return;
        t->size = 1;
        if (t->ch[0]) t->size += t->ch[0]->size;
        if (t->ch[1]) t->size += t->ch[1]->size;
    }

    void rotate(Node *t) 
    {
        Node *q = t->parent;
        int x = !getpos(t);
        q->ch[!x] = t->ch[x];
        if (t->ch[x]) 
            t->ch[x]->parent = q;
        t->parent = q->parent;
        if (q->parent) 
            q->parent->ch[getpos(q)] = t;
        t->ch[x] = q;
        q->parent = t;
        pushup(q);
        pushup(t);
    }

    
    void splay(Node *t, Node *goal = nullptr) 
    {
        while (t->parent != goal) 
        {
            Node *p = t->parent;
            if (p->parent != goal) 
            {
                if (getpos(t) == getpos(p)) 
                    rotate(p);
                else 
                    rotate(t);
            }
            rotate(t);
        }
        if (!goal) 
            root = t;
    }

    
    Node* build(const vector<int>& seq, int l, int r, Node* p) 
    {
        if (l > r) 
            return nullptr;
        int mid = l + (r - l) / 2;
        Node* u = new Node(seq[mid]);
        u->parent = p;
        pos[seq[mid]] = u; 

        u->ch[0] = build(seq, l, mid - 1, u);
        u->ch[1] = build(seq, mid + 1, r, u);
        pushup(u);
        return u;
    }

    void build(const vector<int>& seq) 
    {
        vector<int> init;
        init.push_back(0);
        for (int x : seq) 
            init.push_back(x);
        init.push_back(seq.size() + 1); 
        root = build(init, 0, init.size() - 1, nullptr);
    }

    
    Node* kth(int k) 
    {
        Node* t = root;
        while (t) 
        {
            int lsz = t->ch[0] ? t->ch[0]->size : 0;
            if (k <= lsz) 
                t = t->ch[0];
            else if (k == lsz + 1) 
                return t;
            else 
            {
                k -= lsz + 1;
                t = t->ch[1];
            }
        }
        return nullptr;
    }


    Node* extract(Node* x) 
    {
        splay(x); 
        Node* pre = x->ch[0];
        while (pre->ch[1]) 
            pre = pre->ch[1]; 
        
        Node* nxt = x->ch[1];
        while (nxt->ch[0]) 
            nxt = nxt->ch[0];

        splay(pre, nullptr);
        splay(nxt, pre);
        
       
        Node* target = nxt->ch[0];
        nxt->ch[0] = nullptr;
        target->parent = nullptr;
        
        pushup(nxt);
        pushup(pre);
        return target;
    }

   
    void insertAfter(Node* pre, Node* x) 
    {
        splay(pre, nullptr);
        Node* nxt = pre->ch[1];
        while (nxt->ch[0]) 
            nxt = nxt->ch[0]; 
        
        splay(nxt, pre);
        nxt->ch[0] = x;
        x->parent = nxt;
        
        pushup(nxt);
        pushup(pre);
    }
};


void solve()
{
    int n, m;
    cin >> n >> m;
    
    SplaySeq sp(n);
    vector<int> a(n);
    for (int i = 0; i < n;i++)
        cin >> a[i];
    sp.build(a);
    while(m--)
    {
        string op;
        cin >> op;        
        if(op == "Front")
        {
            int s;
            cin >> s;
            Node *x = sp.extract(sp.pos[s]);
            Node *head = sp.kth(1);
            sp.insertAfter(head, x);
        }
        else if(op == "Back")
        {
            int s;cin >> s;
            Node *x = sp.extract(sp.pos[s]);
            Node *backf = sp.kth(sp.root->size - 1);
            sp.insertAfter(backf, x);
        }
        else if(op == "Insert")
        {
            int s, t;
            cin >> s >> t;
            if(t == 0)
                continue;
            sp.splay(sp.pos[s]);
            int frontcnt = sp.pos[s]->ch[0]->size - 1;

            Node *x = sp.extract(sp.pos[s]);

            Node *targetpre = sp.kth(1 + frontcnt + t);
            sp.insertAfter(targetpre, x);
        }
        else if(op == "Ask")
        {
            int s;
            cin >> s;
            sp.splay(sp.pos[s]);
            cout << sp.pos[s]->ch[0]->size - 1 << "\n";
        }
        else if(op == "Query")
        {
            int k;
            cin >> k;
            Node *ans = sp.kth(k + 1);
            cout << ans->id << "\n";
        }

    }
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}