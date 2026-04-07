#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[25];
int vis[25] = {0};
int cnt = 0;
bool isPrime(int x)
{
    if(x == 1)
        return false;
    if(x == 2 || x== 3)
    {
        return true;
    }
    for (int i = 2; i * i <= x;i++)
    {
        if(x % i == 0)
            return false;
    }
    return true;
}
vector<int> vec;
void dfs(int s)
{
    if(vec.size() == k)
    {
        int sum = 0;
        for (int i = 0; i < vec.size();i++)
            sum += vec[i];
        if(isPrime(sum))
            cnt++;
        return;
    }
    for (int i = s; i < n;i++)
    {
        if(!vis[i])
        {
            vec.push_back(a[i]);
            vis[i] = 1;
            dfs(i + 1);
            vec.pop_back();
            vis[i] = 0;
        }
    }
    return;
}
int main()
{
    cin >> n >> k;
    for (int i = 0; i < n;i++)
    {
        cin >> a[i];
    }
    dfs(0);
    cout << cnt;
}