#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n;
// int a[N] = {0};
// int cal (int x,int y)
// {
//     int tp = abs(x - y);
//     int tp2 = 8 - abs(x - y);
//     return min(tp, tp2);
// }
int vis[9] = {0};
int main()
{
    int t;
    cin >> t;
    deque<int> a;
    while(t--)
    {
        cin >> n;
        int cnt = 0;
        a.resize(n);
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < n;i++)
        {
            cin >> a[i];
            vis[a[i]] = 1;
        }
        int maxx = 0;
        a.clear();
        for (int i = 1; i <= 8;i++)
        {
            if(vis[i])
                a.push_back(i);
        }
        // for(auto i : a)
        //     cout << i << " ";
        // cout << endl;
        for (int i = 0; i < a.size() - 1;i++)
        {
            maxx = max(maxx, a[i + 1] - a[i]);
        }
        maxx = max(maxx, a[0] - a[a.size() - 1] + 8);
        cout << 8 - maxx << "\n";
        a.clear();
    }
}