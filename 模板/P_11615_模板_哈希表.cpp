#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 998244353, INF = 1e9;
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
} f; 

inline u64 read()
{
	char ch;
	ch = getchar();
	//ch = getchar_unlocked();
	u64 f = 1;
	while (ch > '9' || ch < '0')
	{
		if (ch == '-') f = -1;
		ch = getchar();
		//ch = getchar_unlocked();
	}
	u64 k = 0;
	while (ch >= '0' && ch <= '9')
	{
		k = k * 10 + (ch - '0');
		ch = getchar();
		//ch = getchar_unlocked();
	}
	return k * f;
}

inline void out(u64 x)
{
	char ch;
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else out(x / 10), putchar(x % 10 + '0');
}

void solve()
{
    int n;
    n = read();

    u64 finalans = 0;
    for (u64 i = 1; i <= n;i++)
    {
        u64 x, y;
        x = read(), y = read();

        u64 ans = f[x];
        f[x] = y;
        finalans += ans * (u64)i;
    }

    out(finalans);
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();

    return 0;
}