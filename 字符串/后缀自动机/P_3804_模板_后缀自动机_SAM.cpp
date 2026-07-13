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

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SAM
{
    struct Node
    {
        int len;
        int link;
        int next[27];
        i64 siz;
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
        if(c >= 'a' && c <= 'z')
            return c - 'a';
        else if(c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        else if(c >= '0' && c <= '9')
            return c - '0' + 52;
        return 69;
    }

    void extend(char c)
    {
        assert(!sizComputed);
        
        int idx = getId(c);
        int cur = ++sz;
        t[cur].len = t[last].len + 1;
        t[cur].siz = 1;

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
                t[clone].siz = 0;

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

    bool isSubstirng(const string & query)
    {
        int p = 1;
        for (char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return false;
            p = t[p].next[idx];
        }
        return true;
    }

    void comSiz()
    {
        if(sizComputed)
            return;

        vector<int> c(sz + 1, 0);
        vector<int> rk(sz + 1, 0);
        for (int i = 1; i <= sz;i++)
            c[t[i].len]++;
        for (int i = 1; i <= sz;i++)
            c[i] += c[i - 1];
        for (int i = 1; i <= sz;i++)
            rk[c[t[i].len]--] = i;

        for (int i = sz; i >= 2;i--)
        {
            int u = rk[i];
            t[t[u].link].siz += t[u].siz;
        }

        sizComputed = 1;
    }

    i64 count(const string &query)
    {
        comSiz();

        int p = 1;
        for(char c : query)
        {
            int idx = getId(c);
            if(!t[p].next[idx])
                return 0;
            p = t[p].next[idx];
        }

        return t[p].siz;
    }
};

void solve()
{
    string s;
    cin >> s;

    int n = s.size();
    SAM sam(n);
    for(char c : s)
        sam.extend(c);

    sam.comSiz();
    i64 ans = 0;
    for (int i = 1; i <= sam.sz;i++)
        if(sam.t[i].siz != 1)
            chmax(ans, 1ll * sam.t[i].len * sam.t[i].siz);

    cout << ans;
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