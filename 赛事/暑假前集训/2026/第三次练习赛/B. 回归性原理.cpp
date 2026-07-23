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
    static constexpr int SIGMA = 26; // depends on the problem

    struct Node
    {
        int len;
        int link;
        int next[SIGMA];
        i64 siz;
        int tot = 0;
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

    bool isSubstring(const string & query) const
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
        if(query.empty())
            return 0;

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

    i64 distinctSubstringCount() const
    {
        i64 ans = 0;
        for(int u = 2; u <= sz; u++)
            ans += t[u].len - t[t[u].link].len;
        return ans;
    }

    i64 distinctSubstringLengthSum() const
    {
        i64 ans = 0;

        for(int u = 2; u <= sz; u++)
        {
            i64 l = t[t[u].link].len + 1;
            i64 r = t[u].len;   
            ans += (l + r) * (r - l + 1) / 2;
        }

        return ans;
    }

    int LCS(const string &s) const
    {
        int p = 1;
        int len = 0;
        int ans = 0;

        for(char c : s)
        {
            int x = getId(c);

            while(p != 1 && !t[p].next[x])
            {
                p = t[p].link;
                len = t[p].len;
            }

            if(t[p].next[x])
            {
                p = t[p].next[x];
                len++;
            }
            else
            {
                p = 1;
                len = 0;
            }

            ans = max(ans, len);
        }
        return ans;
    }

    int multiLCS(const vector<string> &strs) const
    {
        if(strs.empty())
            return 0;

        int maxlen = 0;
        for (int i = 1; i <= sz; i++)
            maxlen = max(maxlen, t[i].len);

        vector<int> c(maxlen + 1, 0);
        vector<int> rk(sz + 1, 0);

        for (int i = 1; i <= sz; i++)
            c[t[i].len]++;

        for (int i = 1; i <= maxlen; i++)
            c[i] += c[i - 1];

        for (int i = sz; i >= 1; i--)
            rk[c[t[i].len]--] = i;

        vector<int> common(sz + 1);

        for (int i = 1; i <= sz; i++)
            common[i] = t[i].len;

        vector<int> best(sz + 1);

        for (int id = 0; id < (int)strs.size(); id++)
        {
            const string &s = strs[id];

            int p = 1;
            fill(best.begin(), best.end(), 0);
            int curlen = 0;

            for(char ch : s)
            {
                int idx = getId(ch);

                while(p != 1 && !t[p].next[idx])
                {
                    p = t[p].link;
                    curlen = min(curlen, t[p].len);
                }

                if(t[p].next[idx])
                {
                    p = t[p].next[idx];
                    curlen++;
                }
                else
                {
                    p = 1;
                    curlen = 0;
                }

                best[p] = max(best[p], curlen);
            }

            for (int i = sz; i >= 2; i--)
            {
                int u = rk[i];
                int fa = t[u].link;

                best[fa] = max(best[fa], min(best[u], t[fa].len));
            }

            for (int i = 2; i <= sz; i++)
                common[i] = min(common[i], best[i]);
        }
        int ans = 0;
        for (int i = 2; i <= sz; i++)
            ans = max(ans, common[i]);

        return ans;
    }
};

void solve()
{
    string s;
    cin >> s;

    int n = s.size();
    SAM sam(n);
    for (char c : s)
        sam.extend(c);

    sam.comSiz();
    int q;
    cin >> q;

    int tot = 1;
    while(q--)
    {
        string str;
        cin >> str;
        const  int len = str.size();
        str = str + str;
        str.pop_back();

        i64 ans = 0;
        int p = 1;
        int curlen = 0;
        for (char c : str)
        {
            int idx = sam.getId(c);
            while(p > 1 && !sam.t[p].next[idx])
            {
                p = sam.t[p].link;
                curlen = min(curlen, sam.t[p].len);
            }
            if(sam.t[p].next[idx])
            {
                p = sam.t[p].next[idx];
                curlen++;
                if(curlen < len)
                    continue;

                while(sam.t[sam.t[p].link].len >= len)
                    p = sam.t[p].link;
                    
                if(sam.t[p].tot != tot)
                {
                    sam.t[p].tot = tot;
                    ans += sam.t[p].siz;
                }
            }
            else
            {
                p = 1;
                curlen = 0;
            }
        }
        cout << ans << "\n";
        tot++;
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