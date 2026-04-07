#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;

void solve()
{
    i64 a, b, n;
    cin >> n;
    i64 k = 0;
    i64 tp = n;
    while(tp > 0)
    {
        tp >>= 1;
        k++;
    }
    a = n << k;
    b = a ^ n;
    cout << a << " " << b << "\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    while(T--)
        solve();
    return 0;
}