#include <bits/stdc++.h>
using namespace std;
//mean 1
int a[3] = {0};
int vis[15] = {0};
vector<int> vec;
void dfs(int step)
{
    if (step == 3)
    {
        cout << vec[0] << " " << vec[1] << " " << vec[2] << "\n";
        return;
    }
    for (int i = 0; i < 3;i++)
    {
        if(!vis[a[i]])
        {
            vis[a[i]] = 1;
            vec.push_back(a[i]);
            dfs(step + 1);
            vis[a[i]] = 0;
            vec.pop_back();
        }
    }
    return;
}
int main()
{
    int t;
    cin >> t;
    int index = 1;
    while (t--)
    {
        cin >> a[0] >> a[1] >> a[2];
        cout << "Case #" << index << ":\n";
        if (a[0] == a[1] && a[1] == a[2])
        {
            cout << a[0] << " " << a[1] << " " << a[2] << "\n";
        }
        else if (a[0] == a[1] || a[1] == a[2] || a[0] == a[2])
        {
            sort(a, a + 3);
            cout << a[0] << " " << a[1] << " " << a[2] << "\n";
            for (int i = 0; i < 2;i++)
            {
                next_permutation(a, a + 3);
                cout << a[0] << " " << a[1] << " " << a[2] << "\n";
            }
        }
        else
        {
            sort(a, a + 3);
            dfs(0);
        }
        index++;
    }
}