#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    int n, m;
    while(t--)
    {
        cin >> n >> m;
        auto query = [&](int x, int y)
        {
            if(x < 1 || x > n || y < 1 || y > m)
                return -1;
            cout << "? " << x << " " << y << endl;
            cout.flush();
            int z;
            cin >> z;
            return z;
        };
        int d = query(1, 1);
        int lx = max(2 + d - m, 1);
        int p = query(lx, 2 + d - lx);
        int ry = max(1,2 + d - n);
        int q = query(2 + d - ry, ry);
        // int q = query(rx, 2 + d - rx);
        if(query(lx + p / 2,2 + d - lx - p / 2) == 0)
        {
            cout << "! " << lx + p / 2 << " " << 2 + d - lx - p / 2<< endl;
            cout.flush();
        }
        else
        {
            cout << "! " << 2 + d - ry - q / 2 << " " << ry + q / 2 << endl;
            cout.flush();
        }
    }
}