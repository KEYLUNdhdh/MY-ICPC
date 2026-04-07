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
deque<i64> d = {2, 3, 5, 7};

void pre()
{
    auto check = [&](i64 x) -> bool
    {
        for (int i = 2; i * i <= x;i++)
        {
            if(x % i == 0)
                return false;
        }
        return true;
    };

    i64 now = 1;
    while(1)
    {
        i64 lw = now;
        now *= 10;
        if(now == 1e9)
            break;
        int up = d.size();
        for (int j = 1; j <= 9;j++)
        {
            for (int i = 0; i < up;i++)
            {
                i64 num = d[i];
                i64 tmp = num + now * j;
                if(check(tmp) && tmp <= 1e9)
                    d.push_back(tmp);
            }
        }
    }
    // debugarr(d)
    // ofstream ofs(R"(C:\Users\KEYLUN\OneDrive\vscode\output.txt)");
    // for (int i = 0; i < d.size();i++)
    //     ofs << d[i] << " ";
    // ofs.close();

}
void solve()
{
    i64 l, r;
    cin >> l >> r;
    int lw = lower_bound(d.begin(), d.end(), l) - d.begin();
    int up = upper_bound(d.begin(), d.end(), r) - d.begin();
    i64 ll = -1, rr = -1;
    if(up == lw)
    {
        cout << l << " " << r << "\n";
        return;
    }
    i64 maxx = 0;
    auto update = [&](int x, int y) -> void
    {
        if(x > y)
            return;
        i64 len = y - x + 1;
        if(len > maxx)
        {
            maxx = len;
            ll = x;
            rr = y;
        }
    };

    update(l, d[lw] - 1);
    for (int i = lw + 1; i < up;i++)
    {
        update(d[i - 1] + 1, d[i] - 1);
    }
    update(d[up - 1] + 1, r);
    if(maxx == 0)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << ll << " " << rr << "\n";
    }
}

signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}