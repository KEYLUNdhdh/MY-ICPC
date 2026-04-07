#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Treap
{
    static const int INF = 1e9;
    vector<int> val, dat, sz, cnt;
    vector<array<int,2>> ch;
    int tot, root;
    Treap() {}
    Treap(int n)
    {
        val.resize(n + 5);
        dat.resize(n + 5);
        sz.resize(n + 5);
        cnt.resize(n + 5);
        ch.resize(n + 5, {0, 0});
        tot = 0;
        root = 0;
        build();
    }
    int New(int v)
    {
        val[++tot] = v;
        dat[tot] = rand();
        sz[tot] = 1;
        cnt[tot] = 1;
        ch[tot][0] = ch[tot][1] = 0;
        return tot;
    }
    void pushup(int id)
    {
        if(!id)
            return;
        sz[id] = cnt[id] + sz[ch[id][0]] + sz[ch[id][1]];
    }

    void rotate(int &id,int d)
    {
        int tp = ch[id][d ^ 1];
        ch[id][d ^ 1] = ch[tp][d];
        ch[tp][d] = id;
        id = tp;
        pushup(ch[id][d]);
        pushup(id);
    }
    void build()
    {
        root = New(-INF);
        ch[root][1] = New(INF);
        pushup(root);
    }
    void insert(int &id,int v)
    {
        if(!id)
        {
            id = New(v);
            return;
        }
        if(val[id] == v)
        {
            cnt[id]++;
        }
        else
        {
            int d = (v < val[id] ? 0 : 1);
            insert(ch[id][d], v);
            if(dat[ch[id][d]] > dat[id])
                rotate(id, d ^ 1);
        }
        pushup(id);
    }
    void remove(int &id, int v)
    {
        if(!id)
            return;
        if(v == val[id])
        {
            if(cnt[id] > 1)
            {
                cnt[id]--;
                pushup(id);
                return;
            }
            else
            {
                if(ch[id][0] || ch[id][1])
                {
                    if(!ch[id][1]  || dat[ch[id][0]] > dat[ch[id][1]])
                    {
                        rotate(id, 1);
                        remove(ch[id][1], v);
                    }
                    else
                    {
                        rotate(id, 0);
                        remove(ch[id][0], v);
                    }
                    pushup(id);
                }
                else
                {
                    id = 0;
                }
                return;
            }
        }
        v < val[id] ? remove(ch[id][0], v) : remove(ch[id][1], v);
        pushup(id);
    }
    //查询 M 中有多少个数比 x 小，并且将得到的答案加一。
    //排名
    int getRank(int id,int v)
    {
        if(!id)
            return 1;
        if(v == val[id])
            return sz[ch[id][0]] + 1;
        else if(v < val[id])
            return getRank(ch[id][0], v);
        else
            return sz[ch[id][0]] + cnt[id] + getRank(ch[id][1], v);
    }
    //根据排名找数字
    int getVal(int id,int rank)
    {
        if(!id)
            return INF;
        if(rank <= sz[ch[id][0]])
            return getVal(ch[id][0], rank);
        if(rank <= sz[ch[id][0]] + cnt[id])
            return val[id];
        return getVal(ch[id][1],rank - sz[ch[id][0]] - cnt[id]);
    }
    //前驱（小于 x，且最大的数）。
    int getPre(int v)
    {
        int id = root,pre = -INF;
        while(id)
        {
            if(val[id] < v)
                pre = val[id], id = ch[id][1];
            else
                id = ch[id][0];
        }
        return pre;
    }
    //后继（大于 x，且最小的数）。
    int getNext(int v)
    {
        int id = root, nxt = INF;
        while(id)
        {
            if(val[id] > v)
                nxt = val[id], id = ch[id][0];
            else
                id = ch[id][1];
        }
        return nxt;
    }
};

int main()
{
    int n;
    cin >> n;
    Treap t(n);
    while(n--)
    {
        int op, x;
        cin >> op >> x;
        if(op == 1)
            t.insert(t.root, x);
        else if(op == 2)
            t.remove(t.root, x);
        else if(op == 3)
            cout << t.getRank(t.root, x) - 1<< "\n";
        else if(op == 4)
            cout << t.getVal(t.root, x + 1) << "\n";
        else if(op == 5)
            cout << t.getPre(x) << "\n";
        else
            cout << t.getNext(x) << "\n";
    }
}