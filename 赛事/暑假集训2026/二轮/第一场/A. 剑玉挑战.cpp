// #include <bits/stdc++.h>
// #ifndef ONLINE_JUDGE
// #define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
// void debug_out() { cerr << "\n"; }
// template <typename Head, typename... Tail>
// void debug_out(Head H, Tail... T) { cerr << " " << H; debug_out(T...); }
// #define debugarr(...) debugarr_out(#__VA_ARGS__, __VA_ARGS__)
// void debugarr_out(const char* names) {}
// template <typename Head, typename... Tail>
// void debugarr_out(const char* names, Head H, Tail... T) {
//     while (*names == ' ' || *names == ',') names++;
//     int bracket = 0, i = 0;
//     for (; names[i]; ++i) {
//         if (names[i] == '(' || names[i] == '{' || names[i] == '[') bracket++;
//         else if (names[i] == ')' || names[i] == '}' || names[i] == ']') bracket--;
//         else if (names[i] == ',' && bracket == 0) break;
//     }
//     cerr.write(names, i);
//     cerr << " : ";
//     for (auto v : H) cerr << v << " ";
//     cerr << "\n"; 
    
//     debugarr_out(names + i + 1, T...);
// }
// #define cutline { cerr << "----------------------\n"; }
// #else
// #define debug(...)
// #define debugarr(...)
// #define cutline
// #endif
// using namespace std;


// typedef long long ll;
// const int N = 200010;
// const int mod = 998244352;

// ll qmi(ll a, ll k, ll p){
//     ll res = 1;
//     while (k)
//     {
//         if (k & 1) res = (ll)res * a % p;
//         a = (ll)a * a % p;
//         k >>= 1;
//     }
//     return res;
// }

// ll madd(ll a, ll b,ll p) {
//     return (a + b) % p;
// }

// ll msub(ll a, ll b, ll p) {
//     return ((a - b) % p + p) % p;
// }

// ll mdiv(ll a, ll b, ll p) {
//     return a * qmi(b, p - 2, p) % p;
// }

// ll mmul(ll a, ll b, ll p) {
//     return (ll)a * b % p;
// }
// int n, k;
// ll p[N];
// ll pre[N];
// ll dp[N];

// int main() {
//     cin >> n >> k;
//     for (int i = 1; i <= n; ++i) {
//         int a, b;
//         cin >> a >> b;
//         p[i] = mdiv(a, b, mod);
//     }
//     pre[0] = 1;
//     for (int i = 1; i <= n; ++i) {
//         pre[i] = mmul(pre[i - 1], p[i], mod);
//     }
//     dp[k] = pre[k];
//     for (int i = k + 1; i <= n; ++i) {
//         //dp[i]=dp[i-1]*1+(1-dp[i-k-1])*(1-p[i-k])*最后k个都成功
//         ll tem = mmul(mmul(mdiv(pre[i], pre[i - k], mod), msub(1, p[i - k], mod), mod), msub(1, dp[i - k - 1], mod), mod);
//         dp[i] = madd(dp[i - 1], tem, mod);
//     }
//     debugarr(dp);
//     cout << dp[n] << endl;
//     return 0;
// }

