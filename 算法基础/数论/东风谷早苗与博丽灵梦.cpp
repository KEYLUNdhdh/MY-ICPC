#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
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
    static pair<i128,i64> minx(i64 a,i64 b,i64 c)
    {
        result res = solve(a, b, c);
        if(!res.f)
            return {-1, -1};
        if(c == 0)
            return {0, (i64)res.g};
        i128 bg = b / res.g;   
        if(bg < 0)
            bg = -bg;
        i128 k = -res.x / bg;
        while(res.x + k * bg < 0)
            k++;
        while(res.x + (k - 1) * bg >= 0)
            k--;
        i128 x = res.x + k * bg;
        return {x, (i64)res.g};
    }
};
void solve()
{
    i64 x, a, s;
    cin >> x >> a >> s;
    auto [c1, g] = exgcd::minx(a, s, x);
    if(c1 == -1 && g == -1)
    {
        cout << "No\n";
        return;
    }
    i128 c2 = (x - c1 * a) / s;
    i128 sg = s / g;
    i128 ag = a / g;
    //r如果等于 c2 / ag，有可能为0，二分查找直接卡死，要多加一个1
    i128 l = 0, r = c2 / ag + 1;
    auto check = [&](auto mid)
    {
        auto x1 = c1 + mid * sg;
        auto y1 = c2 - mid * ag;
        return pllll {x1, y1};
    };
    //l + 1 < r这是二分查找最安全的写法
    while(l + 1 < r)
    {
        i128 mid = l + r >> 1;
        auto [x1, y1] = check(mid);
        if(x1 > y1)
            r = mid;
        else
            l = mid;
    }
    auto [x0, y0] = check(l);
    auto [x1, y1] = check(r);
    if(min(x0,y0) < 0  && min(x1,y1) < 0)
    {
        cout << "No\n";
        return;
    }
    else
        cout << "Yes\n";
    if(min(x0,y0) < 0)
        cout << x1 << " " << y1 << "\n";
    else if(min(x1,y1) < 0)
        cout << x0 << " " << y0 << "\n";
    else if(max(x0, y0) < max(x1, y1))
        cout << x0 << " " << y0 << "\n";
    else
        cout << x1 << " " << y1 << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}