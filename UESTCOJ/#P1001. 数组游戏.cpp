// #include <bits/stdc++.h>
// #define ing long long
// using namespace std;
// int a[100005] = {0};
// int b[100050] = {0};
// signed main()
// {
//     ios::sync_with_stdio(0);
//     int n, m;
//     cin >> n >> m;
//     for (int i = 1; i <= n;i++)
//         cin >> a[i];
//     int index = 0;
//     while (m--)
//     {
//         int cnt = 0;
//         int l, r;
//         cin >> l >> r;
//         for (int i = l; i <= r;i++)
//         {
//             b[index++] = a[i];
//         }
//         sort(b, b + index);
//         int i = 0;
//         while (i < index)
//         {
//             if (b[i] == b[i + b[i] - 1] && b[i] != b[i+ b[i]])
//             {
//                 cnt++;
//                 i = i + b[i];
//             }
//             else
//             {
//                 int k = i + 1;
//                 for (; k < index;k++)
//                 {
//                     if(b[k] != b[i])
//                     { 
//                         i = k;
//                         break;
//                     }
//                 }
//             }
//         }
//         cout << cnt << "\n";
//     }
// }