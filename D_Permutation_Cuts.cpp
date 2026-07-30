// #include <bits/stdc++.h>
// #define lyc_fan_club main
// #define debug(x) { cerr << #x << " = " << x << "\n"; }
// #define debugarr(x){        \
//     cerr << #x << " : ";    \
//     for(auto v : x)         \
//     cerr << v << " ";       \
//     cerr << "\n";           \
// }
// #define cutline { cerr << "----------------------\n"; }
// using namespace std;
// using i64 = long long;
// using u32 = unsigned int;
// using u64 = unsigned long long;
// using i128 = __int128;
// using ld = long double;
// using db = double;
// typedef pair<int, int> pii;
// typedef pair<i64, i64> pll;
// typedef pair<i128, i128> pllll;
// mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

// template<class T>
// void chmin(T &a, T b) 
// {
//     if (a > b) 
//         a = b;
// }

// template<class T>
// void chmax(T &a, T b) 
// {
//     if (a < b) 
//         a = b;
// }
// bool ST;

// constexpr i64 MOD = 998244353, INF = 1e9;

// void solve()
// {
//     int n;
//     cin >> n;
//     vector<int> a(n, 0);
//     int ok = 1;
//     for (int i = 1; i <= n - 1;i++)
//     {
//         cin >> a[i];
//         if(a[i] < 1 || a[i] >= n)
//             ok = 0;
//     }

//     if(!ok)
//     {
//         cout << 0 << "\n";
//         return;
//     }
//     else if(n == 1)
//     {
//         cout << 1 << "\n";
//         return;
//     }
    
//     vector<int> pre(n, 0), suf(n, 0);
//     pre[0] = 1;
//     for (int i = 1; i <= n - 1;i++)
//     {
//         if(a[i] >= a[i - 1])
//             pre[i] = 1;
//         else
//             break;
//     }
//     suf[n - 1] = 1;
//     for (int i = n - 2; i >= 1;i--)
//     {
//         if(a[i] >= a[i + 1])
//             suf[i] = 1;
//         else
//             break;
//     }

//     vector<int> g;
//     if(suf[1])
//         g.push_back(0);
//     if(pre[n - 1])
//         g.push_back(n - 1);
//     for (int i = 1; i <= n - 2;i++)
//     {
//         if(pre[i] && suf[i + 1] && a[i] != a[i + 1])
//             g.push_back(i);
//     }
    
//     auto calc = [&](int k) -> i64
//     {
//         vector<int> cnt(n + 1, 0);
//         vector<int> forced(n + 1, 0);
//         for (int i = 1; i <= k;i++)
//         {
//             int x = a[i];
//             cnt[x]++;
//             if(i == 1 || a[i] != a[i - 1])
//                 forced[x]++;
//         }

//         for (int i = n - 1; i >= k + 1;i--)
//         {
//             int x = a[i];
//             cnt[x]++;
//             if(i == n - 1 || a[i] != a[i + 1])
//                 forced[x]++;
//         }
//         i64 res = 1;    
//         int used = 0;

//         for (int x = 1; x <= n - 1;x++)
//         {
//             if(cnt[x] == 0)
//                 continue;
            
//             if(forced[x] != 1)
//                 return 0;

//             int need = cnt[x] - 1;
//             int ava = x - 1 - used;
//             if(ava < need)
//                 return 0;
//             for (int j = 0; j < need;j++)
//                 res = res * (ava - j) % MOD;
//             used += cnt[x];
//         }
//         return res;

//     };

//     i64 ans = 0;
//     for(int k : g)
//         ans = (ans + calc(k)) % MOD;

//     cout << ans << "\n";
// }

// bool ED;
// signed lyc_fan_club()
// {
//     ios::sync_with_stdio(0);
//     cin.tie(0);
//     int T = 1;
//     cin >> T;
//     while(T--)
//         solve();
//     cerr << "time used: " << (double)clock() / CLOCKS_PER_SEC << endl;
//     cerr << "memory used: " << abs(&ST - &ED) / 1024.0 / 1024.0 << " MB" << endl;
//     return 0;
// }