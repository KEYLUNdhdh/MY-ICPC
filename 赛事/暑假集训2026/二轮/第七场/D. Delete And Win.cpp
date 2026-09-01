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
void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char* names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char* names, Head H, Tail... T) {
    while (*names == ' ' || *names == ',') names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i) {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[') bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']') bracket--;
        else if (names[i] == ',' && bracket == 0) break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H) cerr << v << " ";
    cerr << "\n"; 
    
    debugarr_out(names + i + 1, T...);
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template<class T> void chmin(T &a, T b) { if (a > b) a = b; }
template<class T> void chmax(T &a, T b) { if (a < b) a = b; }
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

struct SegmentTree
{
    int n;
    vector<i64> mulTag, addTag, sum, eTag, maxx, minn, hasE;
    SegmentTree(int n_) : n{n_}, mulTag(4 * n + 1, 1), addTag(4 * n + 1, 0), sum(4 * n + 1), eTag(4 * n + 1, 0), maxx(4 * n + 1, -INF), minn(4 * n + 1, INF), hasE(4 * n + 1, 0) {}

    void init(int p, int l, int r, const vector<i64> &a)
    {   
        if(l == r)
        {
            sum[p] = a[l];
            maxx[p] = a[l];
            minn[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        init(p << 1, l, m, a);
        init(p << 1 | 1, m + 1, r, a);
        pull(p);
    }

    void pull(int p)
    {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
        maxx[p] = max(maxx[p << 1], maxx[p << 1 | 1]);
        minn[p] = min(minn[p << 1], minn[p << 1 | 1]);
    }

    void mul(int p,i64 v)
    {
        mulTag[p] = 1ll * mulTag[p] * v;
        addTag[p] = 1ll * addTag[p] * v;
        sum[p] = 1ll * sum[p] * v;
        i64 premax = maxx[p];
        i64 premin = minn[p];
        if(v < 0)
        {
            
            maxx[p] = premin * v;
            minn[p] = premax * v;
        }
        else
        {
            maxx[p] = premax * v;
            minn[p] = premin * v;
        }
    }
    void push(int p,int l,int r)
    {
        if(hasE[p])
        {
            int m = l + r >> 1;
            applyE(p << 1, l, m, eTag[p]);
            applyE(p << 1 | 1, m + 1, r, eTag[p]);
            hasE[p] = 0;
        }
        if(mulTag[p] != 1)
        {
            mul(2 * p, mulTag[p]);
            mul(2 * p + 1,mulTag[p]);
            mulTag[p] = 1;
        }
        if(addTag[p] != 0)
        {
            int m = l + (r - l) / 2;
            applyAdd(2 * p, l, m, addTag[p]);
            applyAdd(2 * p + 1, m + 1, r, addTag[p]);
            addTag[p] = 0;
        }
    }
    i64 rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return sum[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    i64 rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y);
    }
    void rangeMul(int p,int l,int r,int x,int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
            return mul(p, v);
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeMul(2 * p, l, m, x, y, v);
        rangeMul(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeMul(int x,int y,i64 v)
    {
        rangeMul(1, 1, n, x, y, v);
    }
    void applyAdd(int p,int l,int r,i64 v)
    {
        addTag[p] = addTag[p] + v;
        sum[p] = sum[p] + 1ll * (r - l + 1) * v;
        maxx[p] += v;
        minn[p] += v;
    }
    void rangeAdd(int p,int l,int r,int x,int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyAdd(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeAdd(int x,int y,i64 v)
    {
        rangeAdd(1, 1, n, x, y, v);
    }

    void applyE(int p, int l, int r, i64 v)
    {
        sum[p] = (r - l + 1) * v;
        maxx[p] = v;
        minn[p] = v;
        addTag[p] = 0;
        mulTag[p] = 1;
        eTag[p] = v;
        hasE[p] = 1;
    }
    void rangeE(int p, int l, int r, int x, int y, i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            applyE(p, l, r, v);
            return;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        rangeE(2 * p, l, m, x, y, v);
        rangeE(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeE(int x, int y, i64 v)
    {
        rangeE(1, 1, n, x, y, v);
    }
    i64 rangeQueryMax(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return -INF;
        if(l >= x && r <= y)
            return maxx[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return max(rangeQueryMax(2 * p, l, m, x, y),  rangeQueryMax(2 * p + 1, m + 1, r, x, y));
    }
    i64 rangeQueryMax(int x,int y)
    {
        return rangeQueryMax(1, 1, n, x, y);
    }
};

void solve()
{
    string a, b;
    cin >> a >> b;

    int lena = a.size(), lenb = b.size();
    a = "*" + a, b = "*" + b;
    if(a == b)
    {
        cout << 1 << "\n";
        return;
    }

    debug(a, b);


    int ans = lena;
    for (int i = 1; i <= lena && i <= lenb;i++)
    {

    }
    vector<int> ch(26, inf);
    vector<vector<int>> nxt(lena + 1);
    int n = 26;
    for(int i = lena;i >= 1;i--)
    {
        int idx = a[i] - 'a';
        ch[idx] = i;
        nxt[i] = ch;
    }

    // for (int i = 1; i <= lena;i++)
    // {
    //     for (int j = 0; j < 26;j++)
    //         cerr << nxt[i][j] << " ";
    //     cerr << "\n";
    // }

    int cnt = 0;
    int p = 1, q = 1;
    for (; q <= lenb;q++)
    {
        debug(p, q);
        if(p > lena)
        {
            chmin(ans, cnt);
            break;
        }
        
        chmin(ans, 1 + lena - p + cnt);
        int minpos = inf;
        for (int i = 0; i < b[q] - 'a';i++)
        {
            chmin(minpos, nxt[p][i]);
        }
        chmin(ans, minpos - p + cnt);
        int nxtpos = nxt[p][b[q] - 'a'];
        if(nxtpos == inf)
            break;
        cnt += (nxtpos - p);
        p = nxtpos + 1;
    }
        // while (p <= lena && q <= lenb)
        // {
        //     debug(p, q, cnt, ans);

        //     if(a[p] == b[q])
        //     {
        //         chmin(ans, 1 + lena - p + cnt);
        //         int np = p + 1, nq = q + 1;
        //         if(np <= lena && nq <= lenb)
        //         {
        //             char c = b[nq];
        //             int minpos = inf;
        //             for (int i = 0; i < (c - 'a');i++)
        //                 chmin(minpos, nxt[np][i]);
        //             if(minpos != inf)
        //                 chmin(ans, minpos - p + cnt);
        //         }
        //         p++;
        //         q++;
        //     }
        //     else if(a[p] > b[q])
        //     {
        //         p++;
        //         cnt++;
        //     }
        //     else
        //         break;
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
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}