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

struct SuffixArray
{
    int n;
    // 1 - index
    vector<int> sa;
    vector<int> rk;
    vector<int> height;

    SuffixArray() = default;

    explicit SuffixArray(const string &str)
    {
        build(str);
    }

    // str 0 - index
    void build(const string &str)
    {
        n = str.size();

        //1 - index
        string s = " " + str;
        sa.assign(n + 1, 0);
        rk.assign(2 * n + 2, 0);

        vector<int> oldrk(2 * n + 2, 0);
        vector<int> id(n + 1, 0);
        vector<int> cnt(max(n, 256) + 1, 0);

        int m = 256;

        for (int i = 1; i <= n;i++)
        {
            rk[i] = static_cast<unsigned char>(s[i]) + 1;
            cnt[rk[i]]++;
        }

        for (int i = 1; i <= m;i++)
            cnt[i] += cnt[i - 1];

        for (int i = n; i >= 1;i--)
            sa[cnt[rk[i]]--] = i;

        for (int w = 1, p = 0;; w <<= 1)
        {
            p = 0;

            for (int i = max(1, n - w + 1); i <= n;i++)
                id[++p] = i;

            for (int i = 1; i <= n;i++)
                if(sa[i] > w)
                    id[++p] = sa[i] - w;

            fill(cnt.begin(), cnt.begin() + m + 1, 0);

            for (int i = 1; i <= n;i++)
                cnt[rk[id[i]]]++;
            for (int i = 1; i <= m;i++)
                cnt[i] += cnt[i - 1];
                
            for (int i = n; i >= 1;i--)
                sa[cnt[rk[id[i]]]--] = id[i];

            oldrk = rk;
            rk[sa[1]] = 1;
            p = 1;

            for (int i = 2; i <= n;i++)
            {
                int x = sa[i - 1];
                int y = sa[i];
                bool same = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
                rk[y] = same ? p : ++p;
            }

            m = p;
            if(p == n)
                break;
        }
        buildHeight(s);
    }

    void buildHeight(const string &s)
    {
        height.assign(n + 1, 0);
        int k = 0;

        for (int i = 1; i <= n;i++)
        {
            int rki = rk[i];
            if(rki == 1)
            {
                k = 0;
                continue;
            }

            int j = sa[rki - 1];

            while(i + k <= n && j + k <= n && s[i + k] == s[j + k])
                k++;

            height[rki] = k;
            if(k > 0)
                k--;
        }
    }
};

template<typename T,typename F>
struct STable
{
    int n;
    int maxlog;
    vector<vector<T>> st;
    F func;
    //a 1 - index
    STable(const vector<T>& a,const F& f) : func(f)
    {
        n = a.size() - 1;
        maxlog = __lg(n) + 1;
        st.assign(n + 1, vector<T>(maxlog));
        for (int i = 1; i <= n;i++)
            st[i][0] = a[i];
        for (int j = 1; j < maxlog;j++)
        {
            int len = 1 << (j - 1);
            for (int i = 1;i <= n - (1 << j) + 1;i++)
                st[i][j] = func(st[i][j - 1], st[i + len][j - 1]);
        }
    }
    inline T query(int l,int r) const
    {
        if (l > r) 
            swap(l, r);
        int k = __lg(r - l + 1);
        return func(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

void solve()
{
    string p;
    while(cin >> p)
    {
        int k;
        cin >> k;
        vector<int> s(k), d(k);
        i64 ans = 0;
        for (int i = 0; i < k;i++)
        {
            cin >> s[i] >> d[i];
            ans += d[i] - s[i] + 1;
        }

        SuffixArray suf(p);
        vector<int> &h = suf.height;
        vector<int> &rk = suf.rk;
        STable st(h, [](const int &a, const int &b) { return min(a, b); });
        // debugarr(h)
        i64 res = 0;
        for (int i = 0; i < k;i++)
        {
            int lcp = 0;
            if(i > 0)
            {   
                int ls = rk[s[i - 1] + 1];
                int rs = rk[s[i] + 1];
                // debug(ls)
                // debug(rs)
                if(ls == rs)
                {
                    lcp = min(d[i] - s[i], d[i - 1] - s[i - 1]);
                    // debug(lcp)
                }
                else
                {
                    int minn = min(ls, rs);
                    int maxx = max(ls, rs);
                    lcp = min({st.query(minn + 1, maxx), d[i] - s[i], d[i - 1] - s[i - 1]});
                }
            }
            // debug(lcp)
            res += (to_string(lcp).size() + 1) + (d[i] - s[i] - lcp) + 1;
            // cutline
        }

        cout << ans << " " << res << "\n";
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