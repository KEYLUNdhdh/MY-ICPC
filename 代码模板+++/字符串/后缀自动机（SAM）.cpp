#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SAM
{
    struct Node
    {
        int len;
        int link;
        int next[70];
        i64 siz;
    };

    vector<Node> t;
    int sz;
    int last;
    bool sizComputed;
    SAM(int n)
    {
        t.resize(2 * n + 2);
        sz = 1;
        last = 1;
        t[1].len = 0;
        t[1].link = 0;
        sizComputed = 0;
    }

    int getId(char c) const
    {
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        return 69;
    }

    void extend(char c)
    {
        int idx = getId(c);
        int cur = ++sz;
        t[cur].len = t[last].len + 1;
        t[cur].siz = 1;

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
                int clone = ++sz;
                t[clone].len = t[p].len + 1;
                t[clone].link = t[q].link;
                copy(begin(t[q].next), end(t[q].next), begin(t[clone].next));
                t[clone].siz = 0;

                while(p > 0 && t[p].next[idx] == q)
                {
                    t[p].next[idx] = clone;
                    p = t[p].link;
                }

                t[q].link = t[cur].link = clone;
            }
        }

        last = cur;
    }

    bool isSubstirng(const string & query)
    {
        int p = 1;
        for (char c : query)
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
        if(sizComputed)
            return;

        vector<int> c(sz + 1, 0);
        vector<int> rk(sz + 1, 0);
        for (int i = 1; i <= sz;i++)
            c[t[i].len]++;
        for (int i = 1; i <= sz;i++)
            c[i] += c[i - 1];
        for (int i = 1; i <= sz;i++)
            rk[c[t[i].len]--] = i;

        for (int i = sz; i >= 2;i--)
        {
            int u = rk[i];
            t[t[u].link].siz += t[u].siz;
        }

        sizComputed = 1;
    }

    i64 count(const string &query)
    {
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
};