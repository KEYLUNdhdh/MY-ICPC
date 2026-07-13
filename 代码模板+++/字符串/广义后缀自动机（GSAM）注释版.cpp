#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Trie
{
    vector<array<int, 62>> ch;
    vector<int> cnt;
    vector<int> pre;

    Trie()
    {
        newNode();
    }

    int newNode()
    {
        ch.push_back({0});
        cnt.push_back(0);
        pre.push_back(0);
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
    void insert(const string& s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u])
                ch[p][u] = newNode();
            p = ch[p][u];
            pre[p]++;
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
    static constexpr int SIGMA = 62;

    struct Node 
    {
        int len;
        int link;
        int next[SIGMA];
        i64 siz;
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
            t[clone].siz = 0;

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
                t[clone].siz = 0;

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
            t[p].siz += trie.pre[u];
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
            t[t[u].link].siz += t[u].siz;
        }
        sizComputed = true;
    }

    i64 count(const string &query)
    {
        if(query.empty())
            return 0;
        comSiz();
        int p = 1;
        for(char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return 0;
            p = t[p].next[idx];
        }
        return t[p].siz;
    }

    i64 distinctSubStringCount()
    {
        assert(built);
        i64 ans = 0;
        for (int i = 2; i <= sz;i++)
            ans += t[i].len - t[t[i].link].len;
        return ans;
    }
};