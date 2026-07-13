#include  <bits/stdc++.h>
using namespace std;
using i64 = long long;

int minRep(const string &s)
{
    int n = s.length();
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n)
    {
        int ni = i + k;
        if(ni >= n)
            ni -= n;
        int nj = j + k;
        if(nj >= n)
            nj -= n;

        if(s[ni] == s[nj])
            k++;
        else
        {
            if(s[ni] > s[nj])
                i += k + 1;
            else
                j += k + 1;
            
            if(i == j)
                j++;
            k = 0;
        }
    }
    return min(i, j);
}

// void solve() {
//     int n;
//     cin >> n;
//     string s;
//     cin >> s;

//     // 获取最小表示的起始位置
//     int start = minRep(s);

//     for (int i = start; i < n; i++) {
//         cout << s[i];
//     }
//     for (int i = 0; i < start; i++) {
//         cout << s[i];
//     }
//     cout << '\n';
// }