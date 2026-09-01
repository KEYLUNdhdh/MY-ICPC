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
bool ST;

constexpr i64 MOD = 998244353, INF = 1e9;

// 哎呦我，通信题不赖
const int c[] = {0, 3, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15, 17, 18, 19, 20, 1, 2, 4, 8, 16};

void solve(string s)
{
    if(s == "first")
    {
        int x;
        cin >> x;
        x -= 1;
        vector<int> a;
        int pre = 0;
        for (int i = 0; i <= 14;i++)
        {
            if((1 << i) & x)
                a.push_back(i + 1), pre ^= c[i + 1];
        }

        for (int i = 0; i < 5;i++)
        {
            if((1 << i) & pre)
                a.push_back(i + 16);
        }

        cout << a.size() << "\n";
        for (int k : a)
            cout << k << " ";
        cout << "\n";
    }
    else
    {
        int n;
        cin >> n;
        vector<int> a(n);
        int pre = 0;
        for (int i = 0; i < n;i++)
            cin >> a[i], pre ^= c[a[i]];

        if(n == 0)
        {
            cout << 1 << "\n";
            return;
        }
        sort(a.begin(), a.end());
        int ans = 0;
        int r = 0, l = 0;
        for (int i = 0; i < a.size();i++)
        {
            if(a[i] >= 16)
                r |= c[a[i]];
            else
                ans |= (1 << (a[i] - 1)), l ^= c[a[i]];
        }
        if(pre == 1 || pre == 2 || pre == 4 || pre == 8 || pre == 16 || pre == 0)
            ;
        else// pre 是多的，l 是真实值， r是校验
        {
            for (int i = 1; i <= 15;i++)
                if(c[i] == pre)
                {
                    ans ^= (1 << (i - 1));
                }
        }
        cout << ans + 1 << "\n";
    }
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int T = 1;
    cin >> T;
    while(T--)
        solve(s);
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
    return 0;
}