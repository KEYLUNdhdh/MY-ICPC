#include <bits/stdc++.h>
using namespace std;
int minstep[100005];
int ans = 0x3f3f3f3f;
int n, m;
void dfs(int now,int step)
{
    if (now < 0 || now > m * 2)
    {
        return;
    }
    if (step > minstep[now])
    {
        return;
    }
    minstep[now] = step;
    if (now == m)   
    {
        ans = min(ans, step);
        return;
    }
    dfs(now * 2, step + 1);
    dfs(now - 1, step + 1);
}
//来点bfs
int bfs()
{
    memset(minstep, -1, sizeof(minstep));
    queue<int> q;
    q.push(n);
    minstep[n] = 0;
    while (!q.empty())
    {
        int tp = q.front();
        q.pop();
        if (tp == m)
        {
            return minstep[tp];
        }
        //tp - 1
        if (tp - 1 > 0&&minstep[tp -1] == -1 )
        {
            minstep[tp - 1] = minstep[tp] + 1;
            q.push(tp - 1);
        }
        if (tp * 2 < 20005 && tp < m &&  minstep[tp * 2] == -1 )
        {
            minstep[tp * 2] = minstep[tp] + 1;
            q.push(tp * 2);
        }
    }
    return -1;
}
int main()
{
    cin >> n >> m;
    memset(minstep, 0x3f, sizeof(minstep));
    if (n > m)
    {
        cout << n - m;
        return 0;
    }
    dfs(n, 0);
    cout << ans;
    // cout << bfs();
    return 0;
}