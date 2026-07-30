#include <bits/stdc++.h>
#define lyc_fan_club main
#ifndef ONLINE_JUDGE
#define debug(x) { cerr << #x << " = " << x << "\n"; }
#define debugarr(x) {       \
    cerr << #x << " : ";    \
    for(auto v : x)         \
        cerr << v << " ";   \
    cerr << "\n";           \
}
#define cutline { cerr << "----------------------\n"; }
#else
#define debug(x)
#define debugarr(x)
#define cutline
#endif
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
// bool ST;

ostream &operator<<(ostream &os, i128 n) {
    string s;
    int f = 0;
    if(n == 0)
        s = "0";
    if(n < 0)
    {
        f = 1;
        n = -n;
    }
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    reverse(s.begin(), s.end());
    if(f)
        s = '-' + s;
    return os << s;
}

istream &operator>>(istream &is,i128 &n)
{
    n = 0;
    string s;
    is >> s;
    int sign = 1, start = 0;
    if(s[0] == '-')
    {
        sign = -1;
        start = 1;
    }
    for (int i = start; i < s.size();i++)
    {
        n = n * 10 + s[i] - '0';
    }
    n *= sign;
    return is;
}

constexpr long long MOD = 1e9 + 7, INF = 1e9;
//使用掩码维护
// 太几把变态了
vector<i64> primes,isPrime;
vector<i64> precom(301, 0);
void sieve(int n)
{
	isPrime.assign(n + 1, 1);
	isPrime[1] = 0;
	for (int i = 2; i <= n; ++i)
	{
		if (isPrime[i])
			primes.push_back(i);
		for (auto p : primes)
		{
			if(i * p > n)
				break;
			isPrime[i * p] = 0;
			if(i % p == 0)
				break;
		}
	}

    for (int i = 1; i <= 300;i++)
    {
        for (int j = 0; j <= 61;j++)
            if(i % primes[j] == 0)
                precom[i] |= (1ll << j);
    }
}

constexpr i64 qpow(i64 a,i64 b)
{
    i64 res = 1;
    a = (a % MOD + MOD) % MOD;
    while(b)
    {
        if(b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res % MOD;
}

i64 inv(i64 a)
{
    return qpow(a, MOD - 2);
}

i64 phi(i64 mask, i64 n)
{
    // i64 res = n;
    i64 res = n;
    debug(n)
    debug(mask)
    for (int i = 0; i <= 61;i++)
    {

        if((1ll << i) & mask)
        {
            i64 num = primes[i];
            debug(num)
            res = res * (num - 1) % MOD * inv(num) % MOD;
        }
    }
    // if(n > 1)
    //     res = res * (n - 1) % MOD * inv(n) % MOD;
    debug(res)
    return res % MOD;
}


struct SegmentTree
{
    int n;
    vector<i64> mulTag, m, msk, mskTag;
    SegmentTree(int n_) : n{n_}, mulTag(4 * n + 1, 1), m(4 * n + 1, 1), msk(4 * n + 1, 0), mskTag(4 * n + 1, 0){}

    void init(int p, int l, int r, const vector<i64> &a)
    {   
        if(l == r)
        {
            m[p] = a[l] % MOD;
            msk[p] |= precom[a[l]];
            debug(a[l])
            debug(msk[p])
            debug(m[p])
            return;
        }
        int m = l + r >> 1;
        init(p << 1, l, m, a);
        init(p << 1 | 1, m + 1, r, a);
        pull(p);
    }

    void pull(int p)
    {
        m[p] = (m[p << 1] * m[p << 1 | 1]) % MOD;
        msk[p] = (msk[p << 1] | msk[p << 1 | 1]);
    }

    void mul(int p, int l, int r, i64 v)
    {
        i64 len = r - l + 1;
        mulTag[p] = 1ll * mulTag[p] * v % MOD;
        m[p] = 1ll * m[p] * qpow(v, len) % MOD;
        debug(m[p])
    }
    
    void mk(int p, int l, int r, i64 v)
    {
        msk[p] |= v;
        mskTag[p] |= v;
    }

    void push(int p,int l,int r)
    {
        int m = l + r >> 1;
        if(mulTag[p] != 1)
        {
            mul(2 * p, l, m, mulTag[p]);
            mul(2 * p + 1, m + 1, r, mulTag[p]);
            mulTag[p] = 1;
        }
        if(mskTag[p] != 0)
        {
            mk(p << 1, l, m, mskTag[p]);
            mk(p << 1 | 1, m + 1, r, mskTag[p]);
            mskTag[p] = 0;
        }
    }

    i64 rangeQuery(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 1;
        if(l >= x && r <= y)
        {
            return m[p] % MOD;
        }
        int m = l + (r - l) / 2;
        push(p, l, r);
        return (rangeQuery(2 * p, l, m, x, y) * rangeQuery(2 * p + 1, m + 1, r, x, y)) % MOD;
    }

    i64 rangeQuery(int x,int y)
    {
        return rangeQuery(1, 1, n, x, y) % MOD;
    }

    i64 rangeQuerymk(int p,int l,int r,int x,int y)
    {
        if(l > y || r < x)
            return 0;
        if(l >= x && r <= y)
            return msk[p];
        int m = l + (r - l) / 2;
        push(p, l, r);
        return (rangeQuerymk(2 * p, l, m, x, y) | rangeQuerymk(2 * p + 1, m + 1, r, x, y));
    }

    i64 rangeQuerymk(int x,int y)
    {
        return rangeQuerymk(1, 1, n, x, y);
    }

    void rangeMul(int p,int l,int r,int x,int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            debug(n)
            mul(p, l, r, v);
            debugarr(m)
            return;
        }
        int m = l + (r - l) / 2;
        debug(n)
        push(p, l, r);
        rangeMul(2 * p, l, m, x, y, v);
        rangeMul(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeMul(int x,int y,i64 v)
    {
        rangeMul(1, 1, n, x, y, v);
    }

    void rangeMk(int p,int l,int r,int x,int y,i64 v)
    {
        if(l > y || r < x)
            return;
        if(l >= x && r <= y)
        {
            debug(n)
            mk(p, l, r, v);
            debugarr(m)
            return;
        }
        int m = l + (r - l) / 2;
        debug(n)
        push(p, l, r);
        rangeMk(2 * p, l, m, x, y, v);
        rangeMk(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeMk(int x,int y,i64 v)
    {
        rangeMk(1, 1, n, x, y, v);
    }
};
// 为什么
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<i64> a(n + 1, 0);
    for (int i = 1; i <= n;i++)
        cin >> a[i];

    debugarr(a)
    SegmentTree seg(n);
    seg.init(1, 1, n, a);
    debugarr(seg.m)
    while(q--)
    {
        string s;
        cin >> s;
        if(s == "TOTIENT")
        {
            int l, r;
            cin >> l >> r;
            i64 ans = seg.rangeQuery(l, r);
            i64 mask = seg.rangeQuerymk(l, r);
            debug(mask)
            debug(ans)
            debugarr(seg.m)
            debugarr(seg.msk)
            cout << phi(mask, ans) << "\n";
        }
        else
        {
            int l, r;
            i64 x;
            cin >> l >> r >> x;
            seg.rangeMul(l, r, x);
            i64 v = precom[x];
            seg.rangeMk(l, r, v);
        }
        cutline
    }
}

// bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    sieve(300);
    debug(primes.size())
    debugarr(primes)
    debugarr(precom)
    debug(precom[293])
    debug(primes[61])
    // cin >> T;
    while(T--)
        solve();
    // cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    // cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}