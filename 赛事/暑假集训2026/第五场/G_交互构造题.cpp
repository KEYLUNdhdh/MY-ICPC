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

// 2 的 16 次为 65536， O(n^2) 风险很大
// 第一个元素和所有其它元素异或
// 若 n - 1 个异或都不同，数组中所有元素都不同。
// 怎么整？
// 这里感觉挺难啊。
// 想下，这时候肯定有一个 n - 1 的掩码，只要找到它就行
// 或者我们找到 0 也可以。
// 尝试使用或？
// 感觉 n - 1 的时候一定能凑出相邻奇数吧
// 偶对了，必然存在 1 和 2，我们二次定位即可


// 如果有相同的，与一下就可以求出原始值，整个数组都知道了。
void solve()
{
    int n;
    cin >> n;
    vector<pii> q(n + 1, {0, 0});
    auto queryXOR = [](int i, int j) -> int
    {
        cout << "XOR " << i << " " << j << endl;
        int res;
        cin >> res;
        return res;
    };

    auto queryOR = [](int i, int j) -> int
    {
        cout << "OR " << i << " " << j << endl;
        int res;
        cin >> res;
        return res;
    };
    auto queryAND = [](int i, int j) -> int
    {
        cout << "AND " << i << " " << j << endl;
        int res;
        cin >> res;
        return res;
    };

    auto pr = [](vector<int> a) -> void
    {
        cout << "! ";
        for (int i = 1; i < a.size();i++)
            cout << a[i] << " ";
        cout << endl;
        return;
    };

    map<int, vector<int>> mp;
    mp[0].push_back(1);
    q[1].second = 1;
    for (int i = 2; i <= n;i++)
    {
        q[i].first = queryXOR(1, i);
        q[i].second = i;
        mp[q[i].first].push_back(i);
    }

    if(mp.size() < n)
    {
        vector<int> ans(n + 1, 0);
        vector<int> pos;
        for(auto &[val, vec] : mp)
        {
            if(vec.size() >= 2)
            {
                pos = vec;
                break;
            }
        }

        int l = pos[0], r = pos[1];
        ans[l] = ans[r] = queryAND(l, r);
        for (int i = 1; i <= n;i++)
        {
            if(i == l || i == r)
                continue;
            ans[i] = ans[l] ^ q[l].first ^ q[i].first;
        }
        pr(ans);
        return;
    }

    // sort(q.begin() + 1, q.end());
    int l = -1, r = -1;
    for (int i = 1; i <= n;i++)
    {
        if(q[i].first == 1)
            l = q[i].second;
        else if(q[i].first == 2)
            r = q[i].second;
    }
    // assert(l != -1 && r != -1);

    int tmp = queryAND(1, l);
    int tmp2 = queryAND(1, r);
    map<int, int> mpp;
    mpp[tmp]++, mpp[tmp + 1]++, mpp[tmp2]++, mpp[tmp2 + 2]++;
    vector<int> ans(n + 1, 0);
    for(auto &[val ,cnt] : mpp)
        if(cnt == 2)
            ans[1] = val;

    // ans[l] = tmp, ans[r] = tmp + 1;
    for (int i = 2; i <= n;i++)
        ans[i] = ans[1] ^ q[1].first ^ q[i].first;
    pr(ans);
    return;
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}

// 2 5 4 3 3 3
// 5 4 3 2 1 0
// 7 6 5 4 3 2 1 0