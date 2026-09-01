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

ostream &operator<<(ostream &os, i128 n) {
    string s;
    int f = 0;
    if(n == 0)
        s = "0";
    if(n < 0)
    {
        f = 1;
        n = -n;
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    if(f)
        s = '-' + s;
    return os << s;
}

istream &operator>>(istream &is,i128& n)
{
    n = 0;
    string s;
    is >> s;
    int sign = 1, start = 0;
    if(s[0] == '-')
    {
        sign = -1;
        start = 1;
    }
    for (int i = start; i < s.size();i++)
    {
        n = n * 10 + s[i] - '0';
    }
    n *= sign;
    return is;
}

int p[] = {2, 3, 5, 7};
i64 memo[22][66][37][26][22];

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    a %= 10;
    while(b)
    {
        if(b)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve()
{
    i64 k;
    i128 l, r;
    cin >> k >> l >> r;
    array<int, 4> rem = {0, 0, 0, 0};
    for (int i = 0; i < 4;i++)
    {
        i64 pr = p[i];
        if(k % pr == 0)
        {
            while(k % pr == 0)
            {
                k /= pr;
                rem[i]++;
            }
        }
    }
    // debug(k);
    for (int i = 0; i < 4;i++)
        cerr << rem[i];
    if (k != 1)
    {
        rem = {65, 0, 0, 0};
    }

    auto add = [&](array<int, 4> cnt, int val) -> array<int, 4>
    {
        if(val == 2)
            cnt[0]++;
        else if(val == 3)
            cnt[1]++;
        else if(val == 5)
            cnt[2]++;
        else if(val == 4)
            cnt[0] += 2;
        else if(val == 6)
            cnt[0]++, cnt[1]++;
        else if(val == 7)
            cnt[3]++;
        else if(val == 8)
            cnt[0] += 3;
        else if(val == 9)
            cnt[1] += 2;
        else if(val == 0)
            cnt = rem;
        for (int i = 0; i < 4;i++)
            chmin(cnt[i], rem[i]);
        return cnt;
    };

    auto sol = [&](i128 n) -> i64
    {
        vector<int> dig;
        i128 tmp = n;
        while(tmp)
        {
            dig.push_back(tmp % 10);
            tmp /= 10;
        }

        memset(memo, -1, sizeof memo);
        auto dfs = [&](auto self, int lim, int num, int pos, array<int, 4> cnt) -> i64
        {
            if(pos < 0)
            {
                if(!num)
                    return 0;
                if(cnt == rem)
                    return 1;
                return 0;
            }

            if(!lim && num && memo[pos][cnt[0]][cnt[1]][cnt[2]][cnt[3]] != -1)
                return memo[pos][cnt[0]][cnt[1]][cnt[2]][cnt[3]];

            i64 res = 0;
            int up = lim ? dig[pos] : 9;
            for (int i = 0; i <= up;i++)
            {
                if(!num && i == 0)
                {
                    res = (res + self(self, lim && (i == up), 0, pos - 1, cnt)) % MOD;
                }
                else
                {
                    array<int, 4> nxtcnt = add(cnt, i);
                    res = (res + self(self, lim && (i == up), 1, pos - 1, nxtcnt)) % MOD;
                }
            }

            if(!lim && num)
                memo[pos][cnt[0]][cnt[1]][cnt[2]][cnt[3]] = res;
            return res;
        };
        return dfs(dfs, 1, 0, dig.size() - 1, {0, 0, 0, 0});
    };

    cout << (sol(r) - sol(l - 1) + MOD) % MOD;

}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
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