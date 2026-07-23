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
using i128 = long long;
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

struct Frac
{
    i128 num;
    i128 den;
    
    Frac(i128 num_ = 0, i128 den_ = 1) : num(num_), den(den_)
    {
        normalize();
    }

    void normalize() 
    {
        if (den < 0)
        {
            num = -num;
            den = -den;
        }

        i128 g = gcd(num, den);

        if (g)
        {
            num /= g;
            den /= g;
        }
    }

    explicit operator ld() const
    {
        return (ld)num / (ld)den;
    }

    Frac &operator+=(const Frac &rhs)
    {
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        normalize(); 
        return *this;
    }
    Frac &operator-=(const Frac &rhs)
    {
        num = num * rhs.den - rhs.num * den;
        den *= rhs.den;
        normalize(); 
        return *this;
    }
    Frac &operator*=(const Frac &rhs)
    {
        num *= rhs.num;
        den *= rhs.den;
        normalize(); 
        return *this;
    }
    Frac &operator/=(const Frac &rhs)
    {
        num *= rhs.den;
        den *= rhs.num;
        if(den < 0)
        {
            num = -num;
            den = -den;
        }
        normalize();
        return *this;
    }
    friend Frac operator+(Frac lhs, const Frac &rhs)
    {
        return lhs += rhs;
    }
    friend Frac operator-(Frac lhs, const Frac &rhs)
    {
        return lhs -= rhs;
    }
    friend Frac operator*(Frac lhs, const Frac &rhs)
    {
        return lhs *= rhs;
    }
    friend Frac operator/(Frac lhs, const Frac &rhs)
    {
        return lhs /= rhs;
    }
    friend Frac operator-(const Frac &a)
    {
        return Frac(-a.num, a.den);
    }
    friend bool operator==(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den == rhs.num * lhs.den;
    }
    friend bool operator!=(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den != rhs.num * lhs.den;
    }
    friend bool operator<(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den < rhs.num * lhs.den;
    }
    friend bool operator>(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den > rhs.num * lhs.den;
    }
    friend bool operator<=(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den <= rhs.num * lhs.den;
    }
    friend bool operator>=(const Frac &lhs, const Frac &rhs) 
    {
        return lhs.num * rhs.den >= rhs.num * lhs.den;
    }
    friend ostream &operator<<(ostream &os, Frac x)
    {
        i128 g = gcd(x.num, x.den);
        if(x.den == g)
            return os << x.num / g;
        else
            return os << x.num / g << "/" << x.den / g;
    }
};

void solve()
{
    i128 px, py, qx, qy;
    cin >> px >> py >> qx >> qy;
    i128 ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    if(py == qy)
    {
        if(ay != by)
        {
            cout << "Yes\n";
            return;
        }
        else
        {
            if(px + qx == ax + bx)
                cout << "Yes\n";
            else
                cout << "No\n";
        }
        return;
    }
    Frac k1((qx - px), (py - qy));
    Frac k2((bx - ax), (ay - by));

    if(k1 != k2)
    {
        cout << "Yes\n";
        return;
    }
    else
    {

        if(px + qx == ax + bx)
        {
            if(py + qy == ay + by)
                cout << "Yes\n";
            else
                cout << "No\n";
            return;
        }
        Frac k3(py + qy - ay - by, px + qx - ax - bx);
        if(k3 != k2)
            cout << "No\n";
        else
            cout << "Yes\n";
    }
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();

    return 0;
}