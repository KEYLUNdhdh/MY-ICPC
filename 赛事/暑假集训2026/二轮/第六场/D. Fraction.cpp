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

i128 abs(i128 x)
{
    return x < 0 ? -x : x;
}

i128 gcd(i128 a, i128 b) 
{
    a = abs(a);
    b = abs(b);
    while (b)
    {
        i128 t = a % b;
        a = b;
        b = t;
    }
    return a;
}

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
    int n;
    cin >> n;
    vector<vector<Frac>> a;
    char c;
    Frac ans;
    for (int i = 0; i < n;i++)
    {
        cin >> c;
        if(c == '(')
            a.emplace_back();
        else if(c >= '1' && c <= '9')
        {
            Frac tmp{c - '0'};
            if(a.empty())
            {
                cout << -1;
                return;
            }

            a.back().push_back(tmp);
        }
        else
        {
            if(a.empty() || a.back().size() != 3)
            {
                cout << -1;
                return;
            }

            auto v = a.back();
            a.pop_back();

            Frac x, y, z;
            x = v[0], y = v[1], z = v[2];
            Frac k = x + y / z;
            if(a.empty())
            {
                if(i == n - 1)
                    ans = k;
                else
                {
                    cout << -1;
                    return;
                }
            }
            else
                a.back().push_back(k);
        }
    }
    if(!a.empty())    
    {
        cout << -1;
        return;
    }
    cout << ans.num << " " << ans.den;
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