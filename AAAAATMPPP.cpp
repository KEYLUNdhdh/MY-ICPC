// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
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
#define KEYLUN main
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
void debug_out() { cerr << "\n"; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char* names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char* names, Head H, Tail... T) {
    while (*names == ' ' || *names == ',') names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i) {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[') bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']') bracket--;
        else if (names[i] == ',' && bracket == 0) break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H) cerr << v << " ";
    cerr << "\n"; 
    
    debugarr_out(names + i + 1, T...);
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template<class T> void chmin(T &a, T b) { if (a > b) a = b; }
template<class T> void chmax(T &a, T b) { if (a < b) a = b; }


// 20k 位
vector<int> primes, isPrime;

void sieve(int n)
{
    isPrime.assign(n + 1, 1);
    isPrime[1] = 0;
    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
            primes.push_back(i);
        for (auto p : primes)
        {
            if (i * p > n)
                break;
            isPrime[i * p] = 0;
            if (i % p == 0)
                break;
        }
    }
}

// 每个合数只被其最小质因数标记一次

int solve()
{
    i64 t = 300 * 300 * 300 * 300 * 8 * 2 / 1024 / 1024;
    debug(t);
    cout << t;
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    sieve(1e3);
    debug(primes.size());
    // debugarr(primes);
    int T = 1;
    // cin >> T;
    // sieve(1e5);
    // debugarr(primes);
    while(T--)
        solve();
    return 0;
}