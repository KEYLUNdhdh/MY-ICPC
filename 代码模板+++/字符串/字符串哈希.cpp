#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;

struct HashVal
{
    u64 h1, h2;
    bool operator<(const HashVal &b) const
    {
        if(h1 != b.h1)
            return h1 < b.h1;
        return h2 < b.h2;
    }

    bool operator==(const HashVal &b) const  
    {
        return h1 == b.h1 && h2 == b.h2;
    }

    bool operator!=(const HashVal &b) const
    {
        return h1 != b.h1 || h2 != b.h2;
    }
};

struct StringHash
{
    static const u64 B1 = 131, M1 = 1e9 + 7;
    static const u64 B2 = 13331, M2 = 1e9 + 9;

    int n;
    vector<u64> h1, h2;
    vector<u64> p1, p2;

    StringHash(const string &s)
    {
        n = s.length();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        p1.assign(n + 1, 1);
        p2.assign(n + 1, 1);

        for (int i = 0; i < n;i++)
        {
            h1[i + 1] = (h1[i] * B1 + s[i]) % M1;
            h2[i + 1] = (h2[i] * B2 + s[i]) % M2;
            p1[i + 1] = (p1[i] * B1) % M1;
            p2[i + 1] = (p2[i] * B2) % M2;
        }
    }

    //0 - index
    HashVal get(int l, int r)
    {
        l++, r++;// offset
        u64 res1 = (h1[r] + M1 - h1[l - 1] * p1[r - l + 1] % M1) % M1;
        u64 res2 = (h2[r] + M2 - h2[l - 1] * p2[r - l + 1] % M2) % M2;
        return {res1, res2};
    }

    HashVal getAll()
    {
        return get(0, n - 1);
    }
};