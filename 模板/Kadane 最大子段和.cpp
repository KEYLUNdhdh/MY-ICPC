#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
//最大字串和
void Kadane()
{
    int n;
    cin >> n;
    vector<i64> vec(n,0);
    for (int i = 0; i < n;i++)
        cin >> vec[i];
    i64 maxx = -1e9;
    i64 now = 0;
    for (int i = 0; i < n;i++)
    {
        now += vec[i];
        maxx = max(maxx, now);
        if(now < 0)
            now = 0;
    }
    cout << maxx;
}
//最小字串和
void KAdane()
{
    int n;
    cin >> n;
    vector<i64> vec(n,0);
    for (int i = 0; i < n;i++)
        cin >> vec[i];
    i64 minn = 1e9;
    i64 now = 0;
    for (int i = 0; i < n;i++)
    {
        now += vec[i];
        minn = min(minn, now);
        if(now > 0)
            now = 0;
    }
    cout << minn;
}
//也可以将整个数组取负再求最大字串和，最后填一个负号就行
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    // cin >> T;
    while(T--)
        KAdane();
    return 0;
}