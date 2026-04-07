#include <bits/stdc++.h>
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
struct edge{
    i64 x, y;
    ld yield;

    void cal()
    {
        ld a = x * x + y * y;
        ld b = x * x + (y - 1) * (y - 1);
        yield = (a - b) / (sqrt(a) + sqrt(b));
    }
    bool operator<(const auto &b) const
    {
        return yield < b.yield;
    }
};
void solve()
{
    i64 n, w;
    cin >> n >> w;
    vector<edge> a(n);
    priority_queue<edge, vector<edge>> q;
    ld sum = 0;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i].x >> a[i].y;
        a[i].cal();
        sum += sqrt(a[i].x * a[i].x + a[i].y * a[i].y);
        q.push(a[i]);
    }
    while(w > 0 && !q.empty())
    {
        edge top = q.top();
        q.pop();
        sum -= top.yield;
        top.y--;
        w--;
        if(top.y > 0)
        {
            top.cal();
            q.push(top);
        }
    }
    cout << fixed << setprecision(10) << sum;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    return 0;
}