#include <bits/stdc++.h>
using namespace std;

struct SplaySeq {
    struct Node {
        int id;      // 存学号
        int size;    // 子树大小
        Node *ch[2];
        Node *parent;
        Node(int _id) : id(_id), size(1), ch{nullptr, nullptr}, parent(nullptr) {}
    };

    Node *root;
    vector<Node*> pos; // pos[i] 指向学号为 i 的节点

    SplaySeq(int n) : root(nullptr) {
        pos.resize(n + 2, nullptr); // 容量包含哨兵 0 和 n+1
    }

    int getpos(Node* t) { return t->parent ? (t->parent->ch[1] == t) : 0; }
    
    void pushup(Node* t) {
        if (!t) return;
        t->size = 1;
        if (t->ch[0]) t->size += t->ch[0]->size;
        if (t->ch[1]) t->size += t->ch[1]->size;
    }

    void rotate(Node *t) {
        Node *q = t->parent;
        int x = !getpos(t);
        q->ch[!x] = t->ch[x];
        if (t->ch[x]) t->ch[x]->parent = q;
        t->parent = q->parent;
        if (q->parent) q->parent->ch[getpos(q)] = t;
        t->ch[x] = q;
        q->parent = t;
        pushup(q);
        pushup(t);
    }

    // 将节点 t 旋转到 goal 的下面（如果 goal 为 nullptr 则转到根）
    void splay(Node *t, Node *goal = nullptr) {
        while (t->parent != goal) {
            Node *p = t->parent;
            if (p->parent != goal) {
                if (getpos(t) == getpos(p)) rotate(p);
                else rotate(t);
            }
            rotate(t);
        }
        if (!goal) root = t;
    }

    // ------------------- 序列专属大招 -------------------

    // O(N) 完美建树
    Node* buildHelper(const vector<int>& seq, int l, int r, Node* p) {
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;
        Node* u = new Node(seq[mid]);
        u->parent = p;
        pos[seq[mid]] = u; // 记录映射

        u->ch[0] = buildHelper(seq, l, mid - 1, u);
        u->ch[1] = buildHelper(seq, mid + 1, r, u);
        pushup(u);
        return u;
    }

    void build(const vector<int>& seq) {
        vector<int> init_seq;
        init_seq.push_back(0); // 极小哨兵
        for (int x : seq) init_seq.push_back(x);
        init_seq.push_back(seq.size() + 1); // 极大哨兵
        root = buildHelper(init_seq, 0, init_seq.size() - 1, nullptr);
    }

    // 找树中排名第 k 的节点（从 1 开始）
    Node* kth(int k) {
        Node* t = root;
        while (t) {
            int lsz = t->ch[0] ? t->ch[0]->size : 0;
            if (k <= lsz) t = t->ch[0];
            else if (k == lsz + 1) return t;
            else {
                k -= lsz + 1;
                t = t->ch[1];
            }
        }
        return nullptr;
    }

    // 从队伍中抽离节点 x
    Node* extract(Node* x) {
        splay(x); // 第一步：把 x 拎到树根
        // 此时 x 的左子树是 [排在 x 前面的所有人]，右子树是 [排在 x 后面的所有人]
        // 找 x 前面的最后一个人（前驱 pre），也就是 x 左子树里最靠右的节点

        Node* pre = x->ch[0];
        while (pre->ch[1]) pre = pre->ch[1]; // 找前驱
        
        // 找 x 后面的第一个人（后继 nxt），也就是 x 右子树里最靠左的节点
        Node* nxt = x->ch[1];
        while (nxt->ch[0]) nxt = nxt->ch[0]; // 找后继

        // 核心连击：
        splay(pre, nullptr);// 把 pre 拎到整棵树的根
        splay(nxt, pre);// 把 nxt 拎到 pre 的下面（成为 pre 的右儿子）
        
        // 魔法发生了！
        // 因为 pre 在 x 前面，nxt 在 x 后面，此时 nxt 的左儿子，必定只能是 x 自己！
        // x 像夹心饼干一样被死死卡在了 nxt 的左边。

        Node* target = nxt->ch[0];// 抓到饼干夹心 x
        nxt->ch[0] = nullptr;// 咔嚓一刀，把 x 切断
        target->parent = nullptr;// x 彻底脱离树结构
        
        pushup(nxt);// 更新人数信息
        pushup(pre);
        return target;// 把抠出来的 x 交给你
    }

    //怎么把抠出来的人，插到别人后面？(insertAfter)
    // 将节点 x 插入到 pre 节点后面
    void insertAfter(Node* pre, Node* x) {
        splay(pre, nullptr);// 第一步：把 pre 拎到根

        // 找 pre 原本后面的第一个人（后继 nxt）
        Node* nxt = pre->ch[1];
        while (nxt->ch[0]) nxt = nxt->ch[0]; // 找 pre 原本的后继
        
        splay(nxt, pre);// 把 nxt 拎到 pre 的下面

        // 魔法再次发生！
        // pre 是根，nxt 是 pre 的右儿子。因为 pre 和 nxt 是紧挨着的两个人，
        // 所以 nxt 此时绝对不可能有左儿子！（如果有，说明两人中间还有人，矛盾）

        nxt->ch[0] = x;// 既然 nxt 的左儿子是空的，直接把 x 塞进去！
        x->parent = nxt;
        
        // 更新人数信息
        pushup(nxt);
        pushup(pre);
    }
};

//第四层魔法：降维打击解决具体问题有了 extract（抽离）和 insertAfter（插入）这两把神兵利器，题目的那些复杂操作简直就是搭积木：
//Front s (移到最前面)：把 s 抽离出来。找到队伍的第一个“幽灵哨兵”（Node *head = sp.kth(1)）。把 s 插入到 head 的后面。搞定！
//Back s (移到最后面)：把 s 抽离出来。找到队伍最后面真正的最后一个人（哨兵前面的那个，sp.kth(sp.root->size - 1)）。把 s 插入到他后面。搞定！
//Insert s t (向前后移动 t 个身位)：先把 s 拎到根（splay），看看它前面现在有几个人（frontcnt）。把 s 抽离出来。我们要把它插到前面有 frontcnt + t 个人的位置。这意味着它要插在第 frontcnt + t 个人（算上哨兵要再 +1）的后面！找到那个人：Node *targetpre = sp.kth(1 + frontcnt + t);把它插进去。搞定！

// if(op == "Front")
// {
//     int s;
//     cin >> s;
//     Node *x = sp.extract(sp.pos[s]);
//     Node *head = sp.kth(1);
//     sp.insertAfter(head, x);
// }
// else if(op == "Back")
// {
//     int s;cin >> s;
//     Node *x = sp.extract(sp.pos[s]);
//     Node *backf = sp.kth(sp.root->size - 1);
//     sp.insertAfter(backf, x);
// }
// else if(op == "Insert")
// {
//     int s, t;
//     cin >> s >> t;
//     if(t == 0)
//         continue;
//     sp.splay(sp.pos[s]);
//     int frontcnt = sp.pos[s]->ch[0]->size - 1;

//     Node *x = sp.extract(sp.pos[s]);

//     Node *targetpre = sp.kth(1 + frontcnt + t);
//     sp.insertAfter(targetpre, x);
// }
// else if(op == "Ask")
// {
//     int s;
//     cin >> s;
//     sp.splay(sp.pos[s]);
//     cout << sp.pos[s]->ch[0]->size - 1 << "\n";
// }
// else if(op == "Query")
// {
//     int k;
//     cin >> k;
//     Node *ans = sp.kth(k + 1);
//     cout << ans->id << "\n";
// }
