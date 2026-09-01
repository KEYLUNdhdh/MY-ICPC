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

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct BigInt
{
    vector<int> vec;
    BigInt(i64 x = 0)
    {
        if(x == 0)
            vec.push_back(0);
        while(x)
        {
            vec.push_back(x % 10);
            x /= 10;
        }
    }
    BigInt(string s)
    {
        for (int i = s.size() - 1; i >= 0;i--)
        {
            vec.push_back(s[i] - '0');
        }
        trim();
    }
    void trim()
    {
        while(vec.size() > 1 && vec.back() == 0)
            vec.pop_back();
    }
    bool operator<(const BigInt& b) const
    {
        if(vec.size() != b.vec.size())
            return vec.size() < b.vec.size();
        for (int i = vec.size() - 1; i >= 0;i--)
        {
            if(vec[i] != b.vec[i])
                return vec[i] < b.vec[i];
        }
        return false;
    }
    bool operator>(const BigInt &b) const { return b < *this; }
    bool operator<=(const BigInt &b) const { return !(*this > b); }
    bool operator>=(const BigInt &b) const { return !(*this < b); }
    bool operator==(const BigInt &b) const { return vec == b.vec; }
    bool operator!=(const BigInt &b) const { return vec != b.vec; }
    BigInt operator+=(const BigInt& b)
    {
        int t = 0;
        for (int i = 0; i < max(vec.size(), b.vec.size()) || t;i++)
        {
            if(i == vec.size())
                vec.push_back(0);
            vec[i] += t + (i < b.vec.size() ? b.vec[i] : 0);
            t = vec[i] / 10;
            vec[i] %= 10;
        }
        trim();
        return *this;
    }
    friend BigInt operator+(BigInt a,const BigInt& b)
    {
        a += b;
        return a;
    }
    //promise *this > b
    BigInt operator-=(const BigInt& b)
    {
        int t = 0;
        for (int i = 0; i < b.vec.size() || t;i++)
        {
            vec[i] -= t + (i < b.vec.size() ? b.vec[i] : 0);
            if(vec[i] < 0)
            {
                vec[i] += 10;
                t = 1;
            }
            else
                t = 0;
        }
        trim();
        return *this;
    }
    friend BigInt operator-(BigInt a,const BigInt& b)
    {
        a -= b;
        return a;
    }
    friend BigInt operator*(const BigInt& a,const BigInt& b)
    {
        if((a.vec.size() == 1 && a.vec[0] == 0) || (b.vec.size() == 1 && b.vec[0] == 0))
        return BigInt(0);
        BigInt res(0);
        res.vec.assign(a.vec.size() + b.vec.size() + 5, 0);
        for (int i = 0; i < a.vec.size();i++)
        {
            for (int j = 0; j < b.vec.size();j++)
            {
                res.vec[i + j] += a.vec[i] * b.vec[j];
                res.vec[i + j + 1] += res.vec[i + j] / 10;
                res.vec[i + j] %= 10;
            }
        }
        res.trim();
        return res;
    }
    //BigInt  * int (int comes later)
    BigInt operator*(int b) const 
    {
        if(b == 0)
            return BigInt(0);
        BigInt res = *this;
        int t = 0;
        for (int i = 0; i < res.vec.size() || t;i++)
        {
            if(i == res.vec.size())
                res.vec.push_back(0);
            i64 cur = 1ll * res.vec[i] * b + t;
            res.vec[i] = cur % 10;
            t = cur / 10;
        }
        res.trim();
        return res;
    }
    BigInt &operator*=(const BigInt b) &
    {
        *this = *this * b;
        return *this;
    }
    //返回{商，余数}
    static pair<BigInt,BigInt> divmod(BigInt a,const BigInt& b)
    {
        if(a < b)
            return {BigInt{0}, a};
        BigInt q(0), r(0);
        q.vec.assign(a.vec.size(), 0);
        for (int i = a.vec.size() - 1; i >= 0;i--)
        {
            r = r * 10 + a.vec[i];
            int cnt = 0;
            while(r >= b)
            {
                r -= b;
                cnt++;
            }
            q.vec[i] = cnt;
        }
        q.trim();
        return {q, r};
    }
    friend BigInt operator/(BigInt& a,BigInt& b)
    {
        return divmod(a, b).first;
    }
    friend BigInt operator%(BigInt& a,BigInt& b)
    {
        return divmod(a, b).second;
    }
    BigInt operator/=(const BigInt& b)
    {
        *this = divmod(*this, b).first;
        return *this;
    }
    BigInt operator%=(const BigInt& b)
    {
        *this = divmod(*this, b).second;
        return *this;
    }
    friend BigInt qpow(BigInt a,int m)
    {
        BigInt res(1);
        while(m)
        {
            if(m & 1)
                res = res * a;
            a = a * a;
            m >>= 1;
        }
        return res;
    }
    friend ostream& operator<<(ostream& os,const BigInt& a)
    {
        for (int i = a.vec.size() - 1; i >= 0;i--)
            os << a.vec[i];
        return os;
    }
    friend istream& operator>>(istream& is,BigInt& a)
    {
        string s;
        if(!(is >> s))
            return is;
        a = BigInt(s);
        return is;
    }
};


