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

struct SAM
{
    static constexpr int SIGMA = 4; // depends on the problem

    struct Node
    {
        int len;
        int link;
        int next[SIGMA];
    };

    vector<Node> t;
    int sz;
    int last;
    bool sizComputed;
    SAM(int n)
    {
        t.resize(2 * n + 2);
        sz = 1;
        last = 1;
        t[1].len = 0;
        t[1].link = 0;
        sizComputed = 0;
    }

    int getId(char c) const
    {
        if(c == 'E')
            return 0;
        else if(c == 'W')
            return 1;
        else if(c == 'S')
            return 2;
        else
            return 3;
    }

    void extend(char c)
    {
        assert(!sizComputed);

        int idx = getId(c);
        int cur = ++sz;
        t[cur].len = t[last].len + 1;

        int p = last;
        while(p > 0 && !t[p].next[idx])
        {
            t[p].next[idx] = cur;
            p = t[p].link;
        }

        if(p == 0)
            t[cur].link = 1;
        else
        {
            int q = t[p].next[idx];
            if(t[p].len + 1 == t[q].len)
                t[cur].link = q;
            else
            {
                int clone = ++sz;
                t[clone].len = t[p].len + 1;
                t[clone].link = t[q].link;
                copy(begin(t[q].next), end(t[q].next), begin(t[clone].next));

                while(p > 0 && t[p].next[idx] == q)
                {
                    t[p].next[idx] = clone;
                    p = t[p].link;
                }

                t[q].link = t[cur].link = clone;
            }
        }

        last = cur;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    SAM sam(n);
    for (char c : s)
        sam.extend(c);

    string p;
    for (int i = 0; i < m;i++)
    {
        cin >> p;

        int cur = 1;
        int cnt = 0;
        for (char c : p)
        {
            int id = sam.getId(c);
            if(!sam.t[cur].next[id])
                break;

            cnt++;
            cur = sam.t[cur].next[id];
        }

        cout << cnt << "\n";
    }
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