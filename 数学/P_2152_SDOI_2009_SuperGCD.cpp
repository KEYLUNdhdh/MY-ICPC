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
using db = double;
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
    BigInt(i64 x = 0)
    {
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
    }
    bool operator<(const BigInt& b) const
    {
        if(vec.size() != b.vec.size())
            return vec.size() < b.vec.size();
        for (int i = vec.size() - 1; i >= 0;i--)
        {
            if(vec[i] != b.vec[i])
                return vec[i] < b.vec[i];
        }
        return false;
    }
    bool operator>(const BigInt &b) const { return b < *this; }
    bool operator<=(const BigInt &b) const { return !(*this > b); }
    bool operator>=(const BigInt &b) const { return !(*this < b); }
    bool operator==(const BigInt &b) const { return vec == b.vec; }
    bool operator!=(const BigInt &b) const { return vec != b.vec; }
    BigInt operator+=(const BigInt& b)
    {
        int t = 0;
        for (int i = 0; i < max(vec.size(), b.vec.size()) || t;i++)
        {
            if(i == vec.size())
                vec.push_back(0);
            vec[i] += t + (i < b.vec.size() ? b.vec[i] : 0);
            t = vec[i] / 10;
            vec[i] %= 10;
        }
        trim();
        return *this;
    }
    friend BigInt operator+(BigInt a,const BigInt& b)
    {
        a += b;
        return a;
    }
    //promise *this > b
    BigInt operator-=(const BigInt& b)
    {
        int t = 0;
        for (int i = 0; i < b.vec.size() || t;i++)
        {
            vec[i] -= t + (i < b.vec.size() ? b.vec[i] : 0);
            if(vec[i] < 0)
            {
                vec[i] += 10;
                t = 1;
            }
            else
                t = 0;
        }
        trim();
        return *this;
    }
    friend BigInt operator-(BigInt a,const BigInt& b)
    {
        a -= b;
        return a;
    }
    friend BigInt operator*(const BigInt& a,const BigInt& b)
    {
        if((a.vec.size() == 1 && a.vec[0] == 0) || (b.vec.size() == 1 && b.vec[0] == 0))
        return BigInt(0);
        BigInt res(0);
        res.vec.assign(a.vec.size() + b.vec.size() + 5, 0);
        for (int i = 0; i < a.vec.size();i++)
        {
            for (int j = 0; j < b.vec.size();j++)
            {
                res.vec[i + j] += a.vec[i] * b.vec[j];
                res.vec[i + j + 1] += res.vec[i + j] / 10;
                res.vec[i + j] %= 10;
            }
        }
        res.trim();
        return res;
    }
    //BigInt  * int (int comes later)
    BigInt operator*(int b) const 
    {
        if(b == 0)
            return BigInt(0);
        BigInt res = *this;
        int t = 0;
        for (int i = 0; i < res.vec.size() || t;i++)
        {
            if(i == res.vec.size())
                res.vec.push_back(0);
            i64 cur = 1ll * res.vec[i] * b + t;
            res.vec[i] = cur % 10;
            t = cur / 10;
        }
        res.trim();
        return res;
    }
    BigInt &operator*=(const BigInt b) &
    {
        *this = *this * b;
        return *this;
    }
    //返回{商，余数}
    static pair<BigInt,BigInt> divmod(BigInt a,const BigInt& b)
    {
        if(a < b)
            return {BigInt{0}, a};
        BigInt q(0), r(0);
        q.vec.assign(a.vec.size(), 0);
        for (int i = a.vec.size() - 1; i >= 0;i--)
        {
            r = r * 10 + a.vec[i];
            int cnt = 0;
            while(r >= b)
            {
                r -= b;
                cnt++;
            }
            q.vec[i] = cnt;
        }
        q.trim();
        return {q, r};
    }
    friend BigInt operator/(BigInt& a,BigInt& b)
    {
        return divmod(a, b).first;
    }
    friend BigInt operator%(BigInt& a,BigInt& b)
    {
        return divmod(a, b).second;
    }
    BigInt operator/=(const BigInt& b)
    {
        *this = divmod(*this, b).first;
        return *this;
    }
    BigInt operator%=(const BigInt& b)
    {
        *this = divmod(*this, b).second;
        return *this;
    }
    friend BigInt qpow(BigInt a,int m)
    {
        BigInt res(1);
        while(m)
        {
            if(m & 1)
                res = res * a;
            a = a * a;
            m >>= 1;
        }
        return res;
    }
    void div2() {
        int t = 0;
        for (int i = vec.size() - 1; i >= 0; i--) {
            int cur = vec[i] + t * 10;
            vec[i] = cur / 2;
            t = cur % 2;
        }
        trim();
    }

    void mul2() {
        int t = 0;
        for (int i = 0; i < vec.size() || t; i++) {
            if (i == vec.size()) vec.push_back(0);
            int cur = vec[i] * 2 + t;
            vec[i] = cur % 10;
            t = cur / 10;
        }
    }
    friend ostream& operator<<(ostream& os,const BigInt& a)
    {
        for (int i = a.vec.size() - 1; i >= 0;i--)
            os << a.vec[i];
        return os;
    }
    friend istream& operator>>(istream& is,BigInt& a)
    {
        string s;
        if(!(is >> s))
            return is;
        a = BigInt(s);
        return is;
    }
};

void solve()
{
    BigInt a, b;
    cin >> a >> b;
    auto even = [&](BigInt a) -> bool
    {
        if(a.vec[0] % 2 == 1)
            return false;
        else
            return true;
    };

    auto gcd = [&](BigInt l, BigInt r) -> BigInt
    {
        int shift = 0;
        while(l != BigInt(0) && r != BigInt(0))
        {
            bool ll = even(l);
            bool rr = even(r);
            if(ll && rr)
            {
                shift++;
                l.div2();
                r.div2();
            }
            else if(ll)
                l.div2();
            else if(rr)
                r.div2();
            else
            {
                if(l < r)
                    swap(l, r);
                l -= r;
            }
        }
        BigInt res = (l == BigInt(0) ? r : l);
        while(shift--)
            res.mul2();
        return res;
    };
    cout << gcd(a, b);
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}