const int N = 300010;
const double PI = acos(-1);

int rev[N], bit, tot;

struct complexs {
    double x, y;
    complexs operator+(const complexs& t)const {
        return { x + t.x,y + t.y };
    }
    complexs operator-(const complexs& t)const {
        return { x - t.x,y - t.y };
    }
    complexs operator*(const complexs& t)const {
        return{ x * t.x - y * t.y,x * t.y + y * t.x };
    }
}a[N], b[N];

void fft(complexs a[], int inv) {
    for (int i = 0; i < tot; ++i) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int mid = 1; mid < tot; mid *= 2) {
        auto w1 = complexs{ cos(PI / mid),inv * sin(PI / mid) };
        for (int i = 0; i < tot; i += 2 * mid) {
            auto wk = complexs{ 1,0 };
            for (int j = 0; j < mid; ++j, wk = wk * w1) {
                auto x = a[i + j], y = a[i + j + mid];
                a[i + j] = x + wk * y, a[i + j + mid] = x - wk * y;
            }
        }
    }
}
int res[N];


string cal(string s1, string s2) {
    // string s1, s2;
    // cin >> s1 >> s2;
    int n = s1.size() - 1, m = s2.size() - 1;
    for (int i = 0; i <= n; ++i)a[i].x = s1[n - i] - '0';
    for (int i = 0; i <= m; ++i)b[i].x = s2[m - i] - '0';
    while ((1 << bit) < m + n + 1)bit++;
    tot = 1 << bit;
    for (int i = 0; i < tot; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
    }
    fft(a, 1);
    fft(b, 1);
    for (int i = 0; i <= tot; ++i)a[i] = a[i] * b[i];
    int t = 0;
    int k = 0;
    fft(a, -1);
    for (int i = 0; i <= n + m + 1 || t; i++) {
        t += a[i].x / tot + 0.5;
        res[k++] = t % 10;
        t /= 10;
    }
    while (k > 1 && !res[k - 1]) k--;
    string ans;
    for (int i = k - 1; i >= 0; --i)ans += char('0' + res[i]);
    return ans;
}

void solve()
{
    string s;
    string cc;
    cin >> s >> cc;
    
    BigInt c(cc);
    int n = s.size();
    int m = c.vec.size();

    //1
    int x;
    if((n - m) % 2 == 0)
    {
        x = (n - m) / 2;
        string aa = s.substr(0, x + m);
        string bb = s.substr(x + m);
        string res = cal(bb, cc);
        BigInt rres(res);
        if(rres == aa)
        {
            cout << aa << " " << bb;
            return;
        }
    }

    x = (n - m - 1) / 2;
    string aa = s.substr(0, x + m);
    string bb = s.substr(x + m);
    cout << aa << " " << bb;
    return;
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