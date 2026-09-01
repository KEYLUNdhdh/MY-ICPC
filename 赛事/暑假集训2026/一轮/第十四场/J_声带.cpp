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

void solve()
{
    i64 mx, my;
    cin >> mx >> my;

    string s;
    cin >> s;

    vector<int> cnt(4, 0);
    for (int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if(c == 'U')
            cnt[0]++;
        else if(c == 'D')
            cnt[1]++;
        else if(c == 'L')
            cnt[2]++;
        else
            cnt[3]++;
    }

    vector<int> vec = {0, 1, 2, 3};
    i64 mvx = cnt[3] - cnt[2], mvy = cnt[0] - cnt[1];
    debug(mvx, mvy, mx, my);
    if(mx == 0 && my == 0)
    {
        cout << "Impossible\n";
        return;
    }
    // if(mvx == mx && mvy == my)
    // {
    //     cout << "Impossible\n";
    //     return;
    // }

    // if(mvx == 0)
    // {
    //     if(abs(mvy) >= abs(my) && mx == 0)
    //     {
    //         cout << "Impossible\n";
    //         return;
    //     }
    // }
    // if(mvy == 0)
    // {
    //     if(abs(mvx) >= abs(mx) && my == 0)
    //     {
    //         cout << "Impossible\n";
    //         return; 
    //     }
    // }
    debug(mx);
    cutline
    map<int, char> mp;
    mp[0] = 'U';
    mp[1] = 'D';
    mp[2] = 'L';
    mp[3] = 'R';
    int count = 0;
    do{
        debugarr(vec);
        int f = 1;
        int curx = 0, cury = 0;
        int count = 0;
        string str = "";
        for (int i = 0; i < 4;i++)
        {
            int num = cnt[vec[i]];
            // debug(st, num);
            for (int j = 0; j < num;j++)
            {
                str += mp[vec[i]];
                if(vec[i] == 0)
                    cury++;
                else if(vec[i] == 1)
                    cury--;
                else if(vec[i] == 2)
                    curx--;
                else
                    curx++;
                if(curx == mx && cury == my)
                {
                    f = 0;
                    break;
                }
            }
            count++;
        }
        if (f)
        {
            cout << str << "\n";
            return;
        }
        count++;
    } while (next_permutation(vec.begin(), vec.end()) && count <= 50);
    cout << "Impossible\n";
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    cin >> T;
    while(T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}