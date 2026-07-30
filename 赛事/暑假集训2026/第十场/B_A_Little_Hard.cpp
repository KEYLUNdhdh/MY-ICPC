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

constexpr i64 MOD = 998244353, INF = 1e9;


// 想让 x -> y
// x -> 1 y -> -1
// 变成最大子段和的问题
// 对每个潜在的映射做一次最大字段和？
// 加上剪枝会好点吗？
// 剪枝不够充分，但是想法对了。?
// 为什么又WA了？
// 以后再用map我吃屎
const int MAXN = 2e6 + 1;
const int offset = 1e6;
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1, 0);
    vector<int> mp(MAXN, 0);
    vector<int> vis(MAXN, 0);

    vector<vector<int>> pos(MAXN);
    int curans = 0;

    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        mp[a[i] + offset]++;
        chmax(curans, mp[a[i] + offset]);
        pos[a[i] + offset].push_back(i);
    }

    if(k == 0)
    {
        cout << curans;
        return;
    }

    auto kadane = [&](int plus, int del) -> int
    {
        i64 maxx = -1e9;
        i64 now = 0;

        vector<int> p = pos[plus + offset], d = pos[del + offset];
        int i = 0, j = 0;
        while(i < p.size() && j < d.size())
        {
            if(p[i] < d[j])
            {
                now++;
                i++;
            }
            else
            {
                now--;
                j++;
            }
            chmax(maxx, now);
            if(now < 0)
                now = 0;
        }

        while(i < p.size())
        {
            now++, i++;
            chmax(maxx, now);
        }

        while(j < d.size())
        {
            now--, j++;
            chmax(maxx, now);
            if(now < 0)
                now = 0;
        }

        // for (int i = 1; i <= n;i++)
        // {
        //     if(a[i] == plus)
        //         now++;
        //     else if(a[i] == del)
        //         now--;
        //     chmax(maxx, now);
        //     if(now < 0)
        //         now = 0;
        // }
        return maxx;
    };

    for (int i = 1; i <= n;i++)
    {
        int val = a[i];
        int cnt = mp[val + offset];
        if(cnt != 0 && !vis[val + offset] && val + k + offset <= 2e6 && val + k + offset >= 0)
        {
            if(mp[val + k + offset] == 0)
                continue;

            // mp[val + offset] = 0;
            vis[val + offset] = 1;
            int ub = cnt + mp[val + k + offset];
            if (ub <= curans)
                continue;

            // int res = kadane
            chmax(curans, kadane(val, val + k) + mp[val + k + offset]);
        }
    }
        // for (auto &[val, cnt] : mp)
        // {
        //     // chmax(curans, cnt);
        //     if (mp.find(val + k) == mp.end())
        //         continue;
        //     else
        //     {
        //         // debug(val)
        //         int ub = cnt + mp[val + k];
        //         if (ub <= curans)
        //             continue;

        //         // int res = kadane
        //         chmax(curans, kadane(val, val + k) + mp[val + k]);
        //     }
        // }

    cout << curans;
}

// bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}