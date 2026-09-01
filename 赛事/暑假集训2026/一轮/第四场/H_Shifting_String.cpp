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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

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


// 首先，我们每个下标属于不同的连通块。所以我们在连通块内考虑，每个连通块是一个子序列。
// 其次，每个连通块内的移动可以看成是一个字符串的循环位移。
// 然后求出连通块之间的操作次数的 lcm 即可
void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "*" + s;
    vector<int> p(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> p[i];

    vector<int> ans;
    vector<int> vis(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        if(vis[i])
            continue;

        vector<int> tmp;
        string k = "";
        int cur = i;
        while(!vis[cur])
        {
            vis[cur] = 1;
            tmp.push_back(cur);
            k += s[cur];
            cur = p[cur];
        }
        // debug(k)
        string m = k + k;
        // m.pop_back();
        KMP kmp;
        kmp.build(k);
        vector<int> res = kmp.match(m, k);
        // debugarr(res)
        ans.push_back(res[1] - 1);
    }

    i64 res = 1;
    for (int i = 0; i < ans.size();i++)
        res = res * ans[i] / gcd(res, ans[i]);

    cout << res << "\n";
    // debugarr(ans)

    //     cutline
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    // cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    // cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}