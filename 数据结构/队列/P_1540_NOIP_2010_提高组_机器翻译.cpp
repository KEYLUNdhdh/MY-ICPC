#include <bits/stdc++.h>
using namespace std;
int n, m;
int vis[1005] = {0};
queue<int> q;
int cnt = 0;
int main()
{
    cin >> m >> n;
    int x;
    for (int i = 0; i < n;i++)
    {
        cin >> x;
        if(vis[x])
        {
            continue;
        }   
        else if(q.size() < m)
        {
            q.push(x);
            vis[x] = 1;
            cnt++;
        }
        else
        {
            vis[q.front()] = 0;
            q.pop();
            vis[x] = 1;
            q.push(x);
            cnt++;
        }
    }
    cout << cnt;
}