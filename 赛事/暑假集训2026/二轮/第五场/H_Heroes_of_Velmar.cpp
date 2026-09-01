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

// 3 location
// 4 spots per location

// 每个location比power
// 如果二人win的location一样，比总power，还一样就tie

void solve()
{
    map<string, pii> mp;
    mp["Shadow"] = {4, 6};
    mp["Gale"] = {3, 5};
    mp["Ranger"] = {2, 4};
    mp["Anvil"] = {5, 7};
    mp["Vexia"] = {2, 3};
    mp["Guardian"] = {6, 8};
    mp["Thunderheart"] = {5, 6};
    mp["Frostwhisper"] = {1, 2};
    mp["Voidclaw"] = {1, 3};
    mp["Ironwood"] = {1, 3};
    mp["Zenith"] = {6, 4};
    mp["Seraphina"] = {1, 1};
    i64 win1 = 0, win2 = 0;
    i64 p1 = 0, p2 = 0;

    for (int ttt = 0; ttt < 3;ttt++)
    {
        int iscenter = 0;
        if(ttt == 1)
            iscenter = 1;
        int n;
        cin >> n;
        int is1 = 0, it1 = 0, iz1 = 0;
        int curp1 = 0;
        vector<string> a;
        for (int i = 0; i < n;i++)
        {
            string s;
            cin >> s;
            if(s == "Seraphina")
                is1++;
            else if(s == "Thunderheart")
                it1++;
            else if(s == "Zenith")
                iz1++;

            int pp = mp[s].second;
            curp1 += pp;
            a.push_back(s);
        }

        if(n == 4)
            curp1 += it1 * 6;
        if(iscenter)
            curp1 += iz1 * 5;
        curp1 += (n - 1) * is1;

        p1 += curp1;
        a.clear();
        cin >> n;
        int is2 = 0, it2 = 0, iz2 = 0;
        int curp2 = 0;
        for (int i = 0; i < n;i++)
        {
            string s;
            cin >> s;
            if(s == "Seraphina")
                is2++;
            else if(s == "Thunderheart")
                it2++;
            else if(s == "Zenith")
                iz2++;

            int pp = mp[s].second;
            curp2 += pp;
        }

        if(n == 4)
            curp2 += it2 * 6;
        if(iscenter)
            curp2 += iz2 * 5;
        curp2 += (n - 1) * is2;
        p2 += curp2;

        if(curp1 > curp2)
            win1++;
        else if(curp1 < curp2)
            win2++;
    }

    if(win1 != win2)
    {
        if(win1 > win2)
            cout << "Player 1";
        else
            cout << "Player 2";
    }
    else
    {
        if(p1 > p2)
            cout << "Player 1";
        else if(p1 < p2)
            cout << "Player 2";
        else
            cout << "Tie";
    }
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