#include <bits/stdc++.h>
#define lyc_fan_club main
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
mt19937 rnd(time(0));
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
constexpr i64 MOD = 998244353, INF = 2000000000000000000;

struct Treap
{
    vector<i64> val, dat, sz, cnt;
    vector<array<i64,2>> ch;
    i64 tot, root;
    Treap() {}
    Treap(i64 n)
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
    i64 New(i64 v)
    {
        val[++tot] = v;
        dat[tot] = rand();
        sz[tot] = 1;
        cnt[tot] = 1;
        ch[tot][0] = ch[tot][1] = 0;
        return tot;
    }
    void pushup(i64 id)
    {
        if(!id)
            return;
        sz[id] = cnt[id] + sz[ch[id][0]] + sz[ch[id][1]];
    }

    void rotate(i64 &id,i64 d)
    {
        i64 tp = ch[id][d ^ 1];
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
    void insert(i64 &id,i64 v)
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
            i64 d = (v < val[id] ? 0 : 1);
            insert(ch[id][d], v);
            if(dat[ch[id][d]] > dat[id])
                rotate(id, d ^ 1);
        }
        pushup(id);
    }
    void remove(i64 &id, i64 v)
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
    i64 getRank(i64 id,i64 v)
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
    i64 getVal(i64 id,i64 rank)
    {
        if(!id)
            return INF;
        if(rank <= sz[ch[id][0]])
            return getVal(ch[id][0], rank);
        if(rank <= sz[ch[id][0]] + cnt[id])
            return val[id];
        return getVal(ch[id][1],rank - sz[ch[id][0]] - cnt[id]);
    }
    i64 getPre(i64 v)
    {
        i64 id = root,pre = -INF;
        while(id)
        {
            if(val[id] < v)
                pre = val[id], id = ch[id][1];
            else
                id = ch[id][0];
        }
        return pre;
    }
    i64 getNext(i64 v)
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

void solve()
{
    int n, m;
    cin >> n >> m;
    Treap tr(n + 5 + m);
    for (int i = 0; i < n;i++)
    {
        int x;
        cin >> x;
        tr.insert(tr.root, x);
    }
    int lst = 0;
    i64 xorVal = 0;
    while(m--)
    {
        int op, x;
        cin >> op >> x;
        x = x ^ lst;
        if(op == 1)
            tr.insert(tr.root, x);
        else if(op == 2)
            tr.remove(tr.root, x);
        else if(op == 3)
        {
            lst = tr.getRank(tr.root, x) - 1;
            xorVal ^= lst;
            // cout << lst << "\n";
        }
        else if(op == 4)
        {
            lst = tr.getVal(tr.root, x + 1);
            xorVal ^= lst;
            // cout << lst << "\n";
        }
        else if(op == 5)
        {
            lst = tr.getPre(x);
            xorVal ^= lst;
            // cout << lst << "\n";
        }
        else
        {
            lst = tr.getNext(x);
            xorVal ^= lst;
            // cout << lst << "\n";
        }
    }
    cout << xorVal;
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}