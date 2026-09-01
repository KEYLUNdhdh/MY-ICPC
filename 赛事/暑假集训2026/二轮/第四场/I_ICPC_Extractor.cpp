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
    string s;
    cin >> s;
    int len = s.size();
    s = "*" + s;
    vector<vector<int>> stk(3);
    vector<int> sufc(len + 2, 0), sufp(len + 2, 0), nxtc(len + 1, -1);
    vector<int> pre(len + 1, -1);
    vector<int> vis(len + 1, 0);
    sufc[len] = (s[len] == 'C' ? 1 : 0);
    sufp[len] = (s[len] == 'P' ? 1 : 0);

    for (int i = len - 1; i >= 1;i--)
    {
        sufc[i] = sufc[i + 1] + (s[i] == 'C' ? 1 : 0);
        sufp[i] = sufp[i + 1] + (s[i] == 'P' ? 1 : 0);
    }
    for (int i = len - 1; i >= 1;i--)
    {
        if(s[i + 1] == 'C')
            nxtc[i] = i + 1;
        else
            nxtc[i] = nxtc[i + 1];
    }
        int cnt = 0;

    // nxtc possibly be -1
    // 0 I
    // 1 IC
    // 2 ICP
    for (int i = 1; i <= len;i++)
    {
        char c = s[i];
        if(c == 'I')
            stk[0].push_back(i);
        else if(c == 'P' && !stk[1].empty())
        {
            int b = stk[1].back();
            stk[1].pop_back();
            stk[2].push_back(i);
            pre[i] = b;
        }
        else if(c == 'C')
        {
            // IC P && (ICP + IC) < C
            if(stk[1].size() < sufp[i + 1] && ((stk[1].size() + stk[2].size()) < sufc[i + 1]))
            {
                if(!stk[0].empty())
                {
                        int a = stk[0].back();
                        stk[0].pop_back();
                        pre[i] = a;
                        stk[1].push_back(i);
                }
                else if(!stk[2].empty())
                {
                    int b = stk[2].back();
                    stk[2].pop_back();
                    vis[i] = 1;
                    pre[i] = b;
                    cnt++;
                }
            }
            else if(!stk[2].empty())
            {
                int b = stk[2].back();
                stk[2].pop_back();
                vis[i] = 1;
                pre[i] = b;
                cnt++;
            }

            // if(stk[0].empty() && stk[2].empty())
            //     continue;

            // // stk[0] have
            // int nc = nxtc[i];
            // if(nc == -1)
            // {
            //     if(!stk[2].empty())
            //     {
            //         int b = stk[2].back();
            //         stk[2].pop_back();
            //         vis[i] = 1;
            //         pre[i] = b;
            //         cnt++;
            //     }
            //     continue;
            // }
            // else if(!stk[0].empty())
            // {
            //     int midp = sufp[i] - sufp[nc];
            //     // 假设分给 I
            //     int midicp = min<int>(midp, (int)stk[1].size() + 1);
            //     // 得到的新的 ICP
            //     int total = midicp + stk[2].size();
            //     // 充足或者本就不能分给 ICP
            //     if((sufc[i] - 1 >= total) || (stk[2].empty()))
            //     {
            //         int a = stk[0].back();
            //         stk[0].pop_back();
            //         pre[i] = a;
            //         stk[1].push_back(i);
            //     }
            //     else if(!stk[2].empty())
            //     {
            //         int b = stk[2].back();
            //         stk[2].pop_back();
            //         vis[i] = 1;
            //         pre[i] = b;
            //         cnt++;
            //     }
            // }
            // // I 为空 ICP 有
            // else
            // {
            //     int b = stk[2].back();
            //     stk[2].pop_back();
            //     vis[i] = 1;
            //     pre[i] = b;
            //     cnt++;
            // }
            // if(!stk[2].empty() && sufc[i] <= stk[2].size())
            // {
            //     int b = stk[2].back();
            //     stk[2].pop_back();
            //     vis[i] = 1;
            //     pre[i] = b;
            //     cnt++;
            // }
            // else if(!stk[0].empty())
            // {
            //     int a = stk[0].back();
            //     stk[0].pop_back();
            //     pre[i] = a;
            //     stk[1].push_back(i);
            // }
        }
    }

    cout << cnt << "\n";
    for (int i = len; i >= 1;i--)
    {
        if(vis[i])
        {
            int d = i;
            int c = pre[d];
            int b = pre[c];
            int a = pre[b];
            cout << a << " " << b << " " << c << " " << d << "\n";
        }
    }
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