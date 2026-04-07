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
        i128 x, y, g;
        bool f;
    };
    //ExGCD 找到通解公式
    // 求解 ax + by = c
    // 返回结构体包含一组特解 x, y，最大公约数 g，以及是否有解
    //对于static来说,可以通过exgcd::使用命名空间直接调用而不用创建实例
    static result solve(i64 a,i64 b,i64 c)
    {
        i128 x = 1, y = 0, g = a;
        function<void(i64, i64)> dfs = [&](i64 a, i64 b)
        {
            if(b == 0)
            {
                g = a;
                x = 1, y = 0;
                return;
            }
            dfs(b, a % b);
            i128 tp = x;
            x = y;//更新x
            y = tp - (i128)(a / b) * y;//更新y
        };
        dfs(a, b);
        if(g < 0)//保证最大公约数为正的
        {
            g = -g;
            x = -x;
            y = -y;
        }
        if(c % g)//如果gcd(a,b)不能整除c,说明无解
        {
            return {0, 0, g, false};
        }
        i128 factor = c / g;
        return {x * factor, y * factor, g, true};
    }
    //获取 x 的最小非负整数解
    //返回 {x_min, g}，若无解返回 {-1, -1}，这里的g是gcd(a,b)
    //这个二分是基于通解 c1 = X + k * b / g 和 c2 = Y - k * a / g 来寻找平衡点的。
    //ax + by = c
    static pair<i128,i64> minx(i64 a,i64 b,i64 c)
    {
        result res = solve(a, b, c);
        //无解
        if(!res.f)
            return {-1, -1};
        //c为0，解可以为0 0
        if(c == 0)
            return {0, (i64)res.g};
        i128 bg = b / res.g;  //这是参数a对应的元的步长 
        //让bg始终为正的，方便二分
        if(bg < 0)
            bg = -bg;
        //我们要找最小的 x >= 0。由公式 x + k * bg >= 0 得 k >= -x / bg
        i128 k = -res.x / bg;
        while(res.x + k * bg < 0)
            k++;
        while(res.x + (k - 1) * bg >= 0)
            k--;
        i128 x = res.x + k * bg;
        return {x, (i64)res.g};
    }
};