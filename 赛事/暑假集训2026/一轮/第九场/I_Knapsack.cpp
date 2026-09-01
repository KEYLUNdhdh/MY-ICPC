#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << endl; }
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

// 妈的怎么是 cnt 啊，看半天看错了
// 840
// 也就是说，我们的 lcm 是840
// 因为 cnt 很大，背包好像可以
// 等下我看看
// 应该用多重背包

void solve()
{
    i64 w;
    cin >> w;
    vector<i64> cnt(9, 0);
    i64 total = 0;
    for (i64 i = 1; i <= 8;i++)
    {
        cin >> cnt[i];
        i64 c = 840ll / i;
        i64 ge = cnt[i] / c;
        if(ge >= 1)
            ge--;
        total += ge;
        cnt[i] -= ge * c;
    }

    // debug(total)    
    // 我们只用凑 840 以内的
    // 不对，好像是 8 * 840
    // 为什么？
    const i64 MAXA = 20 * 840;
    vector<i64> dp(MAXA + 1, 0);
    vector<i64> item;
    for (i64 i = 1; i <= 8;i++)
    {
        i64 cur = cnt[i];
        for (i64 k = 1; k <= cur;k <<= 1)
        {
            item.push_back(k * i);
            cur -= k;
        }

        if(cur * i != 0)
            item.push_back(cur * i);
    }

    // debugarr(item)
    dp[0] = 1;
    for (i64 k : item)
    {
        for (i64 i = MAXA; i >= k; i--)
            if (dp[i - k])
                dp[i] = 1;
    }


    // for (int i = 0; i <= 300;i++)
    //     cerr << dp[i] << " ";
    i64 cc = w / 840ll;
    if(cc >= 1)
        cc -= 1;
    if(cc <= total)
    {
        w -= cc * 840ll;
    }
    else
    {
        w -= total * 840ll;
        cc = total;
    }
    i64 maxx = 0;
    chmin(w, MAXA);
    for (i64 i = w; i >= 0; i--)
    {
        if(dp[i])
        {
            maxx = i;
            // debug(maxx)
            break;
        }
    }   
    cout << cc * 840ll + maxx;
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