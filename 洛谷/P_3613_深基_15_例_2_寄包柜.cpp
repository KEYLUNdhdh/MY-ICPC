#include <bits/stdc++.h>
using namespace std;
typedef struct d{
    int id, good = 0;
} d;
int main()
{
    ios::sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<map<int,int>> vec(n + 5);
    int ch;
    int j, i, k;
    d tp;
    while(q--)
    {
        cin >> ch;
        if(ch == 1)
        {
            cin >> i >> j >> k;
            vec[i][j] = k;
        }
        else
        {
            cin >> i >> j;
            cout << vec[i][j] << "\n";
        }
    }
}