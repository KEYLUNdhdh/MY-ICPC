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
constexpr i64 MOD = 998244353, INF = 2e18;
vector<int> primes,isPrime;

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
			if(i * p > n)
				break;
			isPrime[i * p] = 0;
			if(i % p == 0)
				break;
		}
	}
}


// 20k 位
void solve()
{
    int k;
    cin >> k;
    vector<i64> t;
    vector<i64> vis(1005, 0);
    for (i64 i = 1; i <= 50000;i++)
    {
        i64 num = 1ll * k * i;
        i64 sum = 0;
        while(num)
        {
            sum += num % 10;
            num /= 10;
        }
        // debug(1ll * k * i, sum);
        if(sum <= 1000 && !vis[sum])
        {
            vis[sum] = 1ll * k * i, t.push_back(sum);
        }
    }
    for(i64 i = 1000000; i <= 1050000;i++)
    {
        i64 num = 1ll * k * i;
        i64 sum = 0;
        while(num)
        {
            sum += num % 10;
            num /= 10;
        }
        // debug(1ll * k * i, sum);
        if(sum <= 1000 && !vis[sum])
        {
            vis[sum] = 1ll * k * i, t.push_back(sum);
        }
    }

    vector<int> dp(k + 1, 0);
    vector<int> pre(k + 1, -1);
    dp[0] = 1;
    debugarr(t);
    for (int i = 0; i < t.size();i++)
    {
        for (int j = t[i]; j <= k;j++)
        {
            // if(mp[j].empty() && !mp[j - t[i]].empty())
            // {
            //     mp[j] = mp[j - t[i]];
            //     mp[j].push_back(t[i]);
            // }
            if(dp[j - t[i]] && dp[j] == 0)
            {
                dp[j] = 1;
                pre[j] = t[i];
            }
        }
    }

    debugarr(t);

    auto path = [&](int val) -> vector<i64>
    {
        vector<i64> p;
        int cur = val;
        while(cur > 0 && pre[cur] != -1)
        {
            p.push_back(vis[pre[cur]]);
            cur -= pre[cur];
        }
        return p;
    };

    if(dp[k])
    {
        for(i64 k : path(k))
            cout << k;
        cout << "\n";
        return;
    }

    debugarr(t);

    int f = 0;
    for (int i = 0; i <= t.size() - 1;i++)
    {
        i64 cur = t[i];
        i64 up = max((k - 2500) / cur, 0ll);
        i64 rem = k - cur * up;
        while(rem > 2500)
            rem -= cur, up++;
        
        while(rem >= 0)
        {
            if(dp[rem])
            {
                debug("!", cur, rem);
                // debugarr(mp[rem]);
                // auto &vec = mp[cur];
                // assert(vec.size() == 1);
                // debugarr(vec);
                debug(vis[cur]);
                f = 1;
                for (int j = 0; j < up;j++)
                    cout << vis[cur];

                for(i64 k : path(rem))
                    cout << k;
                cout << "\n";
                return;
            }
            rem -= cur;
            up++;
        }
    }
    // assert(f);
    cutline
    // debug(dp[k]);
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    // sieve(1e5);
    // debugarr(primes);
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}