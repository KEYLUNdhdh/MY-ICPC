// #include <bits/stdc++.h>
// using namespace std;
// int de(string& s)
// {
//     int len = s.size();
//     for (int i = 0; i < len - 1;i++)
//     {
//         if(s[i] == 'Y' && s[i + 1] == 'N' || s[i] == 'N' && s[i + 1] == 'Y')
//         {
//             s.erase(i);
//             s.erase(i);
//             s.insert(i,"Y");
//             return 1;
//         }
//         else if(s[i] == 'N' && s[ i + 1 ] == 'N')
//         {
//             s.erase(i);
//             s.erase(i);
//             s.insert(i, "N");
//             return 1;
//         }
//     }
//     return -1;
// }
// int main()
// {
//     int t;
//     cin >> t;
//     string s;
//     while(t--)
//     {
//         cin >> s;
//         while(de(s) != -1)
//         {

//         }
//         if(s.size() == 1)
//         {
//             cout << "YES\n";
//         }
//         else
//             cout << "NO\n";
//     }
// }

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;cin >> t;
    string s;
    while(t--)
    {
        cin >> s;
        int cnt = 0;
        for (int i = 0; i < s.size();i++)
        {
            if(s[i] == 'Y')
                cnt++;
        }
            if (cnt > 1)
            {
                cout << "NO\n";
            }
            else
            {
                cout << "YES\n";
            }
    }
}