// #include <bits/stdc++.h>
// using namespace std;
// int n;
// int vis[20] = {0};
// void dfs(int step,vector<int> vec)
// {
//     if (step == n)
//     {
//         for (auto &i: vec)
//         {
//             cout << setw(5) <<i;
//         }
//         cout << "\n";
//         return;
//     }
//     for (int i = 1; i <= n;i++)
//     {
//         if (!vis[i])
//         {
//             vec.push_back(i);
//             vis[i] = 1;
//             dfs(step + 1, vec);
//             vec.pop_back();
//             vis[i] = 0;
//         } 
//     }
// }

// int main()
// {
//     cin >> n;
//     vector<int> vec;
//     dfs(0,vec);
// }

//answer II
#include <bits/stdc++.h>
using namespace std;
int a[114514];
int main()
{
    int n;
    cin >> n;
    int mul = 1;
    for (int i = 1; i <= n;i++)
    {
        a[i] = i;
        mul *= i;
    }
    for (int i = 1; i <= mul;i++)
    {
        for (int i = 1; i <= n;i++)
            cout << setw(5) << a[i];
        next_permutation(a + 1, a + n + 1);
        cout << "\n";
    }
   
}