// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
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
#define KEYLUN main
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
void debug_out() { cerr << "\n"; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T)
{
    cerr << " " << H;
    debug_out(T...);
}
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char *names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char *names, Head H, Tail... T)
{
    while (*names == ' ' || *names == ',')
        names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i)
    {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[')
            bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']')
            bracket--;
        else if (names[i] == ',' && bracket == 0)
            break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H)
        cerr << v << " ";
    cerr << "\n";

    debugarr_out(names + i + 1, T...);
}
#define cutline                             \
    {                                       \
        cerr << "----------------------\n"; \
    }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template <class T>
void chmin(T &a, T b)
{
    if (a > b)
        a = b;
}
template <class T>
void chmax(T &a, T b)
{
    if (a < b)
        a = b;
}
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct SAM
{
    static constexpr int SIGMA = 27; // depends on the problem

    struct Node
    {
        int len;
        int link;
        int next[SIGMA];
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
        if (c >= 'a' && c <= 'z')
            return c - 'a';
        assert(false);
        return -1;
    }

    void extend(char c)
    {
        assert(!sizComputed);

        int idx = getId(c);
        int cur = ++sz;
        t[cur].len = t[last].len + 1;
        t[cur].siz = 1;

        int p = last;
        while (p > 0 && !t[p].next[idx])
        {
            t[p].next[idx] = cur;
            p = t[p].link;
        }

        if (p == 0)
            t[cur].link = 1;
        else
        {
            int q = t[p].next[idx];
            if (t[p].len + 1 == t[q].len)
                t[cur].link = q;
            else
            {
                int clone = ++sz;
                t[clone].len = t[p].len + 1;
                t[clone].link = t[q].link;
                copy(begin(t[q].next), end(t[q].next), begin(t[clone].next));
                t[clone].siz = 0;

                while (p > 0 && t[p].next[idx] == q)
                {
                    t[p].next[idx] = clone;
                    p = t[p].link;
                }

                t[q].link = t[cur].link = clone;
            }
        }

        last = cur;
    }

    void comSiz()
    {
        if (sizComputed)
            return;

        vector<int> c(sz + 1, 0);
        vector<int> rk(sz + 1, 0);
        for (int i = 1; i <= sz; i++)
            c[t[i].len]++;
        for (int i = 1; i <= sz; i++)
            c[i] += c[i - 1];
        for (int i = 1; i <= sz; i++)
            rk[c[t[i].len]--] = i;

        for (int i = sz; i >= 2; i--)
        {
            int u = rk[i];
            t[t[u].link].siz += t[u].siz;
        }

        sizComputed = 1;
    }

    i64 count(const string &query)
    {
        if (query.empty())
            return 0;

        comSiz();
        int p = 1;
        for (char c : query)
        {
            int idx = getId(c);
            if (!t[p].next[idx])
                return 0;
            p = t[p].next[idx];
        }

        return t[p].siz;
    }

    i64 distinctSubstringCount() const
    {
        i64 ans = 0;
        for (int u = 2; u <= sz; u++)
            ans += t[u].len - t[t[u].link].len;
        return ans;
    }

    i64 distinctSubstringLengthSum() const
    {
        i64 ans = 0;

        for (int u = 2; u <= sz; u++)
        {
            i64 l = t[t[u].link].len + 1;
            i64 r = t[u].len;
            ans += (l + r) * (r - l + 1) / 2;
        }

        return ans;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    // s = s + s;
    SAM sam(n);
    for (char c : s)
        sam.extend(c);

    SAM sam2(2 * n);
    for (char c : s)
        sam2.extend(c);
    for (char c : s)
        sam2.extend(c);

    SAM sam3(3 * n);
    for (char c : s)
        sam3.extend(c);
    for (char c : s)
        sam3.extend(c);
    for (char c : s)
        sam3.extend(c);
    i64 ans = sam3.distinctSubstringCount();
    i64 dis = ans - sam2.distinctSubstringCount();

    if (m == 1)
    {
        cout << sam.distinctSubstringCount() % MOD << "\n";
        return;
    }
    else if (m == 2)
    {
        cout << sam2.distinctSubstringCount() % MOD << "\n";
        return;
    }
    // debug(sam.distinctSubstringCount());
    // WA

    ans = (ans + 1ll * (m - 3) * (dis % MOD)) % MOD;
    // for (int k = 3; k <= m; k++)
    // {

    // }
    cout << ans;
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}