#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Trie
{
    vector<array<int, 70>> ch;
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
        return 69;
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

// 询问所有模式串是否在一个字符串中出现过，统计出现次数。
struct ACAuto : public Trie
{
    vector<int> fail;

    ACAuto() : Trie() {}

    void build()
    {
        int n = ch.size();
        fail.assign(n, 0);

        queue<int> q;
        for (int i = 0;i < 70;i++)
            if(ch[0][i])
                q.push(ch[0][i]);

        while(!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < 70;i++)
            {
                if(ch[u][i])
                {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.push(ch[u][i]);
                }
                else
                    ch[u][i] = ch[fail[u]][i];
            }
        }
    }

    int query(const string &t)
    {
        int u = 0, res = 0;
        for(char c : t)
        {
            u = ch[u][getId(c)];
            for (int j = u; j && cnt[j] != -1;j = fail[j])
            {
                res += cnt[j];
                cnt[j] = -1;
            } 
        }
        return res;
    }

    void clear()
    {
        Trie::clear();
        fail.clear();
    }
};  

