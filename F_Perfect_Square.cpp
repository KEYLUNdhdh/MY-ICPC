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
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 1e9 + 7, INF = 2e18;
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


void solve()
{
    int n;
    cin >> n;
    set<int> st;
    map<int, vector<int>> mp;
    for (int i = 0; i < n;i++)
    {
        i64 a;
        cin >> a;
        for (int j : primes)
        {
            if(j * j > a)
                break;
            if(a % j == 0)
            {
                int cnt = 0;
                st.insert(j);
                while(a % j == 0)
                    a /= j, cnt++;
                mp[j].push_back(cnt);
            }
        }
        if(a > 1)
        {
            st.insert(a);
            mp[a].push_back(1);
        }
    }

    i64 ans = 1;
    for(int p : st)
    {
        i64 res = 1;
        i64 x = 1, y = 0;
        for(int cnt : mp[p])
        {
            i64 a = 0, b = 0;
            i64 curp = 1;
            for (int i = 0; i <= cnt / 2;i++)
            {
                a = (a + curp) % MOD;
                curp = curp * p % MOD;
            }

            curp = 1;
            for (int i = 0; i <= (cnt - 1) / 2;i++)
            {
                b = (b + curp) % MOD;
                curp = curp * p % MOD;
            }

            i64 nx = (x * a % MOD + y * b % MOD * p % MOD) % MOD;
            i64 ny = (x * b % MOD + y * a % MOD) % MOD;
            x = nx, y = ny;
        }
        ans = ans * x % MOD;
    }
    cout << ans;
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    sieve(1e6);
    // cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}