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

constexpr i64 MOD = 998244353, INF = 2e18;
constexpr ld eps = 1e-12;
constexpr ld PI = 3.1415926535897932384l;

using point_t = ld;

template<typename T> 
struct point
{
    T x, y;
    int id;
    bool operator==(const point &a) const {return (abs(x - a.x) < eps && abs(y - a.y) < eps);}
    point operator+(const point &a) const { return {x + a.x, y + a.y}; }
    point operator-(const point &a) const { return {x - a.x, y - a.y}; }
    point operator-() const { return {-x, -y}; }
    point operator*(const T k) const { return {k * x, k * y}; }
    point operator/(const T k) const { return {x / k, y / k}; }
    T operator*(const point &a) const { return x * a.x + y * a.y; }
    T operator^(const point &a) const { return x * a.y - y * a.x; }
    int toleft(const point &a) const { const auto t = (*this) ^ a; return (t > eps) - (t < -eps);}
    T len2() const { return (*this) * (*this); }
    T dis2(const point &a) const { return (a - (*this)).len2(); }

    ld len() const { return sqrtl(len2()); }
    ld dis(const point &a) const { return sqrtl(dis2(a)); }
    ld ang(const point &a) const { return acosl(max(-1.0l, min(1.0l, ((*this) * a) / (len() * a.len())))); }
    point rot(const ld rad) const { return {x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)}; }
    point rot(const ld cosr, const ld sinr) const { return {x * cosr - y * sinr, x * sinr + y * cosr}; }
};

using Point = point<point_t>;

template<typename T>
struct line
{
    point<T> p, v;
    line(point<T> p = {0,0}, point<T> v = {0,0}) : p(p), v(v) {}
    
    bool operator==(const line &a) const { return v.toleft(a.v) == 0 && v.toleft(p - a.p) == 0; }
    int toleft(const point<T> &a) const { return v.toleft(a - p); }

    // using ld
    point<T> inter(const line &a) const { return p + v * ((a.v ^ (p - a.p)) / (v ^ a.v)); }
    ld dis(const point<T> &a) const { return abs(v ^ (a - p)) / v.len(); }
    point<T> proj(const point<T> &a) const { return p + v * ((v * (a - p)) / (v * v)); }
};

using Line = line<point_t>;


void solve()
{
    i64 n, m, a, b;cin >> n >> m >> a >> b;
    vector<Point> A(n + 1, {0, 0}), B(m + 1, {0, 0});
    vector<i64> l(m + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> A[i].y, A[i].x = a, A[i].id = i;
    for (int i = 1; i <= m;i++)
        cin >> B[i].y, B[i].x = b, B[i].id = i;
    for (int i = 1; i <= m;i++)
        cin >> l[i];

    sort(A.begin() + 1, A.end(), [](const Point &p, const Point &q) {return p.y < q.y - eps;});
    sort(B.begin() + 1, B.end(), [](const Point &p, const Point &q) {return p.y < q.y - eps;});

    ld mindis = 2e18;
    pii ans;
    for (int i = 1; i <= m;i++)
    {
        Line line{{0, 0}, B[i]};
        ld dist = l[i];
        auto it = partition_point(A.begin() + 1, A.end(), [&](Point &a) { return (line.toleft(a)) == -1; });
        int idx = it - A.begin();
        Point p1 = A[idx];
        if(line.toleft(p1) == 0)
        {
            dist += B[i].dis({0, 0});
            if(dist - mindis <= -eps)
            {
                mindis = dist;
                ans = {p1.id, B[i].id};
            }
        }
        else
        {
            dist += p1.dis({0, 0}) + p1.dis(B[i]);
            if(dist - mindis <= -eps)
            {
                mindis = dist;
                ans = {p1.id, B[i].id};
            }

            dist = l[i];
            if(idx > 1)
            {
                idx--;
                p1 = A[idx];
                dist += p1.dis({0, 0}) + p1.dis(B[i]);
                if(dist - mindis <= -eps)
                {
                    mindis = dist;
                    ans = {p1.id, B[i].id};
                }
            }
        }
    }

    cout << ans.first << " " <<  ans.second;
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
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}