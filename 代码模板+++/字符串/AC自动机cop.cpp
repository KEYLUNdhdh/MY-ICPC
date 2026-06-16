#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Trie
{
    vector<array<int, 70>> ch;

    Trie()
    {
        newNode();
    }

    int newNode()
    {
        ch.push_back({0});
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

    int insert(const string& s)
    {
        int p = 0;
        for(char c : s)
        {
            int u = getId(c);
            if(!ch[p][u]) ch[p][u] = newNode();
            p = ch[p][u];
        }
        return p;
    }
};

struct ACAuto : public Trie
{
    vector<int> fail;
    vector<int> cnt;      
    vector<int> bfsOrder; 

    ACAuto() : Trie() {}

    void build()
    {
        int n = ch.size();
        fail.assign(n, 0);
        cnt.assign(n, 0);

        queue<int> q;
        for (int i = 0; i < 70; i++)
        {
            if (ch[0][i])
            {
                q.push(ch[0][i]);
                bfsOrder.push_back(ch[0][i]); 
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < 70; i++)
            {
                if (ch[u][i])
                {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    q.push(ch[u][i]);
                    bfsOrder.push_back(ch[u][i]); 
                }
                else
                    ch[u][i] = ch[fail[u]][i];
            }
        }
    }

    void query(const string &t)
    {
        int u = 0;
        for (char c : t)
        {
            u = ch[u][getId(c)];
            cnt[u]++;
        }
    }

    void topoCount()
    {
        for (int i = bfsOrder.size() - 1; i >= 0; i--)
        {
            int u = bfsOrder[i];
            cnt[fail[u]] += cnt[u];
        }
    }
    
    int getCnt(int nodeId) const 
    {
        return cnt[nodeId];
    }
};
