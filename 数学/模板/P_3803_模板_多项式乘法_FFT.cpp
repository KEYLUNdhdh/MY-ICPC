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
using i128 = __int128;
using db = double;

const db PI = acos(-1.0);

struct Complex
{
    db x, y;
    Complex(db x_ = 0., db y_ = 0.) : x(x_), y(y_) {}
    
    Complex operator+(const Complex &other) const
    {
        return Complex(x + other.x, y + other.y);
    }

    Complex operator-(const Complex &other) const
    {
        return Complex(x - other.x, y - other.y);
    }

    Complex operator*(const Complex &other) const
    {
        return Complex(x * other.x - y * other.y, x * other.y + y * other.x);
    }
};

struct FFT
{
    vector<int> rev;

    void initRev(int n)
    {
        rev.assign(n, 0);
        for (int i = 0; i < n;i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }

    void dft(vector<Complex> &a, int flag)
    {
        int n = a.size();
        for (int i = 0;i < n;i++)
            if(i < rev[i])
                swap(a[i], a[rev[i]]);

        for (int len = 2; len <= n;len <<= 1)
        {
            int half = len >> 1;
            Complex wn(cos(2 * PI / len), flag * sin(2 * PI / len));
            for (int i = 0; i < n;i += len)
            {
                Complex w(1., 0.);
                for (int j = 0; j < half;j++)
                {
                    Complex u = a[i + j];
                    Complex v = a[i + j + half] * w;
                    a[i + j] = u  + v;
                    a[i + j + half] = u - v;
                    w = w * wn;
                }
            }
        }

        if(flag == -1)
            for (int i = 0;i < n;i++)
                a[i].x /= n;
    }

    vector<i64> polyMul(const vector<i64> &A, const vector<i64> &B)
    {
        int n = A.size();
        int m = B.size();

        int len = 1;
        while(len < n + m - 1)
            len <<= 1;

        initRev(len);
        vector<Complex> fa(len), fb(len);

        for (int i = 0; i < n;i++)
            fa[i] = Complex(A[i], 0);

        for (int i = 0; i < m;i++)
            fb[i] = Complex(B[i], 0);

        dft(fa, 1);
        dft(fb, 1);

        for (int i = 0; i < len;i++)
            fa[i] = fa[i] * fb[i];

        dft(fa, -1);
        vector<i64> res(n + m - 1);
        for (int i = 0; i < n + m - 1;i++)
            res[i] = (i64)(fa[i].x + 0.5);

        return res;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1), b(m + 1);
    for (int i = 0; i <= n;i++)
        cin >> a[i];

    for (int i = 0; i <= m;i++)
        cin >> b[i];

    FFT fft;
    vector<i64> res = fft.polyMul(a, b);
    for (int i = 0; i <= n + m;i++)
        cout << res[i] << " ";

    
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