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

struct KMP
{
    vector<int> pi;
    void build(const vector<string>& p)
    {
        int m = p.size();
        pi.assign(m, 0);
        for (int i = 1, j = 0; i < m;i++)
        {
            while(j > 0 && p[i] != p[j])
                j = pi[j - 1];
            if(p[i] == p[j])
                j++;
            pi[i] = j;
        }
    }

    vector<int> match(const vector<string>& s, const vector<string>& p)
    {
        int n = s.size();
        int m = p.size();
        vector<int> res;
        for (int i = 0, j = 0; i < n;i++)
        {
            while(j > 0 && s[i] != p[j])
                j = pi[j - 1];
            if(s[i] == p[j])
                j++;
            if(j == m)
            {
                res.push_back(i - m + 2);
                j = pi[j - 1];
            }
        }
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    cin.ignore();
    vector<string> s, oris;
    for (int i = 0; i < n;i++)
    {
        string p;
        cin >> p;       
        if(p.size() == 1 && ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z')))
        {
            s.push_back("*");
            oris.push_back(p);
        }
        else
            s.push_back(p), oris.push_back(p);
    }
    int q;
    cin >> q;
    KMP kmp;
    while(q--)
    {
        int len;
        cin >> len;
        cin.ignore();
        vector<string> k, orik;
        vector<int> posk;
        for (int i = 0; i < len;i++)
        {
            string p;
            cin >> p;
            if(p.size() == 1 && ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z')))
            {
                k.push_back("*");
                orik.push_back(p);
                posk.push_back(i);
            }
            else
                k.push_back(p), orik.push_back(p);
        }
        debugarr(k, s);
        kmp.build(k);
        vector<int> res = kmp.match(s, k);
        vector<char> revmpk, mpk;
        debugarr(res);
        int ok = 0;
        for(int pos : res)
        {
            revmpk.assign(256, 0);
            mpk.assign(256, 0);
            pos--;
            int f = 1;
            for (int i : posk)
            {
                debug(orik[i], oris[i + pos]);
                if(!revmpk[oris[i + pos][0]] && !mpk[orik[i][0]])
                {
                    revmpk[oris[i + pos][0]] = orik[i][0];
                    mpk[orik[i][0]] = oris[i + pos][0];
                }
                else
                {
                    if(revmpk[oris[i + pos][0]] != orik[i][0] || mpk[orik[i][0]] != oris[i + pos][0])
                    {
                        f = 0;
                        break;
                    }
                }
            }
            if(f)
            {
                ok = 1;
                cout << "yes\n";
                break;  
            }
        }
        if(!ok)
            cout << "no\n";
        cutline
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