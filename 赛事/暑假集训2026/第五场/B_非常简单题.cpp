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

void solve()
{
    int n;
    cin >> n;

    if(n == 1)
    {
        cout << 1 << "\n";
        return;
    }

    int cnt = 0;
    vector<int> a, b;
    vector<int> res(n + 1, -1);
    vector<int> nxt(n + 1, INF);
    for (int i = 1; i <= n; i++)
        cin >> res[i];
    map<int, int> mp;
    for (int i = n; i >= 1;i--)
    {
        int num = res[i];
        if(!mp[num])
            mp[num] = i;
        else
            nxt[i] = mp[num], mp[num] = i;
    }

    // debugarr(nxt) 

    for (int i = 1; i <= n;i++)
    {
        if(a.empty())
            a.push_back(i), cnt++;
        else if(res[a.back()] == res[i])
            a.push_back(i);
        else if(b.empty())
            b.push_back(i), cnt++;
        else if (res[b.back()] == res[i])   
            b.push_back(i);
        else
        {
            int nxa = nxt[a.back()], nxb = nxt[b.back()];
            if(nxa < nxb)
                b.push_back(i);
            else
                a.push_back(i);
            cnt++;
        }
    }
    // for(int)
    cout << cnt;
}

bool ED;
signed lyc_fan_club()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while(T--)
        solve();
    cerr<<"time used: "<<(double)clock()/CLOCKS_PER_SEC<< endl;
    cerr<<"memory used: "<<abs(&ST-&ED)/1024.0/1024.0<<" MB"<< endl;
    return 0;
}