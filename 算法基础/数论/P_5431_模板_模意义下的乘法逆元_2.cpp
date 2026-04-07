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
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
typedef pair<i128, i128> pllll;

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
inline i64 read()
{
	char ch;
	ch = getchar();
	//ch = getchar_unlocked();
	i64 f = 1;
	while (ch > '9' || ch < '0')
	{
		if (ch == '-') f = -1;
		ch = getchar();
		//ch = getchar_unlocked();
	}
	i64 k = 0;
	while (ch >= '0' && ch <= '9')
	{
		k = k * 10 + (ch - '0');
		ch = getchar();
		//ch = getchar_unlocked();
	}
	return k * f;
}
inline void out(i64 x)
{
	char ch;
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else out(x / 10), putchar(x % 10 + '0');
}
i64 qpow(i64 a, i64 b, i64 p)
{
    a %= p;
    i64 res = 1;
    while(b)
    {
        if(b & 1)
            res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

i64 inv(i64 n,i64 p)
{
    return qpow(n, p - 2, p);
}

void solve()
{
    i64 n, p, k;
    n = read(), p = read(), k = read();
    i64 prefix = 1, g = 1;
    i64 ans = 0;
    vector<i64> vec(n + 1, 0), pre(n + 1, 1), bac(n + 1, 1);
    for (int i = 1; i <= n;i++)
    {
        vec[i] = read();
        prefix = prefix * vec[i] % p;
        pre[i] = pre[i - 1] * vec[i] % p;
    }
    bac[n] = vec[n] % p;
    for (int i = n - 1; i >= 1;i--)
    {
        bac[i] = bac[i + 1] * vec[i] % p;
    }
    int invv = inv(prefix, p);
    for (int i = 1; i <= n;i++)
    {
        g = g * k % p;
        ans = (ans + g * pre[i - 1] % p * (i == n ? 1ll : bac[i + 1] % p)) % p;
    }
    ans = ans % p * invv % p;
    out(ans);
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