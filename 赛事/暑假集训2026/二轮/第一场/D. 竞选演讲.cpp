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

template<typename T> 
struct point
{
    T x, y;
    bool operator==(const point &a) const {return (abs(x - a.x) == 0 && abs(y - a.y) == 0);}
    point operator+(const point &a) const { return {x + a.x, y + a.y}; }
    point operator-(const point &a) const { return {x - a.x, y - a.y}; }
    point operator-() const { return {-x, -y}; }
    point operator*(const T k) const { return {k * x, k * y}; }
    T operator*(const point &a) const { return x * a.x + y * a.y; }
    T operator^(const point &a) const { return x * a.y - y * a.x; }
    int toleft(const point &a) const { const auto t = (*this) ^ a; return (t > 0) - (t < 0);}
    T len2() const { return (*this) * (*this); }
    T dis2(const point &a) const { return (a - (*this)).len2(); }

};

using Point = point<point_t>;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<Point> pts(n);
    for (int i = 0; i < n;i++)
        cin >> pts[i].x >> pts[i].y;

    auto nxt = [&](int idx) -> int
    {
        if(idx == n - 1)
            return 0;
        return idx + 1;
    };

    i64 calc = 0;
    for (int i = 0; i < n;i++)
    {
        Point cur = pts[i];
        int nx = nxt(i);
        Point n = pts[nx];
        calc += abs(cur.x - n.x) + abs(cur.y - n.y);
        // debug(i, nx, calc);
    }

    debug(calc);

    map<i64, vector<i64>> xtoy, ytox;
    for (int i = 0; i < m;i++)
    {
        i64 x, y;
        xtoy[x].push_back(y);
        ytox[y].push_back(x);
    }

    vector<int> dist;
    int s = rnd() % n;
    i64 curdis = 0;
    while(dist.size() <= n)
    {
        Point cur = pts[s];
        int nx = nxt(s);
        Point n = pts[nx];
        if(cur.x == n.x)
        {
            i64 lb = min(cur.y, n.y), ub = max(cur.y, n.y);
            if(xtoy[cur.x].empty())
            {
                curdis += ub - lb;
                continue;
            }
            auto l = 
        }
    }
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