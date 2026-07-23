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
typedef tuple<int, int, int> piii;
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
			if(1ll * i * p > n)
				break;
			isPrime[i * p] = 0;
			if(i % p == 0)
				break;
		}
	}
}

const int MAXA = 1e6;
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    map<int, int> mp;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        int q = sqrt(a[i]);
        if(q * q == a[i])
        {
            cout << 1;
            return;
        }
        mp[a[i]]++;
    }

    for(auto &[val, cnt] : mp)
    {
        if(cnt >= 2)
        {
            cout << 2;
            return;
        }
    }

    map<int, int> id;
    int tot = 2;
    vector<vector<int>> adj(primes.size() + 2);
    for(int &k : primes)
        id[k] = tot++;

    vector<pii> tmp;
    for (int i = 1; i <= n; i++)
    {
        
        int num = a[i];
        for(int k : primes)
        {
            if(k * k > num)
                break;

            if(num % k == 0)
            {
                tmp.push_back({k, 0});
                while(num % k == 0)
                    num /= k, tmp.back().second++;
            }    
        }
        if(num != 1)
            tmp.push_back({num, 1});

        if(tmp.size() == 1)
        {
            int p = tmp[0].first;
            adj[1].push_back(id[p]);
            adj[id[p]].push_back(1);
        }
        else
        {
            int p1 = tmp[0].first, p2 = tmp[1].first;
            if(tmp[0].second % 2 && tmp[1].second % 2)
            {
                adj[id[p1]].push_back(id[p2]);
                adj[id[p2]].push_back(id[p1]);
            }
            else if(tmp[0].second % 2)
            {
                adj[1].push_back(id[p1]);
                adj[id[p1]].push_back(1);
            }
            else
            {
                adj[1].push_back(id[p2]);
                adj[id[p2]].push_back(1);
            }
        }
        tmp.clear();
    }

    vector<int> vis, dis;
    int len = INF;
    for (int s = 1; s <= 200;s++)
    {
        vis.assign(primes.size() + 2, 0);
        dis.assign(primes.size() + 2, 0);
        
        queue<pii> q;
        q.push({s, 0});
        vis[0] = 1;
        vis[s] = 1;
        while(!q.empty())
        {
            auto [u, p] = q.front();
            q.pop();
            for(int v : adj[u])
            {
                if(v == p)
                    continue;

                if(vis[v])
                    chmin(len, dis[v] + dis[u] + 1);
                else
                {
                    dis[v] = dis[u] + 1;
                    vis[v] = 1;
                    q.push({v, u});
                }
            }
        }
    }

    if(len == INF)
        cout << -1;
    else
        cout << len;
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    sieve(MAXA);
    while(T--)
        solve();

    return 0;
}