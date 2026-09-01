#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// const int N = 1e5 + 7;
ll t, n, cnt;
map<ll, ll> book;
map<ll, pair<ll, ll>> num;
map<ll, ll> rev;
ll dfs(ll k)
{
    if (book.find(k) != book.end())
    {
        return book[k];
    }
    num[k].second = dfs((k) / 2);
    num[k].first = dfs((k + 1) / 2);
    book[k] = ++cnt;
    rev[cnt] = k;
    // cerr<<"man "<<k<<" "<<book[k]<<" "<<num[k].first<<" "<<num[k].second<<"\n";
    return book[k];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while (t--)
    {
        book.clear();
        num.clear();
        rev.clear();
        num[1] = {-1, -1};
        num[2] = {0, 0};
        book[1] = 0;
        book[2] = 1;
        rev[0] = 1;
        rev[1] = 2;
        cnt = 1;
        cin >> n;
        dfs(n);
        if (n <= 2)
        {
            cout << "2\n";
            cout << "-1 -1\n";
            if (n == 2)
                cout << "0 0\n";
            else if (n == 1)
                cout << "0 -1\n";
            cout << "1\n";
            continue;
        }
        cout << cnt + 1 << "\n";
        // for (auto now : book)
        // {
        //     cout << num[now.first].first << " " << num[now.first].second << '\n';
        // }
        for (int i = 0; i <= cnt;i++)
        {
            ll sz = rev[i];
            cout << num[sz].first << " " << num[sz].second << "\n";
            // assert()
        }
        cout << cnt << "\n";
    }
}