#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 4;
int high[N] = {1};
int vis[15] = {0};
int len = 1;
int sum = 0;
map<int, vector<int>> mp;
void dfs(int p)
{
    vis[p] = 1;
    for (int i = 0; i < mp[p].size();i++)
    {
        if(!vis[mp[p][i]])
        {
            dfs(mp[p][i]);
        }   
    }
}

int main()
{
    string n;
    cin >> n;
    int k;
    cin >> k;
    for (int i = 0; i < k;i++)
    {
        int id, ys;
        cin >> id >> ys;
        mp[id].push_back(ys);
    }
    for (int k = 0; k < n.size();k++)
    {
        memset(vis, 0, sizeof(vis));
        dfs(n[k] - '0');
        for (int i = 0; i < 15;i++)
            sum += vis[i];
        int g = 0;
        for (int i = 0; i < len + 1;i++)
        {
            high[i] = high[i] * sum + g;
            g = high[i] / 10;
            high[i] = high[i] % 10;
        }
        for (int i = len + 5; i >= 0;i--)
        {
            if(high[i] != 0)
            {
                len = i + 1;
                break;
            }
        }
            sum = 0;
    }
    for (int k = len - 1; k >= 0;k--)
        cout << high[k];
    return 0;
}