#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using ld = long double;
typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;
typedef pair<i64, i64> pll;
int Kadane(string s)
{
    int maxx = 0, minn = 0, now = 0;
    for (int i = 0; i< s.size();i++)
    {
        if(s[i] == '1')
            now++;
        else
            now--;
        maxx = max(maxx, now);
        if(now < 0)
            now = 0;
    }
    now = 0;
    for (int i = 0; i < s.size();i++)
    {
        if(s[i] == '1')
            now ++;
        else
            now--;
        minn = min(minn, now);
        if(now > 0)
            now = 0;
    }
    return max(maxx, abs(minn));
}
void solve()
{
    int n;
    string s,t;
    cin >> n >> s;
    for (int i = 0; i < n;i++)
    {
        if(i & 1 && s[i] == '1')
            t += s[i];
        if(!(i & 1) && s[i] == '0')
            t += s[i];
    }
    int ans = Kadane(t);        
    t.clear();
    for (int i = 0; i < n;i++)
    {
        if(i & 1 && s[i] == '0')
            t += s[i];
        if(!(i & 1) && s[i] == '1')
            t += s[i];
    }
    ans = min(ans, Kadane(t));
    cout << ans << "\n";
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