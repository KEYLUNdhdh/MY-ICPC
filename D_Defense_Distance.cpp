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
int len1, len2;
int dp[2010][2010];


int cal(string s1,string s2) {
    len1 = s1.size();
    len2 = s2.size();
    memset(dp, 0x3f, sizeof(dp));
    for (int j = 0; j <= len2; ++j)dp[0][j] = j;
    for (int i = 0; i <= len1; ++i)dp[i][0] = i;
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int add = 1;
            if (s1[i - 1] == s2[j - 1]) {
                add = 0;
            }
            dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]) + 1, dp[i - 1][j - 1] + add);
        }
    }
    return dp[len1][len2];
}

void solve()
{
    vector<int> a(3);
    cin >> a[0] >> a[1] >> a[2];
    vector<int> ori = a;
    sort(a.begin(), a.end());

    if(a[0] + a[1] < a[2])
    {
        cout << "No";
        return;
    }
    vector<string> ss(3, "");
    for (int i = 0; i < a[2];i++)
        ss[1] += 'a';
    debugarr(a);
    ss[2] = ss[1];
    for (int i = a[2] - 1; i >= a[2] - a[1];i--)
        ss[2][i] = 'b';

    while(ss[2].size() > a[0])
        ss[2].pop_back();

    for (int i = 0; i < 3;i++)
        ss[i] = 'a' + ss[i];
    debugarr(ss);

    cout << "Yes\n";
    vector<int> vec = {0, 1, 2};
    do
    {
        int i = vec[0], j = vec[1], k = vec[2];
        if(cal(ss[i], ss[j]) == ori[0] && cal(ss[i], ss[k]) == ori[1] && cal(ss[j], ss[k]) == ori[2])
        {
            cout << ss[i] << "\n" << ss[j] << "\n" << ss[k];
            return;
        }
    } while (next_permutation(vec.begin(), vec.end()));

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