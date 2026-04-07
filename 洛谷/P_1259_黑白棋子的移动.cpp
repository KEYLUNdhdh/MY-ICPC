#include <bits/stdc++.h>
using namespace std;

void solve(int len,int step)
{
    if (len == 3)
        return;
    for (int i = 0; i < len;i++)
        cout << "o";
    for (int i = 0; i < len;i++)
        cout << "*";
    cout << "--";
    for (int i = 0; i < step;i++)
        cout << "o*";
    cout << "\n";
    for (int i = 0; i < len - 1;i++)
        cout << "o";
    cout << "--";
    for (int i = 0; i < len - 1;i++)
        cout << "*";
    for (int i = 0; i < step + 1;i++)
        cout << "o*";
    cout << "\n";
    solve(len - 1, step + 1);
}

int main()
{
    int n;
    cin >> n;
    solve(n, 0);
    cout << "ooo*o**--*";
    for (int i = 0; i < n - 4;i++)
        cout << "o*";
    cout << "\n";
    cout << "o--*o**oo*";
    for (int i = 0; i < n - 4;i++)
        cout << "o*";
    cout << "\n";
    cout << "o*o*o*--o*";
    for (int i = 0; i < n - 4;i++)
        cout << "o*";
    cout << "\n";
    cout << "--";
    for (int i = 0; i < n;i++)
    {
        cout << "o*";
    }
}