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

// 怎么感觉是超级无敌大贪心
// 那我问题，如果是第一个窗口，我是不是怎么说也得选最小的
// 没毛啊
// 那么后面的是不是独立了，对的
template<typename T,typename F>
struct STable
{
    int n;
    int maxlog;
    vector<vector<T>> st;
    F func;
    //a 1 - index
    STable(const vector<T>& a,const F& f) : func(f)
    {
        n = a.size() - 1;
        maxlog = __lg(n) + 1;
        st.assign(n + 1, vector<T>(maxlog));
        for (int i = 1; i <= n;i++)
            st[i][0] = a[i];
        for (int j = 1; j < maxlog;j++)
        {
            int len = 1 << (j - 1);
            for (int i = 1;i <= n - (1 << j) + 1;i++)
                st[i][j] = func(st[i][j - 1], st[i + len][j - 1]);
        }
    }
    inline T query(int l,int r) const
    {
        if (l > r) 
            swap(l, r);
        int k = __lg(r - l + 1);
        return func(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

// 这题感觉是他妈 adhoc 啊
// 贪心加动态规划，无敌了
// 欧耶我不是小猪
void solve()
{
    int m;
    cin >> m;
    string s;
    cin >> s;
    int n = s.size();
    s = "*" + s;

    // for (int i = 1; i <= m - 1;i++)
    //     s += ('z' + 1);
    // n = n + m - 1;
    debug(s);
    // vector<char> a(n + 1, '\0');
    // for (int i = 1; i <= n;i++)
    //     a[i] = s[i];
    // STable st(a, [](char p, char q){ return min(p, q); });
    deque<int> minn;
    // int cur = 0;
    vector<int> minans(n + 1, 0);
    char minchar = 'z' + 1;
    // debug(s);
    vector<int> vis(n + 1, 0);

    
    for (int i = 1; i <= n;i++)
    {

        while(!minn.empty() && s[minn.back()] >= s[i])
            minn.pop_back();
        minn.push_back(i);
        chmin(minchar, s[i]);
        debug(i, s[i]);
        debugarr(minn);
        while(!minn.empty() && i - m >= minn.front())
            minn.pop_front();
            
        if(i - m >= 0)
            minans[i] = minn.front();
    }

    debug(n);
    
    vector<int> ans;
    vector<int> pre(n + 1, 0);
    // for (int i = n + 1; i <= m - 1;i++)
    // {
    //     minans
    // }
    for (int i = 1; i <= n; i++)
    {
        if (i < m)
            continue;

        int p = pre[i - 1];
        debug(i, p, m);
        if (p + m <= i)
        {
            debug(i, minans[i]);
            pre[i] = minans[i];
            ans.push_back(minans[i]);
            vis[minans[i]] = 1;
        }
        // else if(minans[i] < s[p])
        // {
        //     pre[i] = minans[i];
        //     ans.push_back(minans[i]);
        // }
        else
        {
            pre[i] = pre[i - 1];
        }
        cutline
    }

    string res = "";
    for(int k : ans)
        res += s[k];
    sort(res.begin(), res.end());
    minchar = res.back();
    for (int i = 1; i <= n;i++)
    {
        if(!vis[i] && s[i] < minchar)
            res += s[i], vis[i] = 1;
    }

        // int st = pre[n] + 1;
        // debug(minchar, st);
        // for (int i = st; i <= n;i++)
        // {
        //     debug(s[i]);
        //     if(s[i] <= minchar)
        //         res += s[i];
        // }
        // debugarr(pre);
        // debugarr(ans);
    sort(res.begin(), res.end());
    cout << res;

    // string ans;
    // int i = m;
    // int lim = m;
    // debug(minchar);
    // while (i <= n)
    // {
    //     if(i == lim)
    //     {
    //         int idx = minans[i];
    //         debug(i, idx, s[idx]);
    //         // if(vis[idx])
    //         // {
    //         //     i++;
    //         //     continue;
    //         // }
    //         vis[idx] = 1;
    //         lim = idx + m;
    //         ans += s[idx];
    //     }
    //     else
    //     {
    //         int idx = minans[i];
    //         debug(i, idx, s[idx]);
    //         if(vis[idx])
    //         {
    //             i++;
    //             continue;
    //         }
    //         if(s[idx] == minchar)
    //         {   
    //             vis[idx] = 1;
    //             ans += s[idx];
    //             lim = idx + m;
    //         }
    //     }
    //     i++;
    //     // if(i > n)
    //     //     break;        
    // }
    // debugarr(minans);
    // sort(ans.begin(), ans.end());

    // cout << ans;
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