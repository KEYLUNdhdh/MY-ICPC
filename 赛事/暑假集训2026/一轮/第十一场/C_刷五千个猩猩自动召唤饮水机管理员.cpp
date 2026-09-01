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
using point_t = i64;

struct Point
{
    i64 x, y;
    bool operator<(const Point &a) const {if(abs(x - a.x) <= 0) return y < a.y ; return x < a.x ;}
    Point operator-(const Point &a) const { return {x - a.x, y - a.y}; }
    i64 operator*(const Point &a) const { return x * a.x + y * a.y; }
    i64 len2() const { return (*this) * (*this); }
    i64 dis2(const Point &a) const { return (a - (*this)).len2(); }
};


/*
p q 内部的点的距离 与 p q 之间的点的距离 每个都不一样
那么考虑对每个点画圆？
对于 u 这个点，我画一个 r 的圆
如果有多余 1 个的点在上面，是不是这些点一定属于一个集合，没毛病,有毛病，可能有空集
理论上来说，全都划到一个集合就行，但是非空，我们考虑极端情况。
如果说 我们只分出一个点的方法是无解的，那么至少要分两个点。
猜想：这时候的图是高度对称的，对于每个距离，它至少要出现两次。这时候 n >= 4
我们这么分，把距离最远的两个点分到一起，剩下的分一块
可以啊，感觉没毛
这个猜想在 13 错了
感觉可以推广？我们看，对于一个点，它的最大距离出现了多少次，就我们的集合大小就是多少。
这个猜想也在 13 错了
难不成是 n = 3 的情况？
不对啊，等边三角形不能作为合法输入
有什么图能卡我这个？
菊花图没问题，中心对称没问题
轴对称？
太变态了

*/

void solve()
{
    int n;
    cin >> n;

    map<Point, map<i64, int>> mp;
    map<i64, i64> cnt;
    vector<Point> pts(n + 1, {0, 0});
    for (int i = 1; i <= n;i++)
        cin >> pts[i].x >> pts[i].y;

    for (int i = 1; i <= n;i++)
    {
        for (int j = 1 + i; j <= n;j++)
        {
            Point a = pts[i], b = pts[j];
            i64 dis = a.dis2(b);
            mp[a][dis]++;
            mp[b][dis]++;
            cnt[dis]++;
        }
    }

    for (int i = 1; i <= n;i++)
    {
        Point cur = pts[i];
        int f = 1;
        for(auto &[dis, count] : mp[cur])
        {
            if(count < cnt[dis])
            {
                f = 0;
                break;
            }
        }
        if(f)
        {
            cout << 1 << "\n";
            cout << i;
            return;
        }
    }

    // 没return说明图高度对称。
    i64 maxx = 0;
    Point cur = pts[1];
    vector<int> ans;
    // ans.push_back(1);
    for (int i = 2; i <= n;i++)
    {
        Point p = pts[i];
        i64 dist = p.dis2(cur);
        debug(dist);
        if(dist > maxx)
        {
            debug(dist);
            debugarr(ans);
            ans.clear();
            maxx = dist;
            ans.push_back(i);
            debugarr(ans);
        }
        else if(dist == maxx)
            ans.push_back(i);
            
    }

    // 好吧，错了
    // 继续刚才的猜想
    cout << ans.size() + 1<< "\n";
    cout << 1 << " ";
    for (int k : ans)
        cout << k << " ";
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