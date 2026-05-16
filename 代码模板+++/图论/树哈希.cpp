#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

const u64 MASK = rnd();

struct TreeHasher
{
    static u64 shift(u64 x)
    {
        x ^= MASK;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        x ^= MASK;
        return x;
    }
};