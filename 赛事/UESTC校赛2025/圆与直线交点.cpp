#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline {cerr << "----------------------\n";}

using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937 rnd(time(0));
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) // PII 
{
    return os << "(" << p.first << ", " << p.second << ")\n";
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) //vector
{
    os << "[";
    for (int i = 0; i < v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &d) //deque
{
    os << "[";
    for (int i = 0; i < d.size(); ++i)
    {
        if (i)
            os << ", ";
        os << d[i];
    }
    return os << "]\n";
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &v) //set
{
    os << "[";
    for (auto x = v.begin(); x != v.end(); x++)
    {
        if (x != v.begin())
            os << ", ";
        os << *x;
    }
    return os << "]\n";
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &v) //map
{
    os << " {";
    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it != v.begin())
            os << ", ";
        os << "(" << it->first << " -> " << it->second << ")"; //键值对
    }
    return os << "}\n";
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}
constexpr int MOD = 998244353, INF = 1e9;
struct BigInt
{
    vector<int> vec;
    int sign;
    BigInt(i64 x = 0)
    {
        if(x < 0)
            sign = -1, x = -x;
        else
            sign = 1;
        if(x == 0)
            vec.push_back(0);
        while(x)
        {
            vec.push_back(x % 10);
            x /= 10;
        }
    }
    BigInt(string s)
    {
        if(s.empty())
        {
            sign = 1;
            vec = {0};
            return;
        }
        if(s[0] == '-')
        {
            sign = -1;
            s = s.substr(1);
        }
        else
            sign = 1;
        for (int i = s.size() - 1; i >= 0;i--)
        {
            vec.push_back(s[i] - '0');
        }
        trim();
    }
    void trim()
    {
        while(vec.size() > 1 && vec.back() == 0)
            vec.pop_back();
        if(vec.size() == 1 && vec[0] == 0)
            sign = 1;
    }
    static bool abs_less(const BigInt& a,const BigInt &b)
    {
        if(a.vec.size() != b.vec.size())
            return a.vec.size() < b.vec.size();
        for (int i = a.vec.size() - 1; i >= 0;i--)
        {
            if(a.vec[i] != b.vec[i])
                return a.vec[i] < b.vec[i];
        }
        return false;
    }
    bool operator<(const BigInt& b) const
    {
        if(sign != b.sign)
            return sign < b.sign;
        if(sign == 1)
            return abs_less(*this, b);
        else
            return abs_less(b, *this);
    }
    bool operator>(const BigInt &b) const { return b < *this; }
    bool operator<=(const BigInt &b) const { return !(*this > b); }
    bool operator>=(const BigInt &b) const { return !(*this < b); }
    bool operator==(const BigInt &b) const { return (sign == b.sign && vec == b.vec); }
    bool operator!=(const BigInt &b) const { return !(*this == b); }
    static BigInt abs_add(const BigInt& a, const BigInt& b) {
        BigInt res;
        res.vec.clear();
        int t = 0;
        for (int i = 0; i < max(a.vec.size(), b.vec.size()) || t; i++) {
            int cur = t + (i < a.vec.size() ? a.vec[i] : 0) + (i < b.vec.size() ? b.vec[i] : 0);
            res.vec.push_back(cur % 10);
            t = cur / 10;
        }
        return res;
    }
    static BigInt abs_sub(const BigInt& a, const BigInt& b) {
        BigInt res = a;
        int t = 0;
        for (int i = 0; i < b.vec.size() || t; i++) {
            res.vec[i] -= t + (i < b.vec.size() ? b.vec[i] : 0);
            if (res.vec[i] < 0) {
                res.vec[i] += 10;
                t = 1;
            } else t = 0;
        }
        res.trim();
        return res;
    }
    friend BigInt operator+(BigInt a, const BigInt& b) {
        if (a.sign == b.sign) {
            BigInt res = abs_add(a, b);
            res.sign = a.sign;
            return res;
        }
        if (abs_less(a, b)) {
            BigInt res = abs_sub(b, a);
            res.sign = b.sign;
            return res;
        } else {
            BigInt res = abs_sub(a, b);
            res.sign = a.sign;
            return res;
        }
    }
    friend BigInt operator-(BigInt a, BigInt b) {
        b.sign *= -1;
        return a + b;
    }
    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        if ((a.vec.size() == 1 && a.vec[0] == 0) || (b.vec.size() == 1 && b.vec[0] == 0))
            return BigInt(0);
        BigInt res;
        res.vec.assign(a.vec.size() + b.vec.size(), 0);
        for (int i = 0; i < a.vec.size(); i++) {
            for (int j = 0; j < b.vec.size(); j++) {
                res.vec[i + j] += a.vec[i] * b.vec[j];
                res.vec[i + j + 1] += res.vec[i + j] / 10;
                res.vec[i + j] %= 10;
            }
        }
        res.sign = a.sign * b.sign;
        res.trim();
        return res;
    }
    BigInt operator-() const {
        BigInt res = *this;
        if (res != BigInt(0)) res.sign *= -1;
        return res;
    }
    BigInt& operator+=(const BigInt& b) { return *this = *this + b; }
    BigInt& operator-=(const BigInt& b) { return *this = *this - b; }
    BigInt& operator*=(const BigInt& b) { return *this = *this * b; }
    static pair<BigInt, BigInt> abs_divmod(const BigInt& a, const BigInt& b) {
        if (b == BigInt(0)) return {BigInt(0), BigInt(0)};
        if (abs_less(a, b)) return {BigInt(0), a};

        BigInt q, r(0);
        q.vec.assign(a.vec.size(), 0);
        for (int i = a.vec.size() - 1; i >= 0; i--) {
            r = r * 10 + BigInt(a.vec[i]);
            int cnt = 0;
            while (!abs_less(r, b)) {
                r = abs_sub(r, b);
                cnt++;
            }
            q.vec[i] = cnt;
        }
        q.trim();
        r.trim();
        return {q, r};
    }

    friend pair<BigInt, BigInt> divmod(BigInt a, BigInt b) {
        int res_q_sign = a.sign * b.sign;
        int res_r_sign = a.sign; 

        pair<BigInt, BigInt> res = abs_divmod(a, b);
        
        res.first.sign = res_q_sign;
        res.second.sign = res_r_sign;
        
        res.first.trim();  
        res.second.trim();
        return res;
    }

    
    BigInt operator/(const BigInt& b) const { return divmod(*this, b).first; }
    BigInt operator%(const BigInt& b) const { return divmod(*this, b).second; }
    BigInt& operator/=(const BigInt& b) { return *this = *this / b; }
    BigInt& operator%=(const BigInt& b) { return *this = *this % b; }

    BigInt operator*(int b_int) const {
        if (b_int == 0) return BigInt(0);
        BigInt b_big(b_int);
        return (*this) * b_big;
    }
    friend ostream& operator<<(ostream& os, const BigInt& a) {
        if (a.sign == -1) os << '-';
        for (int i = a.vec.size() - 1; i >= 0; i--) os << a.vec[i];
        return os;
    }

    friend istream& operator>>(istream& is, BigInt& a) {
        string s;
        if (!(is >> s)) return is;
        a = BigInt(s);
        return is;
    }
};

void solve()
{
    BigInt x0, y0, x1, y1, x2, y2, m1, m2, xv, yv;
    cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2 >> m1 >> m2 >> xv >> yv;
    x1 = x1 - x0;
    y1 = y1 - y0;
    x2 = x2 - x0;
    y2 = y2 - y0;
    m1 = m1 - x0;
    m2 = m2 - y0;
    BigInt d = 2 * (x1 * y2 - x2 * y1);
    BigInt p = y2 * y2 * y1 + x2 * x2 * y1 - x1 * x1 * y2 - y1 * y1 * y2;
    p *= -1;
    BigInt q = x2 * x2 * x1 + y2 * y2 * x1 - x1 * x1 * x2 - y1 * y1 * x2;
    BigInt l = (yv * p - xv * q + d * (xv * m2 - yv * m1)) * (yv * p - xv * q + d * (xv * m2 - yv * m1));
    BigInt r = (p * p + q * q) * (yv * yv + xv * xv);
    if(l == r)
        cout << "Or\n";
    else if(l > r)
        cout << "No\n";
    else
        cout << "Yes\n";
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