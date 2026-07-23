#include <bits/stdc++.h>
#define lyc_fan_club main
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x){        \
    cerr << #x << " : ";    \
    for(auto v : x)         \
    cerr << v << " ";       \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
using namespace std;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
using db = double;
typedef pair<int, int> pii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
void chmin(T &a, T b) 
{
    if (a > b) 
        a = b;
}

template<class T>
void chmax(T &a, T b) 
{
    if (a < b) 
        a = b;
}
constexpr i64 MOD = 998244353, INF = 1e9;

void solve()
{
    int n, op;
    cin >> n >> op;

    vector<int> a(n + 1, 0), p(n + 1, 0);
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i];
        p[i] = p[i - 1] + a[i];
    }

    vector<i64> x(n + 1, 0);
    x[1] = 0;
    i64 lb = 0;
    for (int i = 1; i <= n;i++)
    {
        lb += p[i] - i;
        chmax(x[1], lb);
    }
    i64 sum = x[1];

    for (int i = 2; i <= n;i++)
        x[i] = x[i - 1] - p[i - 1] + (i - 1), sum += x[i];
    
    if (op == 1)
    {
        cout << sum << "\n";
        queue<pii> q;
        for (int i = 1; i <= n;i++)
            if(x[i] != 0)
                q.push({i, x[i]});
        vector<int> cur(n + 1, 1);
        
        auto check = [&](int pos) -> bool
        {
            if(pos == 1)
                return cur[2] > 0;
            else if(pos == n)
                return cur[n - 1] > 0;
            else
                return (cur[pos - 1] > 0 && cur[pos + 1] > 0);
        };

        while(!q.empty())
        {
            auto [pos, cnt] = q.front();

            if(check(pos))
            {
                q.pop();
                cnt -= 1;
                cout << pos << " ";
                if(cnt > 0)
                    q.push({pos, cnt});

                if(pos == 1)
                    cur[1]++, cur[2]--;
                else if(pos == n)
                    cur[n]++, cur[n - 1]--;
                else
                    cur[pos] += 2, cur[pos - 1]--, cur[pos + 1]--;
            }
            else
            {
                q.push({pos, cnt});
                q.pop();
            }
        }
    }
    else
        cout << sum;
    // debugarr(x)
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