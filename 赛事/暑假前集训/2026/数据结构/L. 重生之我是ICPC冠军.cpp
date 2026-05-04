#include <bits/stdc++.h>
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
constexpr int MOD = 998244353, INF = 1e9;

void solve()
{
    i64 n, l1, l2, l3;
    cin >> n >> l1 >> l2 >> l3;
    vector<pll> pers;
    pers.push_back({l1, 1});
    pers.push_back({l2, 2});
    pers.push_back({l3, 3});
    sort(pers.begin(), pers.end());

    l1 = pers[0].first, l2 = pers[1].first, l3 = pers[2].first;
    vector<int> mp(4);
    for (int i = 1; i <= 3;i++)
    {
        int ori = pers[i - 1].second;
        mp[ori] = i;
    }

    vector<i64> t(4, 0);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    vector<pll> tmp;
    for (int i = 0; i< n;i++)
    {
        i64 p, c;
        cin >> p >> c;
        p = mp[p];
        t[p] += c;

        pq.push({c, p});
    }

    i64 MAX;
    cin >> MAX;
    i64 cur = 0;
    i64 cost = 0;
    while(!pq.empty())
    {
        auto [c, p] = pq.top();
        pq.pop();
        if(p == 1)
        {
            if(cur + c <= l1)
            {
                cur += c;
                cost += cur;
                t[1] -= c;
            }
        }
        else if(p == 2)
        {
            if(cur + c + t[1] <= l1)
            {
                cur += c;
                cost += cur;
                t[2] -= c;
            }
            else
                tmp.push_back({c, p});
        }
        else if(p == 3)
        {
            if(cur + c + t[1] <= l1 && cur + c + t[2] + t[1] <= l2)
            {
                cur += c;
                cost += cur;
                t[3] -= c;
            }
            else
                tmp.push_back({c, p});
        }

        if(t[1] == 0 || cur >= l1)
            break;
    }

    for(auto &[c, p] : tmp)
        pq.push({c, p});
    tmp.clear();
    while(!pq.empty())
    {
        auto [c, p] = pq.top();
        pq.pop();

        if(p == 2)
        {
            if (cur + c <= l2)
            {
                cur += c;
                cost += cur;
                t[2] -= c;
            }
        }
        else if(p == 3)
        {
            if(cur + c + t[2] <= l2)
            {
                cur += c;
                cost += cur;
                t[3] -= c;
            }
            else
                tmp.push_back({c, p});
        }

        if(t[2] == 0 || cur >= l2)
            break;
    }

    for(auto &[c, p] : tmp)
        pq.push({c, p});
    tmp.clear();

    while(!pq.empty())
    {
        auto [c, p] = pq.top();
        pq.pop();

        if(p == 3)
        {
            if(cur + c <= l3)
            {
                cur += c;
                cost += cur;
                t[3] -= c;
            }
        }

        if(t[3] == 0 || cur >= l3)
            break;
    }

    if(t[1] == 0 && t[2] == 0 && t[3] == 0 && cost < MAX)
        cout << "YES\n";
    else
        cout << "NO\n";
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