#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
const u64 SEED = rnd();

struct HashMap
{
    static const int MOD = 8388617;
    static const int MAXNODE = 5e6 + 5;

    int head[MOD];
    int nxt[MAXNODE];
    u64 keys[MAXNODE];
    u64 vals[MAXNODE];
    int tot;

    inline int hashFunc(u64 x)
    {
        x += SEED;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return (x ^ (x >> 31)) % MOD;
    }

    inline u64 &operator[](const u64 k)
    {
        int h = hashFunc(k);

        for (int i = head[h]; i; i = nxt[i])
            if(keys[i] == k)
                return vals[i];

        ++tot;
        keys[tot] = k;
        vals[tot] = 0;
        nxt[tot] = head[h];
        head[h] = tot;
        return vals[tot];
    }

    inline void clear()
    {
        for (int i = 1; i <= tot;i++)
            head[hashFunc(keys[i])] = 0;

        tot = 0;
    }
} f; 
