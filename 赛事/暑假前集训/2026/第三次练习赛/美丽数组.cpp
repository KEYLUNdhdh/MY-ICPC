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
using u32 = unsigned int;
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

void solve()
{
    int n, q;
    cin >> n >> q;

    // sieve(1e5);
    // debug(primes.size())
    vector<int> a(n + 1, 0);
    map<int, vector<int>> mp;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        int num = a[i];
        if(!mp[a[i]].empty())
            continue;
        for (int k = 2; k * k <= num;k++)
        {
            if(num % k == 0)
            {
                mp[a[i]].push_back(k);
                while(num % k == 0)
                    num /= k;
            }
        }
        
        if(num != 1)
            mp[a[i]].push_back(num);
    }

    vector<int> cnt(1e5 + 1, 0);
    vector<vector<i64>> f(n + 1, vector<i64>(32, 0));
    int l = 1;
    for (int r = 1; r <= n;r++)
    {
        int num = a[r];
        for(int k : mp[num])
        {
            cnt[k]++;
            if(cnt[k] >= 2)
            {
                while(cnt[k] >= 2)
                {
                    for(int j : mp[a[l]])
                        cnt[j]--;
                    f[l][0] = r - 1;
                    l++;
                }
            }
        }
    }

    while(l <= n)
    {
        f[l][0] = n;
        l++;
    }

    // debug(l)
    for (int j = 1; j <= 31;j++)
        for (int i = 1; i <= n;i++)
        {
            // f[i][j] = f[f[i][j - 1] + 1][j - 1];
            if(f[i][j - 1] == n)
                f[i][j] = n;
            else
                f[i][j] = f[f[i][j - 1] + 1][j - 1];
        }

    // debug(l)
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        i64 ans = 0;
        int cur = l;
        for (int i = 31; i >= 0; i--)
        {
            if (f[cur][i] < r)
            {
                cur = f[cur][i] + 1;
                ans += pow(2, i);
            }
        }
        cout << ans + 1 << "\n";
    }   
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