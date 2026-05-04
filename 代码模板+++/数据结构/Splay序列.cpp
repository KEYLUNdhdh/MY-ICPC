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

    
    Node* buildHelper(const vector<int>& seq, int l, int r, Node* p) 
    {
        if (l > r) 
            return nullptr;
        int mid = l + (r - l) / 2;
        Node* u = new Node(seq[mid]);
        u->parent = p;
        pos[seq[mid]] = u; 

        u->ch[0] = buildHelper(seq, l, mid - 1, u);
        u->ch[1] = buildHelper(seq, mid + 1, r, u);
        pushup(u);
        return u;
    }

    void build(const vector<int>& seq) 
    {
        vector<int> init_seq;
        init_seq.push_back(0);
        for (int x : seq) 
            init_seq.push_back(x);
        init_seq.push_back(seq.size() + 1); 
        root = buildHelper(init_seq, 0, init_seq.size() - 1, nullptr);
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