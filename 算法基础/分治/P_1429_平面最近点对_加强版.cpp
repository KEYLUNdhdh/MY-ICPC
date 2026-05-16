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

struct po
{
    db x, y;
    db dis(const po &b)
    {
        db tmp =  (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
        return sqrt(tmp);
    }

};
void solve()
{
    int n;
    cin >> n;
    vector<po> a(n + 1);
    db minx, maxx;
    for (int i = 1; i <= n;i++)
    {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin() + 1, a.end(), [](const po &x, const po &y){ return x.x < y.x; });
    minx = a[1].x;
    maxx = a[n].x;

    auto sol = [&](auto self, int l, int r) -> db
    {
        if(l >= r)
            return INF;
        int m = l + r >> 1;
        db lans = self(self, l, m);
        db rans = self(self, m + 1, r);
        db cur = min(lans, rans);
        db curmid = a[m].x;
        db tmpans = min(lans, rans);
        vector<po> tmp;
        for (int i = l; i <= r;i++)
        {
            if(abs(a[i].x - curmid) < cur)
                tmp.push_back(a[i]);
        }

        sort(tmp.begin(), tmp.end(), [](const po &a, const po &b){return a.y < b.y;});

        int len = tmp.size();
        for (int i = 0; i < len;i++)
        {
            for (int j = i + 1; j < len;j++)
            {
                if(tmp[j].y - tmp[i].y >= cur)
                    break;
                db dis = tmp[i].dis(tmp[j]);
                chmin(tmpans, dis);
            }
        }
        
        return tmpans;
    };

    db ans = sol(sol, 1, n);

    cout << fixed << setprecision(4) << ans;
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