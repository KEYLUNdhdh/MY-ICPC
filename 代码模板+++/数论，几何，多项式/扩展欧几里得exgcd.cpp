#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

ostream &operator<<(ostream &os, i128 n) {
    string s;
    if(n == 0)
        s = "0";
    if(n < 0)
    {
        s += "-";
        n = -n;
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

istream &operator>>(istream &is,i128& n)
{
    n = 0;
    string s;
    is >> s;
    for (int i = 0; i < s.size();i++)
    {
        n = n * 10 + s[i] - '0';
    }
    return is;
}

struct exgcd
{
    struct result
    {
        i64 x, y, g;
        bool f;
    };
    static result solve(i64 a,i64 b,i64 c)
    {
        i64 x = 1, y = 0, g = a;
        function<void(i64, i64)> dfs = [&](i64 a, i64 b)
        {
            if(b == 0)
            {
                g = a;
                x = 1, y = 0;
                return;
            }
            dfs(b, a % b);
            i64 tp = x;
            x = y;
            y = tp - (i64)(a / b) * y;
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
        i64 factor = c / g;
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