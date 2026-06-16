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
namespace sieve
{
    int n;
    vector<int> primes;
    vector<int> phi, mu, vis;

    void init(int n_)
    {
        n = n_;
        primes.clear();
        phi.assign(n + 1, 0);
        mu.assign(n + 1, 0);
        vis.assign(n + 1, 0);
    }

    void run()
    {
        phi[1] = 1;
        mu[1] = 1;
        for (int i = 2; i <= n;i++)
        {
            if(!vis[i])
            {
                primes.push_back(i);
                phi[i] = i - 1;
                mu[i] = -1;
            }

            for(int p : primes)
            {
                if(1ll * i * p > n)
                    break;

                int x = i * p;
                vis[x] = 1;

                if(i % p == 0)
                {
                    phi[x] = phi[i] * p;
                    mu[x] = 0;
                    break;
                }
                else
                {
                    phi[x] = phi[i] * (p - 1);
                    mu[x] = -mu[i];
                }
            }
        }
    }
}

void solve()
{
    int n;
    cin >> n;

    sieve::init(n);
    sieve::run();

    for (int i = 1; i <= n;i++)
        cout << sieve::phi[i] << " ";
    cout << "\n";
    for (int i = 1; i <= n;i++)
        cout << sieve::mu[i] << " ";
    cout << "\n";
    vector<i64> sig(n + 1, 0), sig1(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j * i <= n;j++)
        {
            sig[j * i]++;
            sig1[j * i] += i;
        }
    }
    for (int i = 1; i <= n;i++)
        cout << sig[i] << " ";
    cout << "\n";
    for (int i = 1; i <= n;i++)
        cout << sig1[i] << " ";
    cout << "\n";
    vector<i64> f(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j * i <= n;j++)
        {
            f[i * j] += sieve::phi[i] * sieve::mu[i] * sig1[j];
        }
    }
    for (int i = 1; i <= n;i++)
        cout << f[i] << " ";
    
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