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

struct Student
{
    string name;
    int a1, b1, c1;
    int a2, b2, c2;
    int pts;
    int comp_total() const { return (a1 + b1 + c1) + (a2 + b2 + c2); }
    int acad_total() const { return a1 + a2; }
};

bool check(vector<Student> stu, int d1, int d2, int n, int m)
{
    if (m == 0)
        return false; // 如果省奖名额为0，直接返回false

    int zhk = -1;
    for (int i = 0; i < n; i++)
    {
        if (stu[i].name == "crazyzhk")
        {
            zhk = i;
            stu[i].a1 += d1;
            stu[i].a2 += d2;
            break;
        }
    }
    if (zhk == -1)
        return false;

    auto calc_term = [&](auto get_a, auto get_b, auto get_c)
    {
        vector<int> ac;
        for (int i = 0; i < n; i++)
            ac.push_back(get_a(stu[i]));
        sort(ac.rbegin(), ac.rend());

        int r1 = 0.25 * n, r2 = 0.45 * n, r3 = 0.75 * n;

        int thres1 = r1 > 0 ? ac[r1 - 1] : inf;
        int thres2 = r2 > 0 ? ac[r2 - 1] : inf;
        int thres3 = r3 > 0 ? ac[r3 - 1] : inf;

        int q1 = 0.15 * n, q2 = 0.25 * n, q3 = 0.35 * n;

        vector<int> id(n);
        iota(id.begin(), id.end(), 0);

        sort(id.begin(), id.end(), [&](int i, int j)
             {
            int c_i = get_a(stu[i]) + get_b(stu[i]) + get_c(stu[i]);
            int c_j = get_a(stu[j]) + get_b(stu[j]) + get_c(stu[j]);
            if (c_i != c_j) return c_i > c_j;
            if (get_a(stu[i]) != get_a(stu[j])) return get_a(stu[i]) > get_a(stu[j]);
            return stu[i].name < stu[j].name; });

        for (int i : id)
        {
            int a = get_a(stu[i]);
            if (a >= thres1 && q1 > 0)
            {
                q1--;
                stu[i].pts += 15;
            }
            else if (a >= thres2 && q2 > 0)
            {
                q2--;
                stu[i].pts += 10;
            }
            else if (a >= thres3 && q3 > 0)
            {
                q3--;
                stu[i].pts += 5;
            }
        }
    };

    calc_term([](const Student &s)
              { return s.a1; }, [](const Student &s)
              { return s.b1; }, [](const Student &s)
              { return s.c1; });
    calc_term([](const Student &s)
              { return s.a2; }, [](const Student &s)
              { return s.b2; }, [](const Student &s)
              { return s.c2; });

    vector<int> id(n);
    iota(id.begin(), id.end(), 0);

    sort(id.begin(), id.end(), [&](int i, int j)
         {
        if (stu[i].pts != stu[j].pts) return stu[i].pts > stu[j].pts;
        if (stu[i].comp_total() != stu[j].comp_total()) return stu[i].comp_total() > stu[j].comp_total();
        if (stu[i].acad_total() != stu[j].acad_total()) return stu[i].acad_total() > stu[j].acad_total();
        return stu[i].name < stu[j].name; });

    for (int i = 0; i < min(n, m); i++)
    {
        if (stu[id[i]].name == "crazyzhk")
            return true;
    }
    return false;
}

void solve()
{
    int n;
    if (!(cin >> n))
        return;

    vector<Student> stu(n);
    int zhk = -1;

    // 先读入 n 个学生的信息
    for (int i = 0; i < n; i++)
    {
        cin >> stu[i].name >> stu[i].a1 >> stu[i].b1 >> stu[i].c1 >> stu[i].a2 >> stu[i].b2 >> stu[i].c2;
        stu[i].pts = 0;
        if (stu[i].name == "crazyzhk")
            zhk = i;
    }

    int m;
    i64 p, q;
    // 最后读入 m, p, q
    cin >> m >> p >> q;

    if (zhk == -1)
    {
        cout << "Surely next time\n";
        return;
    }

    i64 ans = INF;
    for (int i = 0; i <= 100 - stu[zhk].a1; i++)
    {
        for (int j = 0; j <= 100 - stu[zhk].a2; j++)
        {
            if (check(stu, i, j, n, m))
            {
                chmin(ans, 1ll * i * p + 1ll * j * q);
            }
        }
    }

    if (ans == INF)
    {
        cout << "Surely next time\n";
    }
    else
    {
        cout << ans << "\n";
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
    return 0;
}