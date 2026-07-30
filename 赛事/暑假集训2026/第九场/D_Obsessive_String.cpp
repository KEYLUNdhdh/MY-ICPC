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
// bool ST;

constexpr i64 MOD = 1e9 + 7, INF = 1e9;

struct KMP
{
    vector<int> pi;
    void build(const string& p)
    {
        int m = p.size();
        pi.assign(m, 0);
        for (int i = 1, j = 0; i < m;i++)
        {
            while(j > 0 && p[i] != p[j])
                j = pi[j - 1];
            if(p[i] == p[j])
                j++;
            pi[i] = j;
        }
    }

    vector<int> match(const string& s, const string& p)
    {
        int n = s.size();
        int m = p.size();
        vector<int> res;
        for (int i = 0, j = 0; i < n;i++)
        {
            while(j > 0 && s[i] != p[j])
                j = pi[j - 1];
            if(s[i] == p[j])
                j++;
            if(j == m)
            {
                res.push_back(i - m + 2);
                j = pi[j - 1];
            }
        }
        return res;
    }
};

void solve()
{
    string s;
    cin >> s;
    string p;
    cin >> p;

    KMP kmp;
    kmp.build(p);
    int plen = p.size();
    vector<int> res = kmp.match(s, p);
    // debugarr(res) 
    int n = s.size();
    s = s + "*";
    vector<int> k(n + 1, -1);
    int pre = -1;
    int cur;
    if(!res.empty())
    {
        for (int i = 0; i < res.size();i++)
        {
            cur = res[i];
            for (int j = max(0, pre + plen - 1); j <= cur + plen - 2 && j <= n;j++)
                k[j] = pre;
            pre = cur;
        }
        //debug(cur)
        for (int j = cur + plen - 1; j <= n;j++)
            k[j] = cur;
    }
    // debugarr(k)

    vector<i64> dp(n + 1, 0);
    vector<i64> prefix(n + 1, 0);
    vector<i64> pprefix(n + 1, 0);

    for (int i = 1; i <= n;i++)
    {
        int pre = k[i];
        if(pre == -1)
        {
            prefix[i] = (prefix[i - 1] + dp[i]) % MOD;
            pprefix[i] = (pprefix[i - 1] + prefix[i]) % MOD;
            continue;
        }
        dp[i] = (pprefix[pre - 1] + pre) % MOD;
        prefix[i] = (prefix[i - 1] + dp[i]) % MOD;
        pprefix[i] = (pprefix[i - 1] + prefix[i]) % MOD;

    }
    // debugarr(dp)
    cout << prefix[n];
}

// bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}