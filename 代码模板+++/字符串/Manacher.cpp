#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Manacher
{
    string t;
    vector<int> p;
    int maxlen;

    Manacher(const string &s)
    {
        int n = s.length();
        t.assign(2 * n + 3, '#');
        t[0] = '^';
        for (int i = 0; i < n;i++)
            t[i * 2 + 2] = s[i];

        t[n * 2 + 2] = '$';

        int m = t.length();
        p.assign(m, 0);
        int mid = 0, r = 0;
        maxlen = 0;

        for (int i = 1; i < m - 1;i++)
        {
            if(i < r)
                p[i] = min(r - i, p[2 * mid - i]);
            else
                p[i] = 1;
        
            while(t[i - p[i]] == t[i + p[i]])
                p[i]++;

            if(i + p[i] > r)
            {
                mid = i;
                r = i + p[i];
            }

            maxlen = max(maxlen, p[i] - 1);
        }
    }

    int specific(int idx)
    {
        return p[idx * 2 + 2] - 1;
    }
};