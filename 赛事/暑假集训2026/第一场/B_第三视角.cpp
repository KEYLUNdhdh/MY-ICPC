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
constexpr i64 MOD = 998244353, INF = 1e9;
typedef pair<int, int> pii;
constexpr ld eps = 1e-18;
constexpr ld PI = 3.1415926535897932384l;

using point_t = i128;

template<typename T> 
struct point
{
    T x, y;
    bool operator==(const point &a) const {return (abs(x - a.x) < eps && abs(y - a.y) < eps);}
    bool operator<(const point &a) const {if(abs(x - a.x) <= eps) return y < a.y - eps; return x < a.x - eps;}
    bool operator>(const point &a) const { return !(*this < a || *this == a); }
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



ostream &operator<<(ostream &os, i128 n) {
    string s;
    int f = 0;
    if(n == 0)
        s = "0";
    if(n < 0)
    {
        f = 1;
        n = -n;
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    if(f)
        s = '-' + s;
    return os << s;
}

istream &operator>>(istream &is,i128& n)
{
    n = 0;
    string s;
    is >> s;
    int sign = 1, start = 0;
    if(s[0] == '-')
    {
        sign = -1;
        start = 1;
    }
    for (int i = start; i < s.size();i++)
    {
        n = n * 10 + s[i] - '0';
    }
    n *= sign;
    return is;
}

i128 abs(i128 t)
{
    if(t < 0)
        return -t;
    return t;
}

i128 gcd(i128 a, i128 b) 
{
    return b ? gcd(b, a % b) : a;
}

struct exgcd
{
    struct result
    {
        i128 x, y, g;
        bool f;
    };
    static result solve(i128 a,i128 b,i128 c)
    {
        i128 x = 1, y = 0, g = a;
        function<void(i128, i128)> dfs = [&](i128 a, i128 b)
        {
            if(b == 0)
            {
                g = a;
                x = 1, y = 0;
                return;
            }
            dfs(b, a % b);
            i128 tp = x;
            x = y;
            y = tp - (i128)(a / b) * y;
        };
        dfs(a, b);
        if(g < 0)
        {
            g = -g;
            x = -x;
            y = -y;
        }
        if(c % g)
        {
            return {0, 0, g, false};
        }
        i128 factor = c / g;
        return {x * factor, y * factor, g, true};
    }
    static pair<i64,i64> minx(i64 a,i64 b,i64 c)
    {
        result res = solve(a, b, c);
        if(!res.f)
            return {-1, -1};
        if(c == 0)
            return {0, (i64)res.g};
        i64 bg = b / res.g;   
        if(bg < 0)
            bg = -bg;
        i64 k = -res.x / bg;
        while(res.x + k * bg < 0)
            k++;
        while(res.x + (k - 1) * bg >= 0)
            k--;
        i64 x = res.x + k * bg;
        return {x, (i64)res.g};
    }
};

void solve()
{
    Point a, b;
    cin >> a.x >> a.y >> b.x >> b.y;
    // Point l = b - a;
    // if(l.x == 0)
    // {
    //     cout << a.x + 1 << " " << a.y << "\n";
    //     return;
    // }
    // else if(l.y == 0)
    // {
    //     cout << a.x << " " << a.y + 1 << "\n";
    // }
    // else if(l.x > 0 && l.y > 0)
    // {
    //     Point ex{1, 0};
    //     Point ey{0, 1};
    //     i64 disx = ex * l;
    //     i64 disy = ey * l;
    //     if(disx > disy)
    //         cout << a.x + 1 << " " << a.y << "\n";
    //     else
    //         cout << a.x << " " << a.y + 1 << "\n";
    // }
    // else if(l.x > 0 && l.y < 0)
    // {
    //     Point ex{1, 0};
    //     Point ey{0, -1};
    //     i64 disx = ex * l;
    //     i64 disy = ey * l;
    //     if(disx > disy)
    //         cout << a.x + 1 << " " << a.y << "\n";
    //     else
    //         cout << a.x << " " << a.y + 1 << "\n";
    // }
    // else if(l.x < 0 && l.y > 0)
    // {
    //     Point ex{-1, 0};
    //     Point ey{0, 1};
    //     i64 disx = ex * l;
    //     i64 disy = ey * l;
    //     if(disx > disy)
    //         cout << a.x + 1 << " " << a.y << "\n";
    //     else
    //         cout << a.x << " " << a.y + 1 << "\n";
    // }
    // else
    // {
    //     Point ex{-1, 0};
    //     Point ey{0, -1};
    //     i64 disx = ex * l;
    //     i64 disy = ey * l;
    //     if(disx > disy)
    //         cout << a.x + 1 << " " << a.y << "\n";
    //     else
    //         cout << a.x << " " << a.y + 1 << "\n";
    // } 
    i128 A = a.y - b.y;
    i128 B = b.x - a.x;
    i128 aa = A < 0 ? -A : A;
    i128 bb = B < 0 ? -B : B;
    i128 g = gcd(aa, bb);

    A /= g;
    B /= g;
    int swx = 1, swy = 1;
    if(A < 0)
        swx = -1;
    if(B < 0)
        swy = -1;
    A = A < 0 ? -A : A;
    B = B < 0 ? -B : B;
    auto [x, y, gg, f] = exgcd::solve(A, B, 1);
    cout << x * swx + a.x << " " << y * swy + a.y << "\n";
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0  );
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}