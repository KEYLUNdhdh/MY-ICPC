#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \   
}
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
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
const int MOD = 998244353;

struct f
{
    int id;
    i64 a, b, c;
    bool operator<(const f& p) const
    {
        if(a != p.a)
            return a < p.a;
        else if(b != p.b)
            return b < p.b;
        else
            return c < p.c;
    }
};
//思路严谨一点
bool check(const f& p,const f& q)
{
    i64 m = p.a - q.a;
    if(m < 0)
        return false;
    i64 n = p.b - q.b;
    i64 k = p.c - q.c;
    if(m == 0)
        return (n == 0 && k > 0);
    i64 ju1 = n * n - 4 * m * k;
    if(ju1 < 0 && m > 0)
        return true;
    return false;
}
void solve()
{
    int n;
    cin >> n;
    vector<f> vec(n);
    for (int i = 0; i < n;i++)
    {
        cin >> vec[i].a >> vec[i].b >> vec[i].c;
        vec[i].id = i;
    }
    sort(vec.begin(), vec.end());
    vector<int> l(n, 1), r(n, 1);
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            if(check(vec[i], vec[j]))
                chmax(l[i], l[j] + 1);
        }
    }
    for (int i = n - 1;i >= 0;i--)
    {
        for (int j = n - 1; j > i;j--)
        {
            if(check(vec[j], vec[i]))
                chmax(r[i], r[j] + 1);
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < n;i++)
        ans[vec[i].id] = l[i] + r[i] - 1;
    for (int i = 0; i < n;i++)
        cout << ans[i] << " ";
    cout << "\n";
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