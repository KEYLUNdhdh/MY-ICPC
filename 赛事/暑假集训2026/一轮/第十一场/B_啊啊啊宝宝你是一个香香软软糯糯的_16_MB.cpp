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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, T b) { if (a > b) a = b; }
template<class T> void chmax(T &a, T b) { if (a < b) a = b; }
bool ST;

constexpr int inf = 1e9;
constexpr i64 MOD = 998244353, INF = 2e18;

/*
[a, b]: 4096 16384
[a * b]: 67108864
6e7 级别
打个表先
*/

int get_value(char c)
{
    if ('0' <= c && c <= '9')
        return c - '0';
    return c - 'A' + 10;
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> previous_label(m, 0);
    vector<int> current_label(m, 0);

    // 上一行最多约有 m/2 个活跃连通块，
    // 当前行最多再创建约 m/2 个，因此开 2m 足够。
    vector<int> parent(2 * m + 10);
    vector<int> new_id(2 * m + 10);

    vector<unsigned char> row(m);

    auto read_row = [&]()
    {
        string s;
        cin >> s;

        for (int i = 0; i < m / 4; i++)
        {
            int value = get_value(s[i]);

            for (int k = 0; k < 4; k++)
            {
                row[i * 4 + k] =
                    (value >> (3 - k)) & 1;
            }
        }
    };

    auto find = [&](auto &&self, int x) -> int
    {
        if (parent[x] == x)
            return x;

        return parent[x] = self(self, parent[x]);
    };

    int answer = 0;
    int previous_count = 0;

    for (int turn = 0; turn < n; turn++)
    {
        read_row();

        fill(current_label.begin(), current_label.end(), 0);

        // 上一行的编号已经被压缩到 [1, previous_count]
        int label_count = previous_count;

        for (int i = 1; i <= 2 * m + 5; i++)
            parent[i] = i;

        for (int j = 0; j < m; j++)
        {
            if (row[j] == 0)
                continue;

            int up = 0;
            int left = 0;

            if (previous_label[j] != 0)
            {
                up = find(find, previous_label[j]);
            }

            if (j > 0 && current_label[j - 1] != 0)
            {
                left = find(find, current_label[j - 1]);
            }

            if (up == 0 && left == 0)
            {
                // 上方和左方都没有 1，产生新连通块
                ++label_count;
                parent[label_count] = label_count;
                current_label[j] = label_count;
                answer++;
            }
            else if (up == 0)
            {
                current_label[j] = left;
            }
            else if (left == 0)
            {
                current_label[j] = up;
            }
            else
            {
                up = find(find, up);
                left = find(find, left);

                if (up != left)
                {
                    // 两个原本不同的连通块被当前格子连接
                    parent[up] = left;
                    answer--;
                }

                current_label[j] = find(find, left);
            }
        }

        // 只保留当前行仍然活跃的连通块，并把编号重新压缩。
        // 这样并查集编号不会随 n 不断增长。
        fill(new_id.begin(), new_id.end(), 0);

        int current_count = 0;

        for (int j = 0; j < m; j++)
        {
            if (current_label[j] == 0)
                continue;

            int root = find(find, current_label[j]);

            if (new_id[root] == 0)
                new_id[root] = ++current_count;

            current_label[j] = new_id[root];
        }

        previous_label.swap(current_label);
        previous_count = current_count;
    }

    cout << answer << '\n';
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