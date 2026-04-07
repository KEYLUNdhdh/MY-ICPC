#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int tree[N][2];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i <= n;i++)
    {
        cin >> tree[i][0] >> tree[i][1];
    }

    queue<int> q;
    int cnt = 1;
    q.push(1);
    int h = 0;
    int tp = 1;
    while(1)
    {
        int len = q.size();
        h++;
        for (int i = 0; i < len;i++)
        {
            if(tree[q.front()][0] != 0)
                q.push(tree[q.front()][0]);
            if(tree[q.front()][1] != 0)
                q.push(tree[q.front()][1]);
            q.pop();
        }
        if(q.empty())
            break;
    }
    cout << h;
}