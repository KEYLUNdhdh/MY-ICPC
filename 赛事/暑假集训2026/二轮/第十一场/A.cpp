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
void debug_out(Head H, Tail... T)
{
    cerr << " " << H;
    debug_out(T...);
}
#define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
void debugarr_out(const char *names) {}
template <typename Head, typename... Tail>
void debugarr_out(const char *names, Head H, Tail... T)
{
    while (*names == ' ' || *names == ',')
        names++;
    int bracket = 0, i = 0;
    for (; names[i]; ++i)
    {
        if (names[i] == '(' || names[i] == '{' || names[i] == '[')
            bracket++;
        else if (names[i] == ')' || names[i] == '}' || names[i] == ']')
            bracket--;
        else if (names[i] == ',' && bracket == 0)
            break;
    }
    cerr.write(names, i);
    cerr << " : ";
    for (auto v : H)
        cerr << v << " ";
    cerr << "\n";

    debugarr_out(names + i + 1, T...);
}
#define cutline                             \
    {                                       \
        cerr << "----------------------\n"; \
    }
#else
#define debug(...)
#define debugarr(...)
#define cutline
#endif
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t)new char);
template <class T>
void chmin(T &a, T b)
{
    if (a > b)
        a = b;
}
template <class T>
void chmax(T &a, T b)
{
    if (a < b)
        a = b;
}
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<string> ss;
    for (int i = 0; i < s.size();)
    {
        if(isdigit(s[i]))
        {
            string t = "";
            while(isdigit(s[i]))
            {
                t += s[i];
                i++;
            }
            ss.push_back(t);
        }
        else
        {
            string t = "";
            t += s[i];
            ss.push_back(t);
            i++;
        }
    }
    debugarr(ss);
    for (int tt = 1; tt <= n;tt++)
    {
        string p;
        cin >> p;
        vector<string> pp;
        for (int i = 0; i < p.size();)
        {
            if (isdigit(p[i]))
            {
                string t = "";
                while (isdigit(p[i]))
                {
                    t += p[i];
                    i++;
                }
                pp.push_back(t);
            }
            else
            {
                string t = "";
                t += p[i];
                pp.push_back(t);
                i++;
            }
        }
        if(ss == pp)
        {
            cout << "+\n";
            continue;
        }
        debugarr(pp);
        int i = 0;
        while(i < ss.size() && i < pp.size())
        {
            string a = ss[i], b = pp[i];
            debug(a, b);
            if(isdigit(a[0]) && isdigit(b[0]))
            {
                int aa = stoi(a), bb = stoi(b);
                debug(aa, bb);
                if(aa < bb)
                {
                    cout << "+\n";
                    break;
                }
                else if(aa > bb)
                {
                    cout << "-\n";
                    break;
                }
            }
            else if (!isdigit(a[0]) && isdigit(b[0]))
            {
                cout << "-\n";
                break;
            }
            else if (isdigit(a[0]) && !isdigit(b[0]))
            {
                cout << "+\n";
                break;
            }
            else
            {
                if(a[0] < b[0])
                {
                    cout << "+\n";
                    break;
                }
                else if(a[0] > b[0])
                {
                    cout << "-\n";
                    break;
                }
            }
            i++;
        }
        debugarr(pp);

        if(i == ss.size() || i == pp.size())
        {
            if(ss.size() > pp.size())
            {
                cout << "-\n";
                continue;
            }
            else if(pp.size() > ss.size())
            {
                cout << "+\n";
                continue;
            }
        }
        // assert(false);
    }
}

bool ED;
signed KEYLUN()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
#ifndef ONLINE_JUDGE
    cerr << "\n---------------------------\n";
    cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << " s" << endl;
    cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
#endif
    return 0;
}