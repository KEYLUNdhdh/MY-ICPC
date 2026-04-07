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
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> mp;
    int maxx = 0;
    int minn = 0x3f3f3f3f;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
        maxx = max(maxx, a[i]);
        minn = min(minn, a[i]);
    }
    mp = a;
    sort(mp.begin(), mp.end());
    mp.erase(unique(mp.begin(), mp.end()), mp.end());
    auto getid = [&](int x)
    {
        return lower_bound(mp.begin(), mp.end(), x) - mp.begin();
    };
    int m = mp.size();
    vector<int>  vis(n,0);
    for (int i = 0; i < n;i++)
    {
        vis[getid(a[i])]++;
    }
    int maxvis = -1;
    for (int i = m - 1; i >= 0;i--)
    {
        if(vis[i] % 2 == 1)
        {
            maxvis = i;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        int id = getid(a[i]);
        if(vis[getid(maxx)] % 2 == 0)
        {
            if(a[i] == maxx)
                cout << 0;
            else
                cout << 1;
        }
        else
        {   
            if(id == getid(maxx))
                cout << 1;
            else
                cout << 0;
        }
    }
    cout << "\n";
    
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