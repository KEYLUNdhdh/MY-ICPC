#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

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
constexpr i64 MOD = 998244353, INF = 1e9;

struct Trie
{
    vector<array<int, 27>> ch;
    vector<int> cnt;
    vector<int> pre;
    vector<array<i64, 2>> ppre;
    Trie()
    {
        newNode();
    }
    
    int newNode()
    {
        ch.push_back({0});
        cnt.push_back(0);
        pre.push_back(0);
        ppre.push_back({0, 0});
        return ch.size() - 1;
    }
    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        assert(false);
        return -1;
    }
    void insert(const string& s, int id)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                ch[p][u] = newNode();
            p = ch[p][u];
            pre[p]++;
            ppre[p][id]++;
        }
        cnt[p]++;
    }

    int search(const string &s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                return 0;
            p = ch[p][u];
        }
        return cnt[p];
    }

    int searchPrefix(const string &s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                return 0;
            p = ch[p][u];
        }
        return pre[p];
    }

    void clear() 
    {
        ch.clear();
        cnt.clear();
        pre.clear();
        newNode();
    }
};

struct GSAM
{
    static constexpr int SIGMA = 27;

    struct Node 
    {
        int len;
        int link;
        int next[SIGMA];
        array<i64, 2> siz;
    };

    vector<Node> t;
    vector<int> trieState;
    int sz;
    bool built;
    bool sizComputed;

    GSAM()
    {
        clear();
    }

    GSAM (const Trie &trie)
    {
        build(trie);
    }

    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')   
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        assert(false);
        return -1;
    }

    void clear()
    {
        t.clear();
        t.push_back(Node{});
        t.push_back(Node{});

        sz = 1;
        t[1].len = 0;
        t[1].link = 0;
        trieState.clear();
        built = false;
        sizComputed = false;
    }

    int newNode()
    {
        t.push_back(Node{});
        return ++sz;
    }
    int extend(int last, int idx)
    {
        assert(!sizComputed);

        if(t[last].next[idx])
        {
            int q = t[last].next[idx];
            if(t[last].len + 1 == t[q].len)
                return q;

            int clone = newNode();
            t[clone] = t[q];
            t[clone].len = t[last].len + 1;
            t[clone].siz[0] = 0;
            t[clone].siz[1] = 0;

            int p = last;
            while(p > 0 && t[p].next[idx] == q)
            {
                t[p].next[idx] = clone;
                p = t[p].link;
            }

            t[q].link = clone;
            return clone;
        }

        int cur = newNode();
        t[cur].len = t[last].len + 1;
        int p = last;

        while(p > 0 && !t[p].next[idx])
        {
            t[p].next[idx] = cur;
            p = t[p].link;
        }

        if(p == 0)
            t[cur].link = 1;
        else
        {
            int q = t[p].next[idx];
            if(t[p].len + 1 == t[q].len)
                t[cur].link = q;
            else
            {
                int clone = newNode();
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                t[clone].siz[0] = 0;
                t[clone].siz[1] = 0;

                while(p > 0 && t[p].next[idx] == q)
                {
                    t[p].next[idx] = clone;
                    p = t[p].link;
                }

                t[q].link = t[cur].link = clone;
            }
        }
        return cur;
    }

    void build(const string &s)
    {
        clear();

        t.reserve(2 * s.size() + 2);

        int last = 1;
        for(char ch : s)
            last = extend(last, getId(ch));

        built = true;
    }

    void build(const Trie &trie)
    {
        clear();

        t.reserve(2 * trie.ch.size() + 2);

        trieState.assign(trie.ch.size(), 0);
        trieState[0] = 1;

        queue<int> q;
        q.push(0);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int idx = 0; idx < SIGMA;idx++)
            {
                int v = trie.ch[u][idx];
                if(!v)
                    continue;

                trieState[v] = extend(trieState[u], idx);
                q.push(v);
            }
        }

        for (int u = 1; u < (int)trie.ch.size();u++)
        {
            int p = trieState[u];
            t[p].siz[0] += trie.ppre[u][0];
            t[p].siz[1] += trie.ppre[u][1];
        }

        built = true;
    }

    bool isSubString(const string &query)
    {
        if(query.empty())
            return 0;

        assert(built);
        int p = 1;
        for(char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return false;

            p = t[p].next[idx];
        }
        return true;
    }

    void comSiz()
    {
        assert(built);

        if(sizComputed)
            return;

        int maxlen = 0;
        for (int i = 1; i <= sz;i++)
            maxlen = max(maxlen, t[i].len);

        vector<int> c(maxlen + 1, 0);
        vector<int> rk(sz + 1, 0);

        for (int i = 1; i <= sz;i++)
            c[t[i].len]++;
        for (int i = 1; i <= maxlen;i++)
            c[i] += c[i - 1];
        for (int i = sz; i >= 1;i--)
            rk[c[t[i].len]--] = i;

        for (int i = sz; i >= 2;i--)
        {
            int u = rk[i];
            t[t[u].link].siz[0] += t[u].siz[0];
            t[t[u].link].siz[1] += t[u].siz[1];
        }
        sizComputed = true;
    }


    i64 distinctSubStringCount()
    {
        assert(built);
        i64 ans = 0;
        for (int i = 2; i <= sz;i++)
            ans += t[i].len - t[t[i].link].len;
        return ans;
    }

    int LCS(const string &s)
    {
        assert(built);

        int p = 1;
        int len = 0;
        int ans = 0;

        for(char c : s)
        {
            int idx = getId(c);

            while(p != 1 && !t[p].next[idx])
            {
                p = t[p].link;
                len = t[p].len;
            }

            if(t[p].next[idx])
            {
                p = t[p].next[idx];
                len++;
            }
            else
            {
                p = 1;
                len = 0;
            }

            ans = max(ans, len);
        }

        return ans;
    }

};

void solve()
{
    string a, b;
    cin >> a >> b;

    Trie t;
    t.insert(a, 0);
    t.insert(b, 1);

    GSAM sam(t);
    sam.comSiz();

    i64 ans = 0;
    for (int u = 1; u <= sam.sz;u++)
        ans += (sam.t[u].len - sam.t[sam.t[u].link].len) * sam.t[u].siz[0] * sam.t[u].siz[1];

    cout << ans;
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