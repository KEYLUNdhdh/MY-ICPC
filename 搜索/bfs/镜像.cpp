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

void solve()
{
    int a, b, k;
    cin >> a >> b >> k;
    auto reverse = [&](int k) -> int
    {
        int tp = k;
        int num = 0;
        while(tp)
        {
            num = num * 10 + tp % 10;
            tp /= 10;
        }
        return num;
    };
    if(a == b)
    {
        cout << 0 << "\n";
        return;
    }
    deque<int> d;
    d.push_back(a);
    int step = 0;
    vector<int> mp(1e6 + 5, 0);
    while(!d.empty())
    {
        int len = d.size();
        // debugarr(d);
        step++;
        while(len--)
        {
            int u = d.front();
            d.pop_front();
            if(u % 10 != 0)
            {
                int qq = reverse(u);
                // debug(qq);
                if(qq == b)
                {
                    cout << step << "\n";
                    return;
                }
                if(!mp[qq] && qq <= 1e6)
                {
                    d.push_back(qq);
                    mp[qq]++;
                }
            }
            int pass = u + k;
            // debug(pass);
            if(pass == b)
            {
                cout << step << "\n";
                return;
            }
            else if(pass <= 1e6 && !mp[pass])
            {
                d.push_back(pass);
                mp[pass]++;
            }
        }
    }
    cout << -1 << "\n";
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