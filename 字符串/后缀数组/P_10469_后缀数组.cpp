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

struct SuffixArray
{
    int n;
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

void solve()
{
    string s;
    cin >> s;

    SuffixArray suf(s);
    int len = s.size();
    for (int i = 1; i <= len;i++)
        cout << suf.sa[i] - 1 << " ";
    cout << "\n";
    for (int i = 1; i <= len;i++)
        cout << suf.height[i] << " ";
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