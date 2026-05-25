#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
using ld = long double;
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