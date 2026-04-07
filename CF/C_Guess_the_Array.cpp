#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5005;
int a[N] = {0};
int tp[N] = {0};
int sum = 0;

signed main()
{
    int n;
    cin >> n;
    int b, c, d;
    cout << "? " << 1 << " " << 2 << endl;
    cout.flush();
    cin >> b;
    cout << "? " << 2 << " " << 3 << endl;
    cout.flush();
    cin >> c;
    cout << "? " << 1 << " " << 3 << endl;
    cout.flush();
    cin >> d;
    int total = (b + c + d) / 2;
    a[1] = total - c;
    a[2] = total - d;
    a[3] = total - b;
    int tp;
    for (int i = 4; i <= n;i++)
    {
        cout << "? " << 1 << " " << i << endl;
        cout.flush();
        cin >> tp;
        a[i] = tp - a[1];
    }
    cout << "!";
    for (int i = 1; i <= n;i++)
    {
        cout << " " << a[i];
    }
